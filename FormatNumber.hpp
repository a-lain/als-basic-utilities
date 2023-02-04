/** 
 * @file FormatNumber.hpp
 * @brief This file contains useful functions to deal with formatting
 * numbers as strings.
 * @author Andrés Laín Sanclemente
 * @version 0.8.0
 * @date 27th January 2023
 * 
 */

#ifndef ALS_UTILITIES_FORMAT_NUMBER_HPP
#define ALS_UTILITIES_FORMAT_NUMBER_HPP

#include <string>
#include <cmath>

namespace als::utilities
{
    /**
     * @brief Returns the position of the most significant digit of x.
     * 
     * 
     * For example, 3.34 -> 1, 0 -> 0, 0.79 -> -1.
    */
    int position_of_most_significant_digit(const long double x);

    /**
     * @brief Returns 10^exponent as a long double. It is a fast implemenation
     * because it looks up the value in a table.
     * 
     * @param exponent 
     * @return long double 
     */
    long double long_double_pow10(const unsigned int exponent);

    /**
     * @brief Returns 10^exponent as an unsigned long long int. It is a fast implemenation
     * because it looks up the value in a table.
     * 
     * @param exponent 
     * @return unsigned long long int 
     */
    unsigned long long int long_pow10(const unsigned int exponent);

    /**
     * @brief Rounds a number to a given precision.
     * 
     * @param x 
     * @param precision 
     * @return long double 
     */
    long double round_to_precision(const double x, const unsigned int precision);

    /**
     * @brief Rounds up a number to a given precesion.
     * 
     * @param x 
     * @param precision number of significant digits of the output.
     * @return long double 
     */
    long double ceil_to_precision(const double x, const unsigned int precision);
    
    /**
     * @brief Rounds down a number to a given precision.
     * 
     * @param x 
     * @param precision number of significant digits of the output.
     * @return long double 
     */
    long double floor_to_precision(const double x, const unsigned int precision);

    /**
     * @brief {-1,0,1} sign function.
     * 
     * @tparam T 
     * @param val 
     * @return int 
     */
    template <typename T> int inline sgn(T val)
    {
        return (T(0) < val) - (val < T(0));
    }
}

#endif // ALS_UTILITIES_FORMAT_NUMBER_HPP