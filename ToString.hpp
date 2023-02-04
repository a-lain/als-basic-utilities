/** 
 * @file ToString.hpp
 * @brief This file contains a useful interface to obtain a string
 * representation of an object.
 * @author Andrés Laín Sanclemente
 * @version 0.8.0
 * @date 27th January 2023 
 * 
 * This file provides a function @a to_string .
 * 
 * Currently, we offer support for basic C types, strings, complex numbers,
 * std:array, std::vector, std::deque, std::forward_list, std::list,
 * std::set, std::multiset, std::map, std::multimap, std::unordered_set,
 * std::unordered_multiset, std::unordered_map, std::unordered_multimap.
 * 
 * In order to define @a to_string for your custom objects
 * it suffices to implement the public method 
 * to_string(const T& object, const const RepresentationType rt).
 * You can add extra arguments to your function if you wish.
 * 
 * @todo Add support for other standard containers!
 */

#ifndef ALS_UTILITIES_TO_STRING_HPP
#define ALS_UTILITIES_TO_STRING_HPP

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
#include <iostream>
#include <cmath>

namespace als::utilities
{

    /**
     * @brief Enum class that is used to determine whether a latex
     * or a plain representation of an object should be returned.
     * 
     */
    enum class RepresentationType
    {
        PLAIN,
        LATEX
    };

    /**
     * @brief Returns a string representation of val.
     * 
     * @param val 
     * @param rt determines if a latex or a plain representation
     * of the object is returned.
     * @param show_sign whether to show sign even if number is positive.
     * Take into account that if a number is negative, its sign is always displayed.
     * @return std::string 
     */
    std::string to_string(const unsigned long long val,
        const RepresentationType rt = RepresentationType::PLAIN,
        const bool show_sign = false);

    /**
     * @brief Returns a string representation of val.
     * 
     * @param val 
     * @param rt determines if a latex or a plain representation
     * of the object is returned.
     * @param show_sign whether to show sign even if number is positive.
     * Take into account that if a number is negative, its sign is always displayed.
     * @return std::string 
     */
    std::string to_string(const long long val,
        const RepresentationType rt = RepresentationType::PLAIN,
        const bool show_sign = false);

    /**
     * @brief Returns a string representation of the number.
     * 
     * @param x the number.
     * @param rt determines whether a latex or a plain representation is returned.
     * @param precision number of digits displayed. Must be less than or equal to 19.
     * Note that this is OK since a double can only hold 15 digits of precision.
     * @param show_sign controlls whether the sign of the number is shown even if x
     * is positive. Take into account that if a number is negative, its sign is
     * always displayed.
     * @param lim_inf If x is smaller then 10^(lim_inf), then scientific notation is used
     * to represent the number.
     * @param lim_sup If x is bigger then 10^(lim_sup), then scientific notation is used
     * to represent the number.
     * @return std::string 
     */
    std::string to_string(long double x,
        const RepresentationType rt = RepresentationType::PLAIN,
        const unsigned int precision = 3, const bool show_sign = false,
        const int lim_inf = -3, const int lim_sup = 3);

    std::string to_string(const std::string& str,
        const RepresentationType rt = RepresentationType::PLAIN);

    std::string to_string(const char* const str,
        const RepresentationType rt = RepresentationType::PLAIN);

    std::string to_string(const bool& val,
        const RepresentationType rt = RepresentationType::PLAIN);

    std::string to_string(const RepresentationType val,
        const RepresentationType rt = RepresentationType::PLAIN);

    std::string to_string(const signed char& val,
        const RepresentationType rt = RepresentationType::PLAIN,
        const bool show_sign = false);

    std::string to_string(const char& val,
        const RepresentationType rt = RepresentationType::PLAIN);

    std::string to_string(const unsigned char& val,
        const RepresentationType rt = RepresentationType::PLAIN,
        const bool show_sign = false);

    std::string to_string(const short int& val,
        const RepresentationType rt = RepresentationType::PLAIN,
        const bool show_sign = false);

    std::string to_string(const unsigned short int& val,
        const RepresentationType rt = RepresentationType::PLAIN,
        const bool show_sign = false);

    std::string to_string(const int& val,
        const RepresentationType rt = RepresentationType::PLAIN,
        const bool show_sign = false);

    std::string to_string(const unsigned int& val,
        const RepresentationType rt = RepresentationType::PLAIN,
        const bool show_sign = false);

    std::string to_string(const long int& val,
        const RepresentationType rt = RepresentationType::PLAIN,
        const bool show_sign = false);
    
