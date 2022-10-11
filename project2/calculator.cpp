#include "bignum.cpp"
#include <string.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <regex>
#include <cmath>
#include <functional>

#pragma once

class Calculator
{
protected:
    // storing varibles
    std::unordered_map<std::string, Bignum> varibles;
    // storing common functions
    static const std::unordered_map<std::string, std::function<Bignum(std::vector<Bignum> &)>> functions;

    // used to detect empty characters
    const static std::regex empty_chars;
    // used to detect operators and brackets
    const static std::regex ops;

    Bignum eval0(std::string expr)
    {
        // get rid of empty characters
        std::regex_replace(expr, empty_chars, "");

        // throw if is empty
        if (expr.empty())
        {
            throw std::invalid_argument("Empty expression detected. Please check your expression.");
        }

        // store expression which ignores expression inside brackets;
        std::string no_inside;
        size_t level = 0;
        for (const char &c : expr)
        {
            switch (c)
            {
            case '(':
                if (level <= 0)
                {
                    no_inside += c;
                }
                else
                {
                    no_inside += '.';
                }

                level++;
                break;

            case ')':
                if (level <= 0)
                {
                    throw std::invalid_argument("Bracket not paired or operator missing. Please check your expression.");
                }

                level--;
                // no break to continue to add the char at default

            default:
                if (level <= 0)
                {
                    no_inside += c;
                }
                else
                {
                    no_inside += '.';
                }
            }
        }

        size_t match_index = 0;

        // assignment
        match_index = no_inside.find_first_of('=');
        if (match_index != std::string::npos)
        {
            std::string &&varible = expr.substr(0, match_index);
            if (std::regex_search(expr, ops))
            {
                throw std::invalid_argument("Assignments between two sub-expressions are not allowed.");
            }

            Bignum &&value = eval0(expr.substr(match_index + 1));
            varibles[varible] = value;
            return value;
        }

        // plus & minus
        match_index = fmin(no_inside.find_first_of('+'), no_inside.find_first_of('-'));
        if (match_index != std::string::npos)
        {
            Bignum &&left = eval0(expr.substr(0, match_index));
            Bignum &&right = eval0(expr.substr(match_index + 1));
            switch (expr[match_index])
            {
            case '+':
                return left + right;
            case '-':
                return left - right;
            }
        }

        // multiply & divide
        match_index = fmin(no_inside.find_first_of('*'), no_inside.find_first_of('/'));
        if (match_index != std::string::npos)
        {
            Bignum &&left = eval0(expr.substr(0, match_index));
            Bignum &&right = eval0(expr.substr(match_index + 1));
            switch (expr[match_index])
            {
            case '*':
                return left * right;
            case '/':
                return left / right;
            }
        }

        // functions & brackets
        match_index = no_inside.find_first_of('(');
        if (match_index != std::string::npos)
        {
            size_t length = no_inside.find_first_of(')') - 1 - match_index;
            std::string &&func_name = no_inside.substr(0, match_index);
            std::string &&arg_string = expr.substr(match_index + 1, length);
            
            std::vector<std::string> args_string;
            while (size_t delimiter_index = arg_string.find_first_of(',') != std::string::npos) {
                args_string.push_back(arg_string.substr(0, delimiter_index));
                arg_string.erase(0, delimiter_index + 1);
            }
            args_string.push_back(arg_string);
            
            std::vector<Bignum> args;
            std::transform(args_string.begin(), args_string.end(), args.begin(), eval0);

            for (auto &function_pair: functions) {
                if (function_pair.first == func_name) {
                    return function_pair.second(args);
                }
            }

            throw std::invalid_argument("Unknown function " + func_name);
        }

        // reading varibles
        varibles["pi"] = Bignum::pi();
        varibles["e"] = Bignum::e();
        varibles["catalan"] = Bignum::catalan();

        varibles.try_emplace(expr, Bignum::positive_zero());
        return varibles[expr];
    }

    public:
    ~Calculator() {
        mpfr_free_cache();
    }

    Bignum eval(std::string expr) {
        Bignum &&result = eval0(expr);
        varibles["ans"] = result;
        return result;
    }
};

const std::regex Calculator::empty_chars{"\\s\n"};
const std::regex Calculator::ops{"[+\\-*/()]"};

const std::unordered_map<std::string, std::function<Bignum(std::vector<Bignum> &)>> Calculator::functions = {
    { "", [] (std::vector<Bignum> &args) { return args[0]; } },
    { "sqrt", [] (std::vector<Bignum> &args) { return args[0].sqrt(); } },
    { "cbrt", [] (std::vector<Bignum> &args) { return args[0].cbrt(); } },
    { "root", [] (std::vector<Bignum> &args) { return args[0].root(args[1]); } },
    { "pow", [] (std::vector<Bignum> &args) { return args[0].power(args[1]); } },
    { "pow2", [] (std::vector<Bignum> &args) { return args[0].power_by_2(); } },
    { "powe", [] (std::vector<Bignum> &args) { return args[0].power_by_e(); } },
    { "pow10", [] (std::vector<Bignum> &args) { return args[0].power_by_10(); } },
    { "log", [] (std::vector<Bignum> &args) { return args[0].log(args[1]) ;} },
    { "log2", [] (std::vector<Bignum> &args) { return args[0].log2(); } },
    { "ln", [] (std::vector<Bignum> &args) { return args[0].ln(); } },
    { "lg", [] (std::vector<Bignum> &args) { return args[0].lg(); } },
    { "sin", [] (std::vector<Bignum> &args) { return args[0].sin(); } },
    { "cos", [] (std::vector<Bignum> &args) { return args[0].cos(); } },
    { "tan", [] (std::vector<Bignum> &args) { return args[0].tan(); } },
    { "cot", [] (std::vector<Bignum> &args) { return args[0].cot(); } },
    { "sec", [] (std::vector<Bignum> &args) { return args[0].sec(); } },
    { "csc", [] (std::vector<Bignum> &args) { return args[0].csc(); } },
    { "asin", [] (std::vector<Bignum> &args) { return args[0].asin(); } },
    { "acos", [] (std::vector<Bignum> &args) { return args[0].acos(); } },
    { "atan", [] (std::vector<Bignum> &args) { return args[0].atan(); } },
    { "sinh", [] (std::vector<Bignum> &args) { return args[0].sinh(); } },
    { "cosh", [] (std::vector<Bignum> &args) { return args[0].cosh(); } },
    { "tanh", [] (std::vector<Bignum> &args) { return args[0].tanh(); } },
    { "coth", [] (std::vector<Bignum> &args) { return args[0].coth(); } },
    { "sech", [] (std::vector<Bignum> &args) { return args[0].sech(); } },
    { "csch", [] (std::vector<Bignum> &args) { return args[0].csch(); } },
    { "asinh", [] (std::vector<Bignum> &args) { return args[0].asinh(); } },
    { "acosh", [] (std::vector<Bignum> &args) { return args[0].acosh(); } },
    { "atanh", [] (std::vector<Bignum> &args) { return args[0].atanh(); } },
};