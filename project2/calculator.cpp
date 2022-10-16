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
    // storing variables
    std::unordered_map<std::string, Bignum> variables;
    // storing common functions
    static const std::unordered_map<std::string, std::function<Bignum(std::vector<Bignum> &)>> functions;

    // used to detect empty characters
    const static std::regex empty_chars;
    // used to detect operators and brackets
    const static std::regex invalid_variables;
    // used to detcet numbers
    const static std::regex numbers;

    // used to check argument count inside functions
    static void check_args_count(std::vector<Bignum> &args, size_t count)
    {
        if (args.size() == count)
        {
            return;
        }

        throw std::invalid_argument("Expected " + std::to_string(count) + " args, but got " + std::to_string(args.size()) + ".");
    }

    // used to check if a variable is legal
    static void check_variable(std::string &variable)
    {
        if (std::regex_search(variable, invalid_variables))
        {
            throw std::invalid_argument("Illegal variable \"" + variable + "\", please try to use another name.");
        }
    }

    // used to filter inside expressions
    static std::string filter_inside_brackets(std::string &str)
    {
        std::string no_inside;
        size_t level = 0;

        for (const char &c : str)
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
                    throw std::invalid_argument("Bracket not paired. Please check your expression.");
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

        if (level > 0)
        {
            throw std::invalid_argument("Bracket not paired. Please check your expression.");
        }

        return no_inside;
    }

    // used to filter numbers
    static std::string filter_numbers(std::string &str)
    {
        std::string result = str;
        for (std::sregex_iterator it(result.begin(), result.end(), numbers); it != std::sregex_iterator(); it++)
        {
            std::smatch match = *it;
            std::fill(result.begin() + match.position(), result.begin() + match.position() + match.length(), '.');
        }

        return result;
    }

    // internal evaluate expression
    Bignum eval0(std::string expr)
    {

        // throw if it is empty
        if (expr.empty())
        {
            throw std::invalid_argument("Empty sub-expression detected. Please check your expression.");
        }

        std::string &&no_inside = filter_inside_brackets(expr);
        std::string &&no_number = filter_numbers(no_inside);

        // assignment
        size_t match_index = no_inside.find_first_of('=');
        if (match_index != std::string::npos)
        {
            std::string &&variable = expr.substr(0, match_index);
            check_variable(variable);

            Bignum &&value = eval0(expr.substr(match_index + 1));
            variables[variable] = value;
            return value;
        }

        // plus & minus
        match_index = fmin(no_number.find_first_of('+'), no_number.find_first_of('-'));
        if (match_index != std::string::npos)
        {
            bool negative = false;
            while (match_index == 0)
            {
                if (no_inside[0] == '-')
                {
                    negative = !negative;
                }
                no_inside.erase(0, 1);
                no_number.erase(0, 1);
                expr.erase(0, 1);
                match_index = fmin(no_number.find_first_of('+'), no_number.find_first_of('-'));
            }

            Bignum &&left = eval0(expr.substr(0, match_index));
            if (negative)
            {
                left = left.neg();
            }

            if (match_index == std::string::npos)
            {
                return left;
            }

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
            size_t length = no_inside.find_first_of(')');
            if (no_inside.size() > length + 1)
            {
                throw std::invalid_argument("Redundant expression detected. Please check your expression.");
            }

            length -= match_index + 1;
            std::string &&func_name = no_inside.substr(0, match_index);
            std::string &&arg_string = expr.substr(match_index + 1, length);
            std::string &&filtered_arg_string = filter_inside_brackets(arg_string);

            std::vector<std::string> args_string;
            while (true)
            {
                size_t delimiter_index = filtered_arg_string.find_first_of(',');
                if (delimiter_index == std::string::npos)
                {
                    args_string.push_back(arg_string);
                    break;
                }

                args_string.push_back(arg_string.substr(0, delimiter_index));
                arg_string.erase(0, delimiter_index + 1);
                filtered_arg_string.erase(0, delimiter_index + 1);
            }

            std::vector<Bignum> args(args_string.size());
            std::transform(args_string.begin(), args_string.end(), args.begin(), [=](std::string &expr)
                           { return eval0(expr); });

            for (auto &function_pair : functions)
            {
                if (function_pair.first == func_name)
                {
                    return function_pair.second(args);
                }
            }

            throw std::invalid_argument("Unknown function \"" + func_name + "\".");
        }

        // try to convert to number
        try
        {
            return Bignum(expr.data());
        }
        catch (...)
        {
        }

        // reading variables
        check_variable(expr);

        variables["pi"] = Bignum::pi();
        variables["e"] = Bignum::e();
        variables["euler"] = Bignum::euler();
        variables["catalan"] = Bignum::catalan();
        variables["prec"] = Bignum(Bignum::get_default_precision());
        variables["show"] = Bignum(Bignum::get_show_precision());

        if (variables.count(expr) == 0)
        {
            // all unassigned variables are regarded as 0
            variables[expr] = Bignum::positive_zero();
        }

        return variables[expr];
    }

public:
    ~Calculator()
    {
        mpfr_free_cache();
    }

    // evaluate expression
    Bignum eval(std::string expr)
    {
        // get rid of empty characters
        expr = std::regex_replace(expr, empty_chars, "");

        Bignum &&result = eval0(expr);
        variables["ans"] = result;
        return result;
    }
};

const std::regex Calculator::empty_chars{"[\\s\n]"};
const std::regex Calculator::invalid_variables{"[+\\-*/()=]|\\d*\\.?\\d*e[+-]?\\d+|0[xXbB][0-9a-fA-F]+"};
const std::regex Calculator::numbers{"(\\d*\\.?\\d*e[+-]?\\d+|0[xXbB][0-9a-fA-F]+)"};

const std::unordered_map<std::string, std::function<Bignum(std::vector<Bignum> &)>> Calculator::functions = {
    {"", [](std::vector<Bignum> &args)
     {check_args_count(args, 1);
         return args[0]; }},
    {"sqrt", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].sqrt();
     }},
    {"cbrt", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].cbrt();
     }},
    {"root", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 2);
         return args[0].root(args[1]);
     }},
    {"pow", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 2);
         return args[0].power(args[1]);
     }},
    {"pow2", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].power_by_2();
     }},
    {"powe", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].power_by_e();
     }},
    {"pow10", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].power_by_10();
     }},
    {"log", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 2);
         return args[1].log(args[0]);
     }},
    {"log2", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].log2();
     }},
    {"ln", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].ln();
     }},
    {"lg", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].lg();
     }},
    {"sin", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].sin();
     }},
    {"cos", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].cos();
     }},
    {"tan", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].tan();
     }},
    {"cot", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].cot();
     }},
    {"sec", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].sec();
     }},
    {"csc", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].csc();
     }},
    {"asin", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].asin();
     }},
    {"acos", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].acos();
     }},
    {"atan", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].atan();
     }},
    {"sinh", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].sinh();
     }},
    {"cosh", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].cosh();
     }},
    {"tanh", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].tanh();
     }},
    {"coth", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].coth();
     }},
    {"sech", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].sech();
     }},
    {"csch", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].csch();
     }},
    {"asinh", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].asinh();
     }},
    {"acosh", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].acosh();
     }},
    {"atanh", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         return args[0].atanh();
     }},
    {"prec", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         Bignum::set_default_precision(args[0].get_long());
         return args[0];
     }},
    {"show", [](std::vector<Bignum> &args)
     {
         check_args_count(args, 1);
         Bignum::set_show_precision(args[0].get_long());
         return args[0];
     }},
};