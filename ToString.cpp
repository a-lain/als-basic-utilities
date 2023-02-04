#ifndef ALS_UTILITIES_TO_STRING_CPP
#define ALS_UTILITIES_TO_STRING_CPP

#include <string>
#include <complex>
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#include "FormatNumber.hpp"
#include "ToString.hpp"
#include <iostream>
#include <cmath>

using namespace als::utilities;
std::string als::utilities::to_string(const unsigned long long val,
    const RepresentationType rt, const bool show_sign)
{
    return ((val > 0 && show_sign) ? "+": "") + std::to_string(val);
}

std::string als::utilities::to_string(const long long val,
    const RepresentationType rt, const bool show_sign)
{
    return ((val > 0 && show_sign) ? "+": "") + std::to_string(val);
}

std::string als::utilities::to_string(long double x,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup)
{
    if (precision == 0)
    {
        return std::string("0");
    }

    else
    {
        // First, we check whether the number is infinite or NaN.
        if (std::isinf(x))
        {
            return (rt == RepresentationType::PLAIN) ? "inf": "\\infty";
        }
        else if (std::isnan(x))
        {
            return (rt == RepresentationType::PLAIN) ? "NaN": "\\mathrm{NaN}";
        }
        else
        {
            // We calculate the decimal logarithm of 'x', unless it's zero. In that case,
            // we impose log10(0):=0. We add a small number to faciliate rounding up operations.
            double log10_x = (x != 0) ? std::log10(std::fabs(x)*(1 + 1./long_double_pow10(precision+1))) : 0;

            // If we apply the floor function to 'log10_x', we will obtain the exponent needed
            // for the scientific notation of the number. Please realize that the exponent is
            // computed even if the conditions for scientific notation display are not met;
            // this calculation will be needed later. Explanation: let our number 'x' be
            // greater than 1, for example between 10^3 and 10^4. Then the required 
            // exponent for the number's scientific notation is 3. On the contrary, if our
            // number 'x' is less than 1, for instance between 10^(-3) and 10^(-4), the
            // searched exponent will be -4. Therefore, the exponent will always be the
            // floor function of the 'log10_x'.
            int exponent = (int) std::floor(log10_x);

            // We always round off the number to the wanted precision first.
            unsigned long long base = (exponent - (int)precision + 1 >= 0) ?
                (unsigned long long)std::round(std::fabs(x) / long_double_pow10(exponent - precision + 1))
                : (unsigned long long)round(std::fabs(x) * long_double_pow10(precision - exponent - 1));

            // We take into account the sign stuff.
            std::string sign = "";
            if (x > 0 && show_sign)
            {
                sign = "+";
            }
            else if (x < 0)
            {
                sign = "-";
            }

            // If the conditions for scientific notation display are satisfied.
            if (log10_x >= lim_sup || log10_x <= lim_inf)
            {
                // The special case of a power of ten.
                if (base == long_pow10(precision - 1))
                {
                    return sign + ( (rt == RepresentationType::LATEX) ?
                    "10^{" + std::to_string(exponent) + "}" : "10^(" + std::to_string(exponent) + ")");
                }
                else
                {
                    std::string end = (rt == RepresentationType::LATEX) ?
                        "\\cdot 10^{" + std::to_string(exponent) + "}" : "*10^(" + std::to_string(exponent) + ")";
                    return sign + std::to_string(base).insert(1, ".") + end;     
                }        
            }

            else
            {
                if (base == 0)
                {
                    return "0." + std::string(precision - 1, '0');
                }
                else
                {
                    if (exponent >= 0)
                    {
                        if ((unsigned int)exponent + 1 >= precision)
                        {
                            return sign + std::to_string(base * long_pow10(exponent + 1 - precision));
                        }
                        else
                        {
                            return sign + std::to_string(base).insert(exponent + 1, ".");
                        }
                    }
                    else
                    {
                        return sign + "0." + std::string(-exponent - 1, '0') + std::to_string(base);
                    }
                }
            }
        }
    }
}

std::string als::utilities::to_string(const std::string& str,
    const RepresentationType rt)
{
    // std::string pre = (rt == RepresentationType::LATEX) ? "\\text{" : "";
    // std::string post = (rt == RepresentationType::LATEX) ? "\\}" : "";
    // return pre + str + post;
    return str;
}

std::string als::utilities::to_string(const char* const str,
    const RepresentationType rt)
{
    return als::utilities::to_string(std::string(str), rt);
}

std::string als::utilities::to_string(const bool& val,
    const RepresentationType rt)
{
    return als::utilities::to_string(val ? "true": "false", rt);
}

std::string als::utilities::to_string(const RepresentationType val,
    const RepresentationType rt)
{
    return als::utilities::to_string(val ==
        RepresentationType::PLAIN ? "PLAIN": "LATEX", rt);
}

