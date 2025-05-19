#include "RPN.hpp"

Rpn::Rpn(){
    //
}

Rpn::Rpn(const Rpn &src) {
    *this = src;
}

Rpn::~Rpn() {
    //
}

Rpn &Rpn::operator=(const Rpn &src) {
    (void)src;
    return *this;
}

float Rpn::result(const std::string &input){
    std::list<float> stack;

    bool isSpace = false;
    for (std::string::const_iterator it = input.begin(); it != input.end(); it++) {
        if (*it != ' ' && !isSpace && stack.size() != 0) {
            throw Rpn::BadExpressionException();
        }

        isSpace = (*it == ' ');
        if (*it == ' ') {
            continue;
        }

        if (isdigit(*it)) {
            stack.push_back(*it - '0'); 
        }
        else {
            if (stack.size() < 2) {
                throw Rpn::BadExpressionException();
            }
            float b = stack.back();
            stack.pop_back();
            float a = stack.back();
            stack.pop_back();

            switch (*it) {
                case '+':
                    stack.push_back(a + b);
                    break;
                case '-':
                    stack.push_back(a - b);
                    break;
                case '*':
                    stack.push_back(a * b);
                    break;
                case '/':
                    if (b == 0) {
                        throw Rpn::DivisionBy0();
                    }
                    stack.push_back(a / b);
                    break;
                default:
                    throw Rpn::BadExpressionException();
                    break;
            }
        }
    }
    if (stack.size() != 1) {
        throw Rpn::RemainingTerms();
    }   
    return stack.front();
}

const char *Rpn::BadExpressionException::what() const throw() {
    return "Error: Bad expression";
}

const char *Rpn::DivisionBy0::what() const throw() {
    return "Error: Division by 0";
}

const char *Rpn::RemainingTerms::what() const throw() {
    return "Error: Remaining terms";
}