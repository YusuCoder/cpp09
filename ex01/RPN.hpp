#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <list>

class Rpn
{
    public:
        Rpn();
        Rpn(const Rpn &src);
        ~Rpn();
        Rpn &operator=(const Rpn &src);

        float result(const std::string &input);
        class BadExpressionException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
        class DivisionBy0: public std::exception
        {
            public:
                virtual const char *what() const throw();
        };

        class RemainingTerms : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
};
#endif