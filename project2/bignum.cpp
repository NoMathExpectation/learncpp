#include <mpfr.h>
#include <iostream>
#include <string.h>

#pragma once

class Bignum
{
protected:
    // Storing the prototype.
    mpfr_t num;

    // Used to define digits count to show when printing.
    static mpfr_prec_t show_precision;

public:
    // Get or set default rounding mode, binding to mpfr.
    static mpfr_rnd_t get_default_rounding_mode()
    {
        return mpfr_get_default_rounding_mode();
    }

    static void set_default_rounding_mode(mpfr_rnd_t mode)
    {
        mpfr_set_default_rounding_mode(mode);
    }

    // Get or set default precision, binding to mpfr, all existed Bignums remain unchanged.
    static mpfr_prec_t get_default_precision()
    {
        return mpfr_get_default_prec();
    }

    static void set_default_precision(mpfr_prec_t prec)
    {
        // mpfr internal assertion
        if (!((prec) >= 1 && (prec) <= ((mpfr_prec_t)((((mpfr_uprec_t)-1) >> 1) - 256))))
        {
            throw std::invalid_argument("Illegal precision " + std::to_string(prec) + ".");
        }

        mpfr_set_default_prec(prec);
    }

    // Get or set show precision.
    static mpfr_prec_t get_show_precision()
    {
        return show_precision;
    }

    static void set_show_precision(mpfr_prec_t digits)
    {
        if (digits < 0)
        {
            throw std::invalid_argument("Show precision must not be negative.");
        }

        show_precision = digits;
    }

    // Initialize.

    // constant pi
    static Bignum pi()
    {
        Bignum pi;
        mpfr_const_pi(pi.num, get_default_rounding_mode());
        return pi;
    }

    // constant e
    static Bignum e()
    {
        return Bignum(1L).power_by_e();
    }

    // constant euler
    static Bignum euler()
    {
        Bignum euler;
        mpfr_const_euler(euler.num, get_default_rounding_mode());
        return euler;
    }

    // constant catalan
    static Bignum catalan()
    {
        Bignum catalan;
        mpfr_const_catalan(catalan.num, get_default_rounding_mode());
        return catalan;
    }

    // constant positive zero
    static Bignum positive_zero()
    {
        Bignum zero;
        mpfr_set_zero(zero.num, 1);
        return zero;
    }

    // constant negative zero
    static Bignum negative_zero()
    {
        Bignum zero;
        mpfr_set_zero(zero.num, -1);
        return zero;
    }

    // constant positive infinity
    static Bignum positive_inf()
    {
        Bignum inf;
        mpfr_set_inf(inf.num, 1);
        return inf;
    }

    // constant negative infinity
    static Bignum negative_inf()
    {
        Bignum inf;
        mpfr_set_inf(inf.num, -1);
        return inf;
    }

    // constant NaN
    static Bignum nan()
    {
        Bignum nan;
        mpfr_set_nan(nan.num);
        return nan;
    }

    // No value, set to NaN by mpfr.
    Bignum()
    {
        mpfr_init(num);
    }

    Bignum(const Bignum &from)
    {
        mpfr_init_set(num, from.num, get_default_rounding_mode());
    }

    Bignum(const Bignum &&from) : Bignum(from) {}

    Bignum(const unsigned long int num)
    {
        mpfr_init_set_ui(this->num, num, get_default_rounding_mode());
    }

    Bignum(const long int num)
    {
        mpfr_init_set_si(this->num, num, get_default_rounding_mode());
    }

    Bignum(const float num) : Bignum()
    {
        mpfr_set_flt(this->num, num, get_default_rounding_mode());
    }

    Bignum(const double num)
    {
        mpfr_init_set_d(this->num, num, get_default_rounding_mode());
    }

    Bignum(const long double num)
    {
        mpfr_init_set_ld(this->num, num, get_default_rounding_mode());
    }

