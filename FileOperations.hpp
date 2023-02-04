/** 
 * @file FileOperations.hpp
 * @brief This file contains a useful interface to read and write from files.
 * @author Andrés Laín Sanclemente
 * @version 0.8.0
 * @date 27th January 2022 
 * 
 * This file provides functions @a write_to_file and @a read_from_file .
 * @a write_to_file follows the following syntax:
 * write_to_file(const reference to the object you want to save, FILE pointer to your file)
 * @a read_from_file follows the following syntax:
 * read_from_file(reference to the object, FILE pointer to your file)
 * 
 * Currently, we offer support for basic C types, strings, complex numbers,
 * std:array, std::vector, std::deque, std::forward_list, std::list.
 * 
 * In order to define @a write_to_file and @a read_from_file for your
 * custom objects, it suffices to implement the public methods
 * write_to_file(FILE* file) and read_from_file(FILE* file).
 * 
 * @todo Add support for other standard containers!
 */


#ifndef ALS_UTILITIES_FILE_OPERATIONS_HPP
#define ALS_UTILITIES_FILE_OPERATIONS_HPP

#include <cstdio>

#include <string>
#include <complex>
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

namespace als::utilities
{
    // Writing operations.
    void inline write_to_file(const signed char& val, FILE* file)
    {
        fwrite(&val, sizeof(signed char), 1, file);
    }

    void inline write_to_file(const char& val, FILE* file)
    {
        fwrite(&val, sizeof(char), 1, file);
    }

    void inline write_to_file(const unsigned char& val, FILE* file)
    {
        fwrite(&val, sizeof(unsigned char), 1, file);
    }

    void inline write_to_file(const short int& val, FILE* file)
    {
        fwrite(&val, sizeof(short int), 1, file);
    }

    void inline write_to_file(const unsigned short int& val, FILE* file)
    {
        fwrite(&val, sizeof(unsigned short int), 1, file);
    }

    void inline write_to_file(const int& val, FILE* file)
    {
        fwrite(&val, sizeof(int), 1, file);
    }

    void inline write_to_file(const unsigned int& val, FILE* file)
    {
        fwrite(&val, sizeof(unsigned int), 1, file);
    }

    void inline write_to_file(const long int& val, FILE* file)
    {
        fwrite(&val, sizeof(long int), 1, file);
    }

    void inline write_to_file(const unsigned long int& val, FILE* file)
    {
        fwrite(&val, sizeof(unsigned long int), 1, file);
    }

    void inline write_to_file(const long long int& val, FILE* file)
    {
        fwrite(&val, sizeof(long long int), 1, file);
    }

    void inline write_to_file(const unsigned long long int& val, FILE* file)
    {
        fwrite(&val, sizeof(unsigned long long int), 1, file);
    }

    void inline write_to_file(const float& val, FILE* file)
    {
        fwrite(&val, sizeof(float), 1, file);
    }

    void inline write_to_file(const double& val, FILE* file)
    {
        fwrite(&val, sizeof(double), 1, file);
    }

    void inline write_to_file(const long double& val, FILE* file)
    {
        fwrite(&val, sizeof(long double), 1, file);
    }

    void inline write_to_file(const wchar_t& val, FILE* file)
    {
        fwrite(&val, sizeof(wchar_t), 1, file);
    }

    void inline write_to_file(const bool& val, FILE* file)
    {
        write_to_file((char) val, file);
    }

    void inline write_to_file(const std::string& str, FILE* file)
    {
        write_to_file((unsigned int)str.size(), file);
        fwrite(str.c_str(), sizeof(char), str.size()+1, file);
    }

    template <class K>
    void inline write_to_file(const std::complex<K>& z, FILE* file)
    {
        write_to_file(z.real(), file);
        write_to_file(z.imag(), file);
    }

