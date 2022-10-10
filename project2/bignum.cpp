#include <mpfr.h>
#include <iostream>
#include <string.h>

#pragma once

class Bignum
{
protected:
    // Storing the prototype.
    mpfr_t num;

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
        mpfr_set_default_prec(prec);
    }

    // Used to define precision when showing.
    static mpfr_prec_t show_precision;

    // Initialize.

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
        mpfr_set_str(num, ptr, 0, get_default_rounding_mode());
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
        mpfr_set(num, from.num, get_default_rounding_mode());
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
        mpfr_set_str(num, ptr, 0, get_default_rounding_mode());
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
        Bignum result;
        mpfr_add(result.num, num, another.num, get_default_rounding_mode());
        return result;
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
        Bignum result;
        mpfr_sub(result.num, num, another.num, get_default_rounding_mode());
        return result;
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

    // multiply

    Bignum operator*(const Bignum &another)
    {
        Bignum result;
        mpfr_mul(result.num, num, another.num, get_default_rounding_mode());
        return result;
    }

    Bignum operator*(const Bignum &&another)
    {
        Bignum result;
        mpfr_mul(result.num, num, another.num, get_default_rounding_mode());
        return result;
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
        Bignum result;
        mpfr_div(result.num, num, another.num, get_default_rounding_mode());
        return result;
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