    Bignum(const char *ptr) : Bignum()
    {
        int result = mpfr_set_str(num, ptr, 0, get_default_rounding_mode());
        if (result != 0)
        {
            throw std::invalid_argument("Not a valid number.");
        }
    }

    // unititialize.
    ~Bignum()
    {
        mpfr_clear(num);
    }

    // assignment

    void operator=(const Bignum &from)
    {
        mpfr_set(num, from.num, get_default_rounding_mode());
    }

    void operator=(const Bignum &&from)
    {
        *this = from;
    }

    void operator=(const unsigned long int num)
    {
        mpfr_set_ui(this->num, num, get_default_rounding_mode());
    }

    void operator=(const long int num)
    {
        mpfr_set_si(this->num, num, get_default_rounding_mode());
    }

    void operator=(const float num)
    {
        mpfr_set_flt(this->num, num, get_default_rounding_mode());
    }

    void operator=(const double num)
    {
        mpfr_set_d(this->num, num, get_default_rounding_mode());
    }

    void operator=(const long double num)
    {
        mpfr_set_ld(this->num, num, get_default_rounding_mode());
    }

    void operator=(const char *ptr)
    {
        Bignum copy(*this);
        int result = mpfr_set_str(num, ptr, 0, get_default_rounding_mode());
        if (result != 0)
        {
            *this = copy;
            throw std::invalid_argument("Not a valid number.");
        }
    }

    long get_long()
    {
        return mpfr_get_si(num, get_default_rounding_mode());
    }

    unsigned long get_ulong()
    {
        return mpfr_get_ui(num, get_default_rounding_mode());
    }

    long double get_ldouble()
    {
        return mpfr_get_ld(num, get_default_rounding_mode());
    }

    // calculating

    // plus

    Bignum operator+(const Bignum &another)
    {
        Bignum result;
        mpfr_add(result.num, num, another.num, get_default_rounding_mode());
        return result;
    }

    Bignum operator+(const Bignum &&another)
    {
        return *this + another;
    }

    Bignum operator+(const unsigned long int another)
    {
        Bignum result;
        mpfr_add_ui(result.num, num, another, get_default_rounding_mode());
        return result;
    }

    Bignum operator+(const long int another)
    {
        Bignum result;
        mpfr_add_si(result.num, num, another, get_default_rounding_mode());
        return result;
    }

    Bignum operator+(const double another)
    {
        Bignum result;
        mpfr_add_d(result.num, num, another, get_default_rounding_mode());
        return result;
    }

    // minus

    Bignum operator-(const Bignum &another)
    {
        Bignum result;
        mpfr_sub(result.num, num, another.num, get_default_rounding_mode());
        return result;
    }

    Bignum operator-(const Bignum &&another)
    {
        return *this - another;
    }

    Bignum operator-(const unsigned long int another)
    {
        Bignum result;
        mpfr_sub_ui(result.num, num, another, get_default_rounding_mode());
        return result;
    }

    Bignum operator-(const long int another)
    {
        Bignum result;
        mpfr_sub_si(result.num, num, another, get_default_rounding_mode());
        return result;
    }

    Bignum operator-(const double another)
    {
        Bignum result;
        mpfr_sub_d(result.num, num, another, get_default_rounding_mode());
        return result;
    }

    Bignum minus_by(const unsigned long int another)
    {
        Bignum result;
        mpfr_ui_sub(result.num, another, num, get_default_rounding_mode());
        return result;
    }

    Bignum minus_by(const long int another)
    {
        Bignum result;
        mpfr_si_sub(result.num, another, num, get_default_rounding_mode());
        return result;
    }

    Bignum minus_by(const double another)
    {
        Bignum result;
        mpfr_d_sub(result.num, another, num, get_default_rounding_mode());
        return result;
    }

    // multiply

    Bignum operator*(const Bignum &another)
    {
        Bignum result;
        mpfr_mul(result.num, num, another.num, get_default_rounding_mode());
        return result;
    }

    Bignum operator*(const Bignum &&another)
    {
        return *this * another;
    }

