#pragma once

#ifndef LONGNUMBERS_H
#define LONGNUMBERS_H

#include <compare>
#include <vector>
#include <cstddef>
#include <string>

class LongNumber {
public:
    LongNumber();
    LongNumber(int number, int precision = 10);
    LongNumber(long long number, int precision = 10);
    LongNumber(double number, int precision = 10);
    LongNumber(long double number, int precision = 10);
    LongNumber(const LongNumber&) = default;
    ~LongNumber() = default;

    LongNumber operator-() const;
    LongNumber operator+(const LongNumber& other) const;
    LongNumber operator-(const LongNumber& other) const;
    LongNumber operator*(const LongNumber& other) const;
    LongNumber operator/(const LongNumber& other) const;

    std::string to_string(int precision = -1) const;
    friend std::ostream& operator<<(std::ostream& out, const LongNumber& num);
    
    std::strong_ordering operator<=>(const LongNumber& other) const;
    bool operator==(const LongNumber& other) const;

    int get_precision() const;

private:
    int precision;
    std::vector<bool> number;
    bool is_positive = true;

    LongNumber(std::vector<bool> number, int precision, bool is_positive = true) 
        : precision { precision }
        , number { number }
        , is_positive { is_positive }
    {}

    LongNumber _add(const LongNumber& other) const;
    LongNumber _substract(const LongNumber& other) const;

    void _shl();
    void _shr();

    void _remove_leading_zeros();
    std::vector<int> _to_vec_integral() const;
};

inline LongNumber operator""_longnum(long double number);

#endif