    std::string to_string(const unsigned long int& val,
        const RepresentationType rt = RepresentationType::PLAIN,
        const bool show_sign = false);

    std::string to_string(float x,
        const RepresentationType rt = RepresentationType::PLAIN,
        const unsigned int precision = 3, const bool show_sign = false,
        const int lim_inf = -3, const int lim_sup = 3);

    std::string to_string(double x,
        const RepresentationType rt = RepresentationType::PLAIN,
        const unsigned int precision = 3, const bool show_sign = false,
        const int lim_inf = -3, const int lim_sup = 3);

    // BEGIN TEMPLATE FUNCTION DECLARATIONS.
    
    template <class K, typename... Args>
    std::string inline to_string(const std::complex<K>& z,
        const RepresentationType rt,
        Args... args);
    template <class T, size_t N, typename... Args>
    std::string inline to_string(const std::array<T, N>& object,
        const RepresentationType rt,
        Args... args);
    template <class T, typename... Args>
    std::string inline to_string(const std::vector<T>& object,
        const RepresentationType rt,
        Args... args);
    template <class T, typename... Args>
    std::string inline to_string(const std::deque<T>& object,
        const RepresentationType rt,
        Args... args);
    template <class T, typename... Args>
    std::string inline to_string(const std::forward_list<T>& object,
        const RepresentationType rt,
        Args... args);
    template <class T, typename... Args>
    std::string inline to_string(const std::list<T>& object,
        const RepresentationType rt,
        Args... args);
    template <class T, typename... Args>
    std::string inline to_string(const std::set<T>& object,
        const RepresentationType rt,
        Args... args);
    template <class T, typename... Args>
    std::string inline to_string(const std::multiset<T>& object,
        const RepresentationType rt,
        Args... args);
    template <class T, typename... Args>
    std::string inline to_string(const std::unordered_set<T>& object,
        const RepresentationType rt,
        Args... args);
    template <class T, typename... Args>
    std::string inline to_string(const std::unordered_multiset<T>& object,
        const RepresentationType rt,
        Args... args);
    template <class K, class T, typename... Args>
    std::string inline to_string(const std::map<K, T>& object,
        const RepresentationType rt,
        Args... args);
    template <class K, class T, typename... Args>
    std::string inline to_string(const std::multimap<K, T>& object,
        const RepresentationType rt,
        Args... args);
    template <class K, class T, typename... Args>
    std::string inline to_string(const std::unordered_map<K, T>& object,
        const RepresentationType rt,
        Args... args);
    template <class K, class T, typename... Args>
    std::string inline to_string(const std::unordered_multimap<K, T>& object,
        const RepresentationType rt,
        Args... args);
    template <class T>
    std::string inline to_string(const T* ptr, const RepresentationType rt);
    template<class T, class... Args>
    std::string inline to_string(const T& object, const RepresentationType rt,
        Args... args);
    template<class T, class... Args>
    std::string inline to_plain(const T& object, Args... args);
    template<class T, class... Args>
    std::string inline to_latex(const T& object, Args... args);

    // END TEMPLATE FUNCTION DECLARATIONS.


    // BEGIN TEMPLATE FUNCTION IMPLEMENTATIONS.

    template <class K, typename... Args>
    std::string inline to_string(const std::complex<K>& z,
        const RepresentationType rt,
        Args... args)
    {
        std::string i = 
            rt == als::utilities::RepresentationType::PLAIN ? "i" : "\\mathrm{i}";    
        if (z.imag() < 0)
        {
            return als::utilities::to_string(z.real(), rt, args...) + " - " +
                als::utilities::to_string(-z.imag(), rt, args...) + i;
        }
        else
        {
            return als::utilities::to_string(z.real(), rt, args...) + " + " +
                als::utilities::to_string(z.imag(), rt, args...) + i;
        }
    }

    template <class T, size_t N, typename... Args>
    std::string inline to_string(const std::array<T, N>& object,
        const RepresentationType rt,
        Args... args)
    {
        std::string pre = (rt == RepresentationType::LATEX) ? "\\left[" : "[";
        std::string post = (rt == RepresentationType::LATEX) ? "\\right]" : "]";

        std::string text = "";
        if (object.size() >= 1)
        {
            text += als::utilities::to_string(*object.begin(), rt, args...);
        }
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            text += ", " + als::utilities::to_string(*it, rt, args...);
        }

