#include "doctest.h"
#include "longnumbers.hpp"
#include <vector>

TEST_CASE("Test constructors") {
    SUBCASE("Zero") {
        LongNumber num1 {};
        LongNumber num2  { static_cast<int>(0) };
        LongNumber num3  { static_cast<long long>(0) };
        LongNumber num4 { static_cast<double>(0) };
        LongNumber num5 { static_cast<long double>(0) };
        LongNumber num6 = 0.0_longnum;
        std::vector numbers { num1, num2, num3, num4, num5, num6 };
        for (int i = 0; i < 6; i++) {
            for (int j = i; j < 6; j++) {
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
        for (int i = 0; i < 5; i++) {
            for (int j = i; j < 5; j++) {
                CHECK_EQ(numbers[i], numbers[j]);
            }
        }
    }

    SUBCASE("Fractional numbers") {
        LongNumber num1 { static_cast<double>(2.5) };
        LongNumber num2 { static_cast<long double>(2.5) };
        LongNumber num3 = 2.5_longnum;
        std::vector numbers { num1, num2, num3 };
        for (int i = 0; i < 3; i++) {
            for (int j = i; j < 3; j++) {
                CHECK_EQ(numbers[i], numbers[j]);
            }
        }
    }
}