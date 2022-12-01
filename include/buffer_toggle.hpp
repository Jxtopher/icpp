
#ifndef ICPP_BUFFER_TOGGLE_H
#define ICPP_BUFFER_TOGGLE_H

#include <termios.h>
#include <unistd.h>

namespace icpp {
class BufferToggle {
 private:
    struct termios t;

 public:
    // Disable press enter before proceeding
    void off(void) {
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag &= static_cast<tcflag_t>(~ICANON & ~ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
    }

    // Enable waits for you to press enter before proceeding
    void on(void) {
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag |= static_cast<tcflag_t>(ICANON & ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
    }
};

}  // namespace icpp

#endif