    Bignum operator*(const unsigned long int another)
    {
        Bignum result;
        mpfr_mul_ui(result.num, num, another, get_default_rounding_mode());
        return result;
    }

    Bignum operator*(const long int another)
    {
        Bignum result;
        mpfr_mul_si(result.num, num, another, get_default_rounding_mode());
        return result;
    }

    Bignum operator*(const double another)
    {
        Bignum result;
        mpfr_mul_d(result.num, num, another, get_default_rounding_mode());
        return result;
    }

    // divide

    Bignum operator/(const Bignum &another)
    {
        Bignum result;
        mpfr_div(result.num, num, another.num, get_default_rounding_mode());
        return result;
    }

    Bignum operator/(const Bignum &&another)
    {
        return *this / another;
    }

    Bignum operator/(const unsigned long int another)
    {
        Bignum result;
        mpfr_div_ui(result.num, num, another, get_default_rounding_mode());
        return result;
    }

    Bignum operator/(const long int another)
    {
        Bignum result;
        mpfr_div_si(result.num, num, another, get_default_rounding_mode());
        return result;
    }

    Bignum operator/(const double another)
    {
        Bignum result;
        mpfr_div_d(result.num, num, another, get_default_rounding_mode());
        return result;
    }

    Bignum divide_by(const unsigned long int another)
    {
        Bignum result;
        mpfr_ui_div(result.num, another, num, get_default_rounding_mode());
        return result;
    }

    Bignum divide_by(const long int another)
    {
        Bignum result;
        mpfr_si_div(result.num, another, num, get_default_rounding_mode());
        return result;
    }

    Bignum divide_by(const double another)
    {
        Bignum result;
        mpfr_d_div(result.num, another, num, get_default_rounding_mode());
        return result;
    }

    // power

    Bignum power(Bignum &exp)
    {
        Bignum result;
        mpfr_pow(result.num, num, exp.num, get_default_rounding_mode());
        return result;
    }

    Bignum power(Bignum &&exp)
    {
        return power(exp);
    }

    Bignum power(const unsigned long int exp)
    {
        Bignum result;
        mpfr_pow_ui(result.num, num, exp, get_default_rounding_mode());
        return result;
    }

    Bignum power(const long int exp)
    {
        Bignum result;
        mpfr_pow_si(result.num, num, exp, get_default_rounding_mode());
        return result;
    }

    static Bignum power(const unsigned long int base, const unsigned long int exp)
    {
        Bignum result;
        mpfr_ui_pow_ui(result.num, base, exp, get_default_rounding_mode());
        return result;
    }

    Bignum power_by(Bignum &exp)
    {
        return exp.power(*this);
    }

    Bignum power_by(Bignum &&exp)
    {
        return power_by(exp);
    }

    Bignum power_by(const unsigned long int base)
    {
        Bignum result;
        mpfr_ui_pow(result.num, base, num, get_default_rounding_mode());
        return result;
    }

