#ifndef ICPP_VERSION_H
#define ICPP_VERSION_H

#include <iostream>

namespace icpp {
void version(const std::string &num_version) {
    std::cout << "IC++ " << num_version
              << " -- An enhanced Interactive C++. Type '?' for help."
              << std::endl;
}
}  // namespace icpp

#endif