std::string als::utilities::to_string(const signed char& val,
    const RepresentationType rt, const bool show_sign)
{
    return als::utilities::to_string((long long)val, rt, show_sign);
}

std::string als::utilities::to_string(const char& val,
    const RepresentationType rt)
{
    return als::utilities::to_string(std::to_string(val), rt);
}

std::string als::utilities::to_string(const unsigned char& val,
    const RepresentationType rt, const bool show_sign)
{
    return als::utilities::to_string((unsigned long long)val, rt, show_sign);
}

std::string als::utilities::to_string(const short int& val,
    const RepresentationType rt, const bool show_sign)
{
    return als::utilities::to_string((long long)val, rt, show_sign);
}

std::string als::utilities::to_string(const unsigned short int& val,
    const RepresentationType rt, const bool show_sign)
{
    return als::utilities::to_string((unsigned long long)val, rt, show_sign);
}

std::string als::utilities::to_string(const int& val,
    const RepresentationType rt, const bool show_sign)
{
    return als::utilities::to_string((long long)val, rt, show_sign);
}

std::string als::utilities::to_string(const unsigned int& val,
    const RepresentationType rt, const bool show_sign)
{
    return als::utilities::to_string((unsigned long long)val, rt, show_sign);
}

std::string als::utilities::to_string(const long int& val,
    const RepresentationType rt, const bool show_sign)
{
    return als::utilities::to_string((long long)val, rt, show_sign);
}

std::string als::utilities::to_string(const unsigned long int& val,
    const RepresentationType rt, const bool show_sign)
{
    return als::utilities::to_string((unsigned long long)val, rt, show_sign);
}

std::string als::utilities::to_string(float x,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup)
{
    return als::utilities::to_string((long double)x, rt, precision,
        show_sign, lim_inf, lim_sup);
}

std::string als::utilities::to_string(double x,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup)
{
    return als::utilities::to_string((long double)x, rt, precision,
        show_sign, lim_inf, lim_sup);
}


// We begin template instantiation.
template <> std::string als::utilities::to_string(const std::complex<double>& z,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::complex<double>& z,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::complex<double>& z,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::complex<double>& z,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::complex<double>& z,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::vector<char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::vector<char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::vector<unsigned char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::vector<unsigned char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::vector<short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::vector<short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::vector<unsigned short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::vector<unsigned short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::vector<int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::vector<int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::vector<unsigned int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::vector<unsigned int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::vector<long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::vector<long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::vector<unsigned long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::vector<unsigned long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::vector<long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::vector<long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::vector<unsigned long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::vector<unsigned long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::vector<std::string>& object,
    const RepresentationType rt);

template <> std::string als::utilities::to_string(const std::vector<float>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::vector<float>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::vector<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::vector<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::vector<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::vector<double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::vector<double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::vector<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::vector<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::vector<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::vector<long double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::vector<long double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::vector<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::vector<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::vector<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);


template <> std::string als::utilities::to_string(const std::deque<char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::deque<char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::deque<unsigned char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::deque<unsigned char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::deque<short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::deque<short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::deque<unsigned short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::deque<unsigned short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::deque<int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::deque<int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::deque<unsigned int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::deque<unsigned int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::deque<long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::deque<long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::deque<unsigned long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::deque<unsigned long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::deque<long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::deque<long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::deque<unsigned long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::deque<unsigned long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::deque<std::string>& object,
    const RepresentationType rt);

template <> std::string als::utilities::to_string(const std::deque<float>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::deque<float>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::deque<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::deque<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::deque<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::deque<double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::deque<double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::deque<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::deque<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::deque<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::deque<long double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::deque<long double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::deque<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::deque<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::deque<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);


template <> std::string als::utilities::to_string(const std::forward_list<char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::forward_list<char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::forward_list<unsigned char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::forward_list<unsigned char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::forward_list<short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::forward_list<short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::forward_list<unsigned short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::forward_list<unsigned short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::forward_list<int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::forward_list<int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::forward_list<unsigned int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::forward_list<unsigned int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::forward_list<long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::forward_list<long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::forward_list<unsigned long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::forward_list<unsigned long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::forward_list<long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::forward_list<long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::forward_list<unsigned long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::forward_list<unsigned long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::forward_list<std::string>& object,
    const RepresentationType rt);

template <> std::string als::utilities::to_string(const std::forward_list<float>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::forward_list<float>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::forward_list<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::forward_list<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::forward_list<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::forward_list<double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::forward_list<double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::forward_list<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::forward_list<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::forward_list<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::forward_list<long double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::forward_list<long double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::forward_list<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::forward_list<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::forward_list<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);


