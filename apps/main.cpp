#include <fcntl.h>
#include <stdlib.h>  // mkostemp
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>  // O_WRONLY
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <threads.h>
#include <unistd.h>  // read

#include <cassert>
#include <chrono>
#include <cstdio>   // perror
#include <cstring>  // size_t
#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <stop_token>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "headers.hpp"
#include "help.hpp"
#include "input_console.hpp"
#include "term.hpp"
#include "version.hpp"

#define NUM_VERSION "0.0.0"

namespace icpp {
#define WRITE_END 1
#define READ_END  0

int fd_out[2];
int fd_err[2];
pid_t pID;

void create_child(const std::string &programname,
                  const std::vector<std::string> &arg, char **envp) {
    pipe(fd_out);
    pipe(fd_err);
    pID = fork();
    if (pID == 0) {  // child
        const char **argv = new const char *[arg.size() + 2];
        argv[0] = programname.c_str();
        for (uint j = 0; j < arg.size() + 1; ++j) argv[j + 1] = arg[j].c_str();
        argv[arg.size() + 1] = NULL;  // end of arguments sentinel is NULL

        dup2(fd_out[WRITE_END], STDOUT_FILENO);
        // dup2(fd_err[WRITE_END], STDERR_FILENO);
        close(fd_out[WRITE_END]);
        // close(fd_err[WRITE_END]);
        int ret = execvpe(programname.c_str(), const_cast<char **>(argv), envp);
        if (ret == -1) {
            std::cerr << programname << ": " << strerror(errno) << std::endl;
        }
    } else if (pID < 0) {
        throw std::runtime_error(std::string{} + __FILE__ + ":" +
                                 std::to_string(__LINE__) +
                                 " [-] Failed to fork");
    } else {
        close(fd_out[WRITE_END]);
        // close(fd_err[WRITE_END]);
    }
}

bool filter(const std::string &code_line, uint num_line) {
    if (num_line <= 1)
        return false;
    std::regex re("(.*)(std::cout)(.*)");
    std::cmatch m;
    return std::regex_match(code_line.c_str(), m, re);
}

void create_source(const std::string &path, const Headers &headers,
                   const std::vector<std::string> &code_lines) {
    std::ofstream out(path);
    for (const auto &header : headers) {
        out << "#include <" << header << ">" << std::endl;
    }
    out << "int main() {" << std::endl;
    for (uint i = 0; i < code_lines.size(); i++) {
        if (!filter(code_lines[i], code_lines.size() - i)) {
            out << code_lines[i] << std::endl;
        }
    }
    out << "return 0; }" << std::endl;
    out.close();
}

auto sandglass = [](std::stop_token stoken) {
    char c[5] = {"\\|/-"};
    int i = 0;
    while (i < 4 && !stoken.stop_requested()) {
        printf("[%c]\r", c[i]);
        fflush(stdout);
        i = i >= 3 ? 0 : i + 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
};

}  // namespace icpp

int main(int argc, char **argv, char **envp) {
    using namespace icpp;
    version(NUM_VERSION);

    InputConsole input_console;
    const int buffer_size = 256;
    char buff[buffer_size];
    Headers headers;
    std::string source_file_path = std::string{std::tmpnam(nullptr)} + ".cpp";
    std::string binary_file_path{std::tmpnam(nullptr)};

    int status;
    int size;
    bool reset;
    const std::string compilator{"g++"};
    std::vector<std::string> options{"-g", source_file_path, "-o",
                                     binary_file_path, "--std=c++20"};

    uint num_line = 0;
    std::vector<std::string> code_lines;

    while (true) {
        std::string code_line = input_console(num_line);

        if (code_line == "") {
            num_line--;
            continue;
        } else if (code_line[0] == '!') {
            num_line--;
            system(code_line.substr(1).c_str());
            continue;
        } else if (code_line[0] == '?') {
            help();
            num_line--;
            continue;
        } else if (code_line == "exit") {
            break;
        } else if (code_line == "reset") {
            headers.clear();
            num_line = 0;
            code_lines.clear();
            continue;
        } else if (code_line == "reset-on") {
            reset = true;
            continue;
        } else if (code_line == "reset-off") {
            reset = false;
            continue;
        } else if (code_line == "history") {
            input_console.show_history();
            continue;
        }
        if (reset) {
            headers.clear();
            num_line = 0;
            code_lines.clear();
        }
        code_line =
            std::regex_replace(code_line, std::regex("^<<"), "std::cout<<");

        headers.code_analysis(code_line);
        code_lines.push_back(code_line);
        create_source(source_file_path, headers, code_lines);

        // Compilation
        create_child(compilator, options, envp);
        std::jthread thread_object(sandglass);
        waitpid(pID, &status, 0);
        thread_object.request_stop();
        if (status != 0) {
            num_line--;
            code_lines.pop_back();
            continue;
        }

        // while ((size = read(fd_err[READ_END], buff, buffer_size)) > 0) {
        //     write(STDERR_FILENO, buff, size);
        // }

        while ((size = read(fd_out[READ_END], buff, buffer_size)) > 0) {
            write(STDOUT_FILENO, buff, size);
        }

        // Execution of code
        create_child(binary_file_path, {""}, envp);
        std::jthread thread_object2(sandglass);
        waitpid(pID, &status, 0);
        thread_object2.request_stop();
        bool back_to_line = false;
        while ((size = read(fd_out[READ_END], buff, buffer_size)) > 0) {
            printf("%s", term::CLEAR_LINE);
            fflush(stdout);
            write(STDOUT_FILENO, buff, size);
            for (uint i = 0; i < size; i++) {
                back_to_line = buff[i] != '\n';
            }
        }
        if (back_to_line) {
            printf("\n");
        }
    }

    std::remove(source_file_path.c_str());
    std::remove(binary_file_path.c_str());

    return 0;
}
