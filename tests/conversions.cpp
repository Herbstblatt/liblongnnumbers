#include "doctest.h"
#include "longnumbers.hpp"
#include <vector>


TEST_CASE("Test constructors") {
    using namespace longnumbers;
    using namespace longnumbers::literals;

    SUBCASE("Zero") {
        LongNumber num1 {};
        LongNumber num2  { static_cast<int>(0) };
        LongNumber num3  { static_cast<long long>(0) };
        LongNumber num4 { static_cast<double>(0) };
        LongNumber num5 { static_cast<long double>(0) };
        LongNumber num6 = 0.0_longnum;
        
        std::vector numbers { num1, num2, num3, num4, num5, num6 };
        for (int i = 0; i < numbers.size(); i++) {
            for (int j = i; j < numbers.size(); j++) {
                CHECK_EQ(numbers[i], numbers[j]);
            }
        }
    }

    SUBCASE("Whole numbers") {
        LongNumber num1  { static_cast<int>(100) };
        LongNumber num2  { static_cast<long long>(100) };
        LongNumber num3 { static_cast<double>(100) };
        LongNumber num4 { static_cast<long double>(100) };
        LongNumber num5 = 100.0_longnum;

        std::vector numbers { num1, num2, num3, num4, num5 };
        for (int i = 0; i < numbers.size(); i++) {
            for (int j = i; j < numbers.size(); j++) {
                CHECK_EQ(numbers[i], numbers[j]);
            }
        }
    }

    SUBCASE("Fractional numbers") {
        LongNumber num1 { static_cast<double>(2.5) };
        LongNumber num2 { static_cast<long double>(2.5) };
        LongNumber num3 = 2.5_longnum;

        std::vector numbers { num1, num2, num3 };
        for (int i = 0; i < numbers.size(); i++) {
            for (int j = i; j < numbers.size(); j++) {
                CHECK_EQ(numbers[i], numbers[j]);
            }
        }
    }
}