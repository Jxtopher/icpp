#ifndef ICPP_INPUT_CONSOLE_H
#define ICPP_INPUT_CONSOLE_H

#include <cstdint>    // uint
#include <cstdio>     // printf
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string
#include <tuple>      // std::tuple
#include <iostream>

#include "brackets.hpp"
#include "buffer_toggle.hpp"
#include "dict.hpp"
#include "term.hpp"

namespace icpp {

/**
 * http://www.climagic.org/mirrors/VT100_Escape_Codes.html
 */
class InputConsole {
 public:
    InputConsole() {}
    void prompt(uint num_line, char joker = '>') {
        if (joker == '!') {
            printf("[!]: ");
        } else {
            printf("[%d]: ", num_line);
        }
    }

    /**
     * @brief Colorization of the code source.
     *
     * @param current_line text to colorize
     * @param offset offset from which to analyse
     * @return (number of caracters n, color) with the next n to color
     */
    std::tuple<uint, const char *> colorization(const std::string &current_line,
                                                uint offset) {
        if (current_line.size() > 0 && current_line[0] == '!' ||
            current_line.size() == 0) {
            return std::pair<uint, const char *>{0, term::color::NO_COLOR};
        } else {
            dict::cpp::keywords;
            int max_length = 0;
            const char *color = term::color::NO_COLOR;

            // Double quote
            if (current_line[offset] == '"') {
                color = term::color::GREEN;
                max_length += 1;
                while (offset + max_length < current_line.size() &&
                       current_line[offset + max_length] != '"')
                    max_length++;
                max_length += 1;
            }

            // Single quotes
            if (current_line[offset] == '\'') {
                color = term::color::GREEN;
                max_length += 1;
                while (offset + max_length < current_line.size() &&
                       current_line[offset + max_length] != '\'')
                    max_length++;
                max_length += 1;
            }

            // Numeric
            if (current_line[offset] >= '0' && current_line[offset] <= '9') {
                color = term::color::BROWN;
                while (offset + max_length < current_line.size() &&
                       current_line[offset + max_length] >= '0' &&
                       current_line[offset + max_length] <= '9')
                    max_length++;
            }

            // Keyword-core
            for (std::string keyword : dict::cpp::keywords) {
                std::string substr =
                    current_line.substr(offset, keyword.size());
                if (substr == keyword && keyword.size() > max_length) {
                    max_length = keyword.size();
                    color = term::color::PURPLE;
                }
            }

            // Functions
            for (auto include : dict::cpp::includes) {
                for (std::string keyword : include.second) {
                    std::string substr =
                        current_line.substr(offset, keyword.size());
                    if (substr == keyword && keyword.size() > max_length) {
                        max_length = keyword.size();
                        color = term::color::BROWN;
                    }
                }
            }

            return std::make_tuple(max_length, color);
        }
    }

    // Print the line with the colorarisation and good position of cursor
    void text(const std::string &current_line, uint cursor_position = 0) {
        if (cursor_position < 0) return;
        
        uint mark;
        const char *color;
        std::tie(mark, color) = colorization(current_line, 0);

        bool state = mark != 0;
        for (uint i = 0; i < current_line.size() - cursor_position; i++) {
            if (mark == 0) {
                printf("%s", term::color::NO_COLOR);
                std::tie(mark, color) = colorization(current_line, i);
                if (mark != 0) {
                    state = true;
                }
            }
            if (mark > 0) {
                if (state) {
                    printf("%s", color);
                    state = false;
                }
                mark--;
            }
            printf("%c", current_line[i]);
        }
        printf("%s", term::color::NO_COLOR);
    }

    std::string operator()(uint &num_line) {
        uint cursor_history = 0;
        uint cursor_left_right = 0;
        Brackets brackets;
        std::string current_line;
        bt.off();

        prompt(num_line);
        while (true) {
            char char_0 = std::getchar();
            if (char_0 == '\033') {
                getchar();
                char char_2 = getchar();


                switch (char_2) {
                    case 'A':  // Arrow up
                        if (history.size() > cursor_history)
                            cursor_history++;
                        if (history.size() != 0)
                            current_line =
                                history[history.size() - cursor_history];
                        break;
                    case 'B':  // Arrow down
                        if (cursor_history > 0)
                            cursor_history--;
                        if (history.size() != 0 && cursor_history > 0)
                            current_line =
                                history[history.size() - cursor_history];
                        else
                            current_line.clear();
                        break;
                    case 'C':  // Arrow right
                        if (cursor_left_right > 0)
                            cursor_left_right--;
                        break;
                    case 'D':  // Arrow left
                        if (cursor_left_right < current_line.size())
                            cursor_left_right++;
                        break;
                    case '3': // "Suppr"
                        {
                            getchar();
                            if (cursor_left_right > 0) {
                                auto it = current_line.begin();
                                std::advance(it,
                                            current_line.size() - cursor_left_right);
                                cursor_left_right--;
                                current_line.erase(it);
                            }
                        }
                        break;
                    case 'F': // "Fin"
                        cursor_left_right = 0;
                        break;
                    case '6': // "PgSv"
                        getchar();
                        break;
                    case '5': // "PgPr"
                        getchar();
                        break;
                    case 'H': // "Orig"
                        cursor_left_right = current_line.size();
                        break;
                    case '2': // "Inser"
                        getchar();
                        break;
                    default:
                        throw std::runtime_error(
                            std::string{} + __FILE__ + ":" +
                            std::to_string(__LINE__) + " [-] ");
                }
            } else if (char_0 == ASCII_TAB) {
            } else if (char_0 == ASCII_DEL) {
                printf("%s", term::CLEAR_LINE);
                if (current_line.size() - cursor_left_right > 0) {
                    brackets.analysis(current_line[current_line.size() -
                                                   cursor_left_right - 1],
                                      true);
                    auto it = current_line.begin();
                    std::advance(it,
                                 current_line.size() - cursor_left_right - 1);
                    current_line.erase(it);
                }
            } else if (char_0 == ASCII_ENTER) {
                if (brackets.is_closed()) {
                    history.push_back(current_line);
                    num_line++;
                    break;
                } else {
                    // ! Need to clean lines
                    // char char_temp = '\n';
                    // brackets.analysis(char_temp);
                    // auto it = current_line.begin();
                    // std::advance(it, current_line.size() -
                    // cursor_left_right); current_line.insert(it, char_temp);
                }
            } else {
                brackets.analysis(char_0);
                auto it = current_line.begin();
                std::advance(it, current_line.size() - cursor_left_right);
                current_line.insert(it, char_0);
            }
            printf("%s\r", term::CLEAR_LINE);
            prompt(num_line, current_line.empty() ? '>' : current_line[0]);
            text(current_line);
            if (cursor_left_right > 0) {
                printf("\r");
                prompt(num_line, current_line.empty() ? '>' : current_line[0]);
                text(current_line, cursor_left_right);
            }
        }

        bt.on();
        printf("\n");
        return current_line;
    }

    void show_history() {
        for (auto item : history) {
            std::cout << item << std::endl;
        }
    }

 private:
    std::vector<std::string> history;
    BufferToggle bt;

    static const unsigned char ASCII_DEL = 127;
    static const unsigned char ASCII_ENTER = 10;
    static const unsigned char ASCII_TAB = 9;
};
}  // namespace icpp

#endif