template <> std::string als::utilities::to_string(const std::list<char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::list<char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::list<unsigned char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::list<unsigned char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::list<short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::list<short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::list<unsigned short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::list<unsigned short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::list<int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::list<int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::list<unsigned int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::list<unsigned int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::list<long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::list<long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::list<unsigned long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::list<unsigned long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::list<long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::list<long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::list<unsigned long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::list<unsigned long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::list<std::string>& object,
    const RepresentationType rt);

template <> std::string als::utilities::to_string(const std::list<float>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::list<float>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::list<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::list<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::list<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::list<double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::list<double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::list<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::list<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::list<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::list<long double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::list<long double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::list<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::list<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::list<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);


template <> std::string als::utilities::to_string(const std::set<char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::set<char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::set<unsigned char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::set<unsigned char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::set<short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::set<short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::set<unsigned short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::set<unsigned short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::set<int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::set<int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::set<unsigned int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::set<unsigned int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::set<long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::set<long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::set<unsigned long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::set<unsigned long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::set<long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::set<long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::set<unsigned long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::set<unsigned long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::set<std::string>& object,
    const RepresentationType rt);

template <> std::string als::utilities::to_string(const std::set<float>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::set<float>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::set<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::set<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::set<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::set<double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::set<double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::set<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::set<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::set<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::set<long double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::set<long double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::set<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::set<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::set<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);


template <> std::string als::utilities::to_string(const std::multiset<char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::multiset<char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::multiset<unsigned char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::multiset<unsigned char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::multiset<short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::multiset<short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::multiset<unsigned short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::multiset<unsigned short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::multiset<int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::multiset<int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::multiset<unsigned int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::multiset<unsigned int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::multiset<long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::multiset<long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::multiset<unsigned long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::multiset<unsigned long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::multiset<long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::multiset<long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::multiset<unsigned long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::multiset<unsigned long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::multiset<std::string>& object,
    const RepresentationType rt);

template <> std::string als::utilities::to_string(const std::multiset<float>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::multiset<float>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::multiset<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::multiset<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::multiset<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::multiset<double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::multiset<double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::multiset<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::multiset<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::multiset<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::multiset<long double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::multiset<long double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::multiset<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::multiset<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::multiset<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);


template <> std::string als::utilities::to_string(const std::unordered_set<char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_set<char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_set<unsigned char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_set<unsigned char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_set<short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_set<short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_set<unsigned short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_set<unsigned short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_set<int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_set<int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_set<unsigned int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_set<unsigned int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_set<long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_set<long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_set<unsigned long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_set<unsigned long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_set<long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_set<long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_set<unsigned long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_set<unsigned long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_set<std::string>& object,
    const RepresentationType rt);

template <> std::string als::utilities::to_string(const std::unordered_set<float>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_set<float>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::unordered_set<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::unordered_set<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::unordered_set<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::unordered_set<double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_set<double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::unordered_set<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::unordered_set<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::unordered_set<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::unordered_set<long double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_set<long double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::unordered_set<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::unordered_set<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::unordered_set<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);


template <> std::string als::utilities::to_string(const std::unordered_multiset<char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_multiset<char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_multiset<unsigned char>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_multiset<unsigned char>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_multiset<short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_multiset<short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_multiset<unsigned short int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_multiset<unsigned short int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_multiset<int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_multiset<int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_multiset<unsigned int>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_multiset<unsigned int>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_multiset<long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_multiset<long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_multiset<unsigned long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_multiset<unsigned long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_multiset<long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_multiset<long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_multiset<unsigned long long>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_multiset<unsigned long long>& object,
    const RepresentationType rt, const bool show_sign);

template <> std::string als::utilities::to_string(const std::unordered_multiset<std::string>& object,
    const RepresentationType rt);

template <> std::string als::utilities::to_string(const std::unordered_multiset<float>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_multiset<float>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::unordered_multiset<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::unordered_multiset<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::unordered_multiset<float>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::unordered_multiset<double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_multiset<double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::unordered_multiset<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::unordered_multiset<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::unordered_multiset<double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

template <> std::string als::utilities::to_string(const std::unordered_multiset<long double>& object,
    const RepresentationType rt);
template <> std::string als::utilities::to_string(const std::unordered_multiset<long double>& object,
    const RepresentationType rt, const unsigned int precision);
template <> std::string als::utilities::to_string(const std::unordered_multiset<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign);
template <> std::string als::utilities::to_string(const std::unordered_multiset<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf);
template <> std::string als::utilities::to_string(const std::unordered_multiset<long double>& object,
    const RepresentationType rt, const unsigned int precision,
    const bool show_sign, const int lim_inf, const int lim_sup);

#endif // ALS_UTILITIES_TO_STRING_CPP
