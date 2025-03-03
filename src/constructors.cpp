#include "longnumbers.hpp"
#include <cmath>

namespace longnumbers {

    LongNumber::LongNumber() 
        : LongNumber { 0LL }
    {}

    LongNumber::LongNumber(int number, int precision) 
        : LongNumber { static_cast<long long>(number), precision }
    {}

    LongNumber::LongNumber(long long number, int precision)
        : precision { precision }
        , number { std::vector<char>(precision, 0) }
        , is_positive { number >= 0 }
    {
        number = std::abs(number);
        if (number == 0) {
            this->number.push_back(0);
            return;
        }
        while (number != 0) {
            this->number.push_back(number % 2);
            number /= 2;
        }
    }

    LongNumber::LongNumber(double number, int precision) 
        : LongNumber { static_cast<long double>(number), precision }
    {}

    LongNumber::LongNumber(long double number, int precision)
        : LongNumber { static_cast<long long>(number), precision } 
    {
        number = std::abs(number);
        double integer;
        double part = std::modf(number, &integer);
        for (int i = 0; i < precision; i++) {
            part *= 2;
            double curr;
            part = std::modf(part, &curr);
            this->number[precision - i - 1] = static_cast<int>(curr);
        }
    }

    namespace literals {
        LongNumber operator""_longnum(long double number) {
            return LongNumber { number };
        };
    }

}