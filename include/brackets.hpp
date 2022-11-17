#ifndef ICPP_BRACKETS_H
#define ICPP_BRACKETS_H

// ! Need to fixed "if([xx]*)"
namespace icpp {
class Brackets {
 public:
    Brackets()
        : parenthesis(0),
          square_brackets(0),
          curly_brackets(0),
          single_quotes(true),
          double_quotes(true) {}

    bool is_closed() const {
        return true;  // parenthesis == 0 && square_brackets == 0 &&
                      // curly_brackets == 0 && single_quotes && double_quotes;
    }

    void analysis(unsigned char c, bool revert = false) {
        if (single_quotes && double_quotes) {
            if (c == '(')
                parenthesis = revert ? parenthesis - 1 : parenthesis + 1;
            else if (c == ')')
                parenthesis = revert ? parenthesis + 1 : parenthesis - 1;
            else if (c == '[')
                square_brackets =
                    revert ? square_brackets - 1 : square_brackets + 1;
            else if (c == ']')
                square_brackets =
                    revert ? square_brackets + 1 : square_brackets - 1;
            else if (c == '{')
                curly_brackets =
                    revert ? curly_brackets - 1 : curly_brackets + 1;
            else if (c == '}')
                curly_brackets =
                    revert ? curly_brackets + 1 : curly_brackets - 1;
        }
        if (c == '\'')
            single_quotes = !single_quotes;
        else if (c == '"')
            double_quotes = !double_quotes;
    }

 private:
    int parenthesis;
    int square_brackets;
    int curly_brackets;
    bool single_quotes;
    bool double_quotes;
};
}  // namespace icpp

#endif
