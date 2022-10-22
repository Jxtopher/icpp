
#ifndef ICPP_HEADERS_H
#define ICPP_HEADERS_H
#include <string>
#include <vector>

#include "dict.hpp"

namespace icpp {
class Headers : public std::vector<std::string> {
 public:
    void code_analysis(const std::string &code_line) {
        for (auto it = dict::cpp::includes.cbegin();
             it != dict::cpp::includes.cend(); ++it) {
            for (auto token = it->second.cbegin(); token != it->second.cend();
                 ++token) {
                if (code_line.find(*token) != std::string::npos) {
                    this->push_back(it->first);
                }
            }
        }
    }
};
}  // namespace icpp

#endif