#ifndef ICPP_HELP_H
#define ICPP_HELP_H

#include <iostream>
#include <string>
#include <vector>

namespace icpp {
void help() {
    std::vector<std::string> text{
        "\t?\t\t-> Access IC++'s own help system.",
        "\t!\t\t-> Call shell commands.",
        "\texit\t\t-> Close the IC++.",
        "\treset\t\t-> ",
        "\treset-on\t-> ",
        "\treset-off\t-> ",
        "\thistory\t\t-> ",
        "\tinclude\t\t-> ",
        "\texport\t\t-> ",
    };

    for (auto line : text) {
        std::cout << line << std::endl;
    }
}

}  // namespace icpp

#endif