    template <class T, size_t N>
    void inline write_to_file(const std::array<T, N>& object, FILE* file)
    {
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            write_to_file(*it, file);
        }
    }

    template <class T>
    void inline write_to_file(const std::vector<T>& object, FILE* file)
    {
        write_to_file((unsigned int)object.size(), file);
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            write_to_file(*it, file);
        }
    }

    template <class T>
    void inline write_to_file(const std::deque<T>& object, FILE* file)
    {
        write_to_file((unsigned int)object.size(), file);
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            write_to_file(*it, file);
        }
    }

    template <class T>
    void inline write_to_file(const std::forward_list<T>& object, FILE* file)
    {
        write_to_file((unsigned int)object.size(), file);
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            write_to_file(*it, file);
        }
    }

    template <class T>
    void inline write_to_file(const std::list<T>& object, FILE* file)
    {
        write_to_file((unsigned int)object.size(), file);
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            write_to_file(*it, file);
        }
    }

    template <class T>
    void inline write_to_file(const T& object, FILE* file)
    {
        object.write_to_file(file);
    }


    // Reading operations.
    void inline read_from_file(char& val, FILE* file)
    {
        fread(&val, sizeof(char), 1, file);
    }

    void inline read_from_file(signed char& val, FILE* file)
    {
        fread(&val, sizeof(signed char), 1, file);
    }

    void inline read_from_file(unsigned char& val, FILE* file)
    {
        fread(&val, sizeof(unsigned char), 1, file);
    }

    void inline read_from_file(short int& val, FILE* file)
    {
        fread(&val, sizeof(short int), 1, file);
    }

    void inline read_from_file(unsigned short int& val, FILE* file)
    {
        fread(&val, sizeof(unsigned short int), 1, file);
    }

    void inline read_from_file(int& val, FILE* file)
    {
        fread(&val, sizeof(int), 1, file);
    }

    void inline read_from_file(unsigned int& val, FILE* file)
    {
        fread(&val, sizeof(unsigned int), 1, file);
    }

    void inline read_from_file(long int& val, FILE* file)
    {
        fread(&val, sizeof(long int), 1, file);
    }

    void inline read_from_file(unsigned long int& val, FILE* file)
    {
        fread(&val, sizeof(unsigned long int), 1, file);
    }

    void inline read_from_file(long long int& val, FILE* file)
    {
        fread(&val, sizeof(long long int), 1, file);
    }

    void inline read_from_file(unsigned long long int& val, FILE* file)
    {
        fread(&val, sizeof(unsigned long long int), 1, file);
    }

    void inline read_from_file(float& val, FILE* file)
    {
        fread(&val, sizeof(float), 1, file);
    }

    void inline read_from_file(double& val, FILE* file)
    {
        fread(&val, sizeof(double), 1, file);
    }

    void inline read_from_file(long double& val, FILE* file)
    {
        fread(&val, sizeof(long double), 1, file);
    }

    void inline read_from_file(wchar_t& val, FILE* file)
    {
        fread(&val, sizeof(wchar_t), 1, file);
    }

    void inline read_from_file(bool& val, FILE* file)
    {
        char temp;
        read_from_file(temp, file);
        val = temp;
    }

    void inline read_from_file(std::string& val, FILE* file)
    {
        unsigned int N;
        read_from_file(N, file);
        char* str = new char[N];
        for (unsigned int i = 0; i < N; i++)
        {
            fread(str + i, sizeof(char), 1, file);
        }
        val = std::string(str);
        delete[] str;
    }

    template <class K>
    void inline read_from_file(std::complex<K>& z, FILE* file)
    {
        K x, y;
        read_from_file(x, file);
        read_from_file(y, file);
        z = std::complex<K>(x, y);
    }

    template <class T, size_t N>
    void inline read_from_file(std::array<T, N>& object, FILE* file)
    {
        object = std::array<T, N>();
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            read_from_file(*it, file);
        }
    }

    template <class T>
    void inline read_from_file(std::vector<T>& object, FILE* file)
    {
        unsigned int size;
        read_from_file(size, file);
        object = std::vector<T>(size);
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            read_from_file(*it, file);
        }
    }

    template <class T>
    void inline read_from_file(std::deque<T>& object, FILE* file)
    {
        unsigned int size;
        read_from_file(size, file);
        object = std::deque<T>(size);
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            read_from_file(*it, file);
        }
    }

    template <class T>
    void inline read_from_file(std::forward_list<T>& object, FILE* file)
    {
        unsigned int size;
        read_from_file(size, file);
        object = std::forward_list<T>(size);
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            read_from_file(*it, file);
        }
    }

    template <class T>
    void inline read_from_file(std::list<T>& object, FILE* file)
    {
        unsigned int size;
        read_from_file(size, file);
        object = std::list<T>(size);
        for (auto it = object.begin() + 1; it != object.end(); ++it)
        {
            read_from_file(*it, file);
        }
    }

    template <class T>
    void inline read_from_file(T& object, FILE* file)
    {
        object.read_from_file(file);
    }
}

#endif // ALS_UTILITIES_FILE_OPERATIONS_HPP