    Bignum power_by_2()
    {
        Bignum result;
        mpfr_exp2(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum power_by_e()
    {
        Bignum result;
        mpfr_exp(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum power_by_10()
    {
        Bignum result;
        mpfr_exp10(result.num, num, get_default_rounding_mode());
        return result;
    }

    // root

    // note: this function will transform n to unsigned long int
    Bignum root(Bignum &n)
    {
        return root(n.get_ulong());
    }

    // note: this function will transform n to unsigned long int
    Bignum root(Bignum &&n)
    {
        return root(n);
    }

    Bignum root(const unsigned long int n)
    {
        Bignum result;
        mpfr_rootn_ui(result.num, num, n, get_default_rounding_mode());
        return result;
    }

    Bignum sqrt()
    {
        Bignum result;
        mpfr_sqrt(result.num, num, get_default_rounding_mode());
        return result;
    }

    static Bignum sqrt(unsigned long int n)
    {
        Bignum result;
        mpfr_sqrt_ui(result.num, n, get_default_rounding_mode());
        return result;
    }

    Bignum cbrt()
    {
        Bignum result;
        mpfr_cbrt(result.num, num, get_default_rounding_mode());
        return result;
    }

    // note: this function will transform the object to unsigned long int
    Bignum root_by(Bignum &n)
    {
        return n.root(get_ulong());
    }

    // note: this function will transform the object to unsigned long int
    Bignum root_by(Bignum &&n)
    {
        return root_by(n);
    }

    Bignum root_by(const unsigned long int n)
    {
        return Bignum(n).root(*this);
    }

    Bignum root_by(const long double n)
    {
        return Bignum(n).root(*this);
    }

    // negative value

    Bignum neg()
    {
        Bignum result;
        mpfr_neg(result.num, num, get_default_rounding_mode());
        return result;
    }

    // absolute value

    Bignum abs()
    {
        Bignum result;
        mpfr_abs(result.num, num, get_default_rounding_mode());
        return result;
    }

    // logarithm

    Bignum log(const Bignum &base)
    {
        Bignum a, b;
        mpfr_log2(a.num, num, get_default_rounding_mode());
        mpfr_log2(b.num, base.num, get_default_rounding_mode());
        return a / b;
    }

    Bignum log(const Bignum &&base)
    {
        return log(base);
    }

    Bignum log(const unsigned long int n)
    {
        return log(Bignum(n));
    }

    Bignum log(const long int n)
    {
        return log(Bignum(n));
    }

    Bignum log(const long double n)
    {
        return log(Bignum(n));
    }

    Bignum log2()
    {
        Bignum result;
        mpfr_log2(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum ln()
    {
        Bignum result;
        mpfr_log(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum lg()
    {
        Bignum result;
        mpfr_log10(result.num, num, get_default_rounding_mode());
        return result;
    }

    // trigonometric functions

    Bignum sin()
    {
        Bignum result;
        mpfr_sin(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum cos()
    {
        Bignum result;
        mpfr_cos(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum tan()
    {
        Bignum result;
        mpfr_tan(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum cot()
    {
        Bignum result;
        mpfr_cot(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum sec()
    {
        Bignum result;
        mpfr_sec(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum csc()
    {
        Bignum result;
        mpfr_csc(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum asin()
    {
        Bignum result;
        mpfr_asin(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum acos()
    {
        Bignum result;
        mpfr_acos(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum atan()
    {
        Bignum result;
        mpfr_atan(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum sinh()
    {
        Bignum result;
        mpfr_sinh(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum cosh()
    {
        Bignum result;
        mpfr_cosh(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum tanh()
    {
        Bignum result;
        mpfr_tanh(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum coth()
    {
        Bignum result;
        mpfr_coth(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum sech()
    {
        Bignum result;
        mpfr_sech(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum csch()
    {
        Bignum result;
        mpfr_csch(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum asinh()
    {
        Bignum result;
        mpfr_asinh(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum acosh()
    {
        Bignum result;
        mpfr_acosh(result.num, num, get_default_rounding_mode());
        return result;
    }

    Bignum atanh()
    {
        Bignum result;
        mpfr_atanh(result.num, num, get_default_rounding_mode());
        return result;
    }

    // define friend ostream functions for printing
    friend std::ostream &operator<<(std::ostream &os, const Bignum &num);
    friend std::ostream &operator<<(std::ostream &os, const Bignum &&num);
};

// Define default showing precision.
mpfr_prec_t Bignum::show_precision = 10;

// ostream output.
std::ostream &operator<<(std::ostream &os, const Bignum &num)
{
    mpfr_printf(("%." + std::to_string(Bignum::show_precision) + "RNF").data(), num.num);
    return os;
}

std::ostream &operator<<(std::ostream &os, const Bignum &&num)
{
    mpfr_printf(("%." + std::to_string(Bignum::show_precision) + "RNF").data(), num.num);
    return os;
}

// cin input.
std::istream &operator>>(std::istream &is, Bignum &num)
{
    char chars[mpfr_get_default_prec()];
    is >> chars;
    num = chars;
    return is;
}