        return pre + text + post;
    }

    template <class T, typename... Args>
    std::string inline to_string(const std::vector<T>& object,
        const RepresentationType rt,
        Args... args)
    {
        std::string pre = (rt == RepresentationType::LATEX) ? "\\left[" : "[";
        std::string post = (rt == RepresentationType::LATEX) ? "\\right]" : "]";

        std::string text = "";
        if (object.size() >= 1)
        {
            text += als::utilities::to_string(*object.begin(), rt, args...);
        }
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            text += ", " + als::utilities::to_string(*it, rt, args...);
        }

        return pre + text + post;
    }

    template <class T, typename... Args>
    std::string inline to_string(const std::deque<T>& object,
        const RepresentationType rt,
        Args... args)
    {
        std::string pre = (rt == RepresentationType::LATEX) ? "\\left[" : "[";
        std::string post = (rt == RepresentationType::LATEX) ? "\\right]" : "]";

        std::string text = "";
        if (object.size() >= 1)
        {
            text += als::utilities::to_string(*object.begin(), rt, args...);
        }
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            text += ", " + als::utilities::to_string(*it, rt, args...);
        }

        return pre + text + post;
    }

    template <class T, typename... Args>
    std::string inline to_string(const std::forward_list<T>& object,
        const RepresentationType rt,
        Args... args)
    {
        std::string pre = (rt == RepresentationType::LATEX) ? "\\left[" : "[";
        std::string post = (rt == RepresentationType::LATEX) ? "\\right]" : "]";

        std::string text = "";
        if (object.size() >= 1)
        {
            text += als::utilities::to_string(*object.begin(), rt, args...);
        }
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            text += ", " + als::utilities::to_string(*it, rt, args...);
        }

        return pre + text + post;
    }

    template <class T, typename... Args>
    std::string inline to_string(const std::list<T>& object,
        const RepresentationType rt,
        Args... args)
    {
        std::string pre = (rt == RepresentationType::LATEX) ? "\\left[" : "[";
        std::string post = (rt == RepresentationType::LATEX) ? "\\right]" : "]";

        std::string text = "";
        if (object.size() >= 1)
        {
            text += als::utilities::to_string(*object.begin(), rt, args...);
        }
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            text += ", " + als::utilities::to_string(*it, rt, args...);
        }

        return pre + text + post;
    }

    template <class T, typename... Args>
    std::string inline to_string(const std::set<T>& object,
        const RepresentationType rt,
        Args... args)
    {
        std::string pre = (rt == RepresentationType::LATEX) ? "\\left\\{" : "{";
        std::string post = (rt == RepresentationType::LATEX) ? "\\right\\}" : "}";

        std::string text = "";
        if (object.size() >= 1)
        {
            text += als::utilities::to_string(*object.begin(), rt, args...);
        }
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            text += ", " + als::utilities::to_string(*it, rt, args...);
        }

        return pre + text + post;
    }

    template <class T, typename... Args>
    std::string inline to_string(const std::multiset<T>& object,
        const RepresentationType rt,
        Args... args)
    {
        std::string pre = (rt == RepresentationType::LATEX) ? "\\left\\{" : "{";
        std::string post = (rt == RepresentationType::LATEX) ? "\\right\\}" : "}";

        std::string text = "";
        if (object.size() >= 1)
        {
            text += als::utilities::to_string(*object.begin(), rt, args...);
        }
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            text += ", " + als::utilities::to_string(*it, rt, args...);
        }

        return pre + text + post;
    }

    template <class T, typename... Args>
    std::string inline to_string(const std::unordered_set<T>& object,
        const RepresentationType rt,
        Args... args)
    {
        std::string pre = (rt == RepresentationType::LATEX) ? "\\left\\{" : "{";
        std::string post = (rt == RepresentationType::LATEX) ? "\\right\\}" : "}";

        std::string text = "";
        if (object.size() >= 1)
        {
            text += als::utilities::to_string(*object.begin(), rt, args...);
        }
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            text += ", " + als::utilities::to_string(*it, rt, args...);
        }

        return pre + text + post;
    }

    template <class T, typename... Args>
    std::string inline to_string(const std::unordered_multiset<T>& object,
        const RepresentationType rt,
        Args... args)
    {
        std::string pre = (rt == RepresentationType::LATEX) ? "\\left\\{" : "{";
        std::string post = (rt == RepresentationType::LATEX) ? "\\right\\}" : "}";

        std::string text = "";
        if (object.size() >= 1)
        {
            text += als::utilities::to_string(*object.begin(), rt, args...);
        }
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            text += ", " + als::utilities::to_string(*it, rt, args...);
        }

        return pre + text + post;
    }

    /**
     * @brief Returns a string representation of the map.
     * @warning Currently, extra arguments are only passed to the als::utilities::to_string
     * function of the types, not of the keys.
    */
    template <class K, class T, typename... Args>
    std::string inline to_string(const std::map<K, T>& object,
        const RepresentationType rt,
        Args... args)
    {
        std::string pre = (rt == RepresentationType::LATEX) ? "\\left\\{" : "{";
        std::string post = (rt == RepresentationType::LATEX) ? "\\right\\}" : "}";

        std::string text = "";
        if (object.size() >= 1)
        {
            text += als::utilities::to_string(object.begin()->first, rt) + ": "
                + als::utilities::to_string(object.begin()->second, rt, args...);
        }
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            text += ", " + als::utilities::to_string(it->first, rt) + ": "
                + als::utilities::to_string(it->second, rt, args...);
        }

        return pre + text + post;
    }

    /**
     * @brief Returns a string representation of the map.
     * @warning Currently, extra arguments are only passed to the als::utilities::to_string
     * function of the types, not of the keys.
    */
    template <class K, class T, typename... Args>
    std::string inline to_string(const std::multimap<K, T>& object,
        const RepresentationType rt,
        Args... args)
    {
        std::string pre = (rt == RepresentationType::LATEX) ? "\\left\\{" : "{";
        std::string post = (rt == RepresentationType::LATEX) ? "\\right\\}" : "}";

        std::string text = "";
        if (object.size() >= 1)
        {
            text += als::utilities::to_string(object.begin()->first, rt) + ": "
                + als::utilities::to_string(object.begin()->second, rt, args...);
        }
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            text += ", " + als::utilities::to_string(it->first, rt) + ": "
                + als::utilities::to_string(it->second, rt, args...);
        }

        return pre + text + post;
    }

    /**
     * @brief Returns a string representation of the map.
     * @warning Currently, extra arguments are only passed to the als::utilities::to_string
     * function of the types, not of the keys.
    */
    template <class K, class T, typename... Args>
    std::string inline to_string(const std::unordered_map<K, T>& object,
        const RepresentationType rt,
        Args... args)
    {
        std::string pre = (rt == RepresentationType::LATEX) ? "\\left\\{" : "{";
        std::string post = (rt == RepresentationType::LATEX) ? "\\right\\}" : "}";

        std::string text = "";
        if (object.size() >= 1)
        {
            text += als::utilities::to_string(object.begin()->first, rt) + ": "
                + als::utilities::to_string(object.begin()->second, rt, args...);
        }
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            text += ", " + als::utilities::to_string(it->first, rt) + ": "
                + als::utilities::to_string(it->second, rt, args...);
        }

        return pre + text + post;
    }

    /**
     * @brief Returns a string representation of the map.
     * @warning Currently, extra arguments are only passed to the als::utilities::to_string
     * function of the types, not of the keys.
    */
    template <class K, class T, typename... Args>
    std::string inline to_string(const std::unordered_multimap<K, T>& object,
        const RepresentationType rt,
        Args... args)
    {
        std::string pre = (rt == RepresentationType::LATEX) ? "\\left\\{" : "{";
        std::string post = (rt == RepresentationType::LATEX) ? "\\right\\}" : "}";

        std::string text = "";
        if (object.size() >= 1)
        {
            text += als::utilities::to_string(object.begin()->first, rt) + ": "
                + als::utilities::to_string(object.begin()->second, rt, args...);
        }
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            text += ", " + als::utilities::to_string(it->first, rt) + ": "
                + als::utilities::to_string(it->second, rt, args...);
        }

        return pre + text + post;
    }


    // Support for pointers.
    template <class T>
    std::string inline to_string(const T* ptr, const RepresentationType rt)
    {
        std::stringstream text;
        text << ptr;
        return als::utilities::to_string(text.str(), rt);
    }

    // General to_string implementation.
    template<class T, class... Args>
    std::string inline to_string(const T& object, const RepresentationType rt,
        Args... args)
    {
        return object.to_string(rt, args...);
    }

    // Definition of to_plain and to_latex.
    template<class T, class... Args>
    std::string inline to_plain(const T& object, Args... args)
    {
        return als::utilities::to_string(object, RepresentationType::PLAIN, args...);
    }

    template<class T, class... Args>
    std::string inline to_latex(const T& object, Args... args)
    {
        return als::utilities::to_string(object, RepresentationType::LATEX, args...);
    }

    // END TEMPLATE FUNCTION IMPLEMENTATIONS.
}

#endif // ALS_UTILITIES_TO_STRING_HPP
