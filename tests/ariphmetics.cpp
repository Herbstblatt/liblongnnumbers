#include <doctest.h>
#include "longnumbers.hpp"

TEST_CASE("Test negation") {
    SUBCASE("Whole numbers") {
        LongNumber whole_pos { 5 };
        LongNumber whole_neg { -5 };
        CHECK(whole_pos == -whole_neg);
        CHECK(-whole_pos == whole_neg);
    }
    SUBCASE("Frac numbers") {
        LongNumber frac_pos { 5.2 };
        LongNumber frac_neg { -5.2 };

        LongNumber eps { 0.0001 };

        CHECK(abs(frac_pos - (-frac_neg)) == 0);
    }
}