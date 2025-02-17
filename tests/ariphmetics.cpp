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

        CHECK(abs(frac_pos - (-frac_neg)) < eps);
    }
}

TEST_CASE("Test division") {
    SUBCASE("Whole numbers") {
        LongNumber whole_big_prec_2 { 20, 2 };
        LongNumber whole_big_prec_10 { 20, 2 };

        LongNumber whole_small_prec_2 { 20, 2 };
        LongNumber whole_small_prec_10 { 20, 2 };

        LongNumber ans { 5 };

        CHECK_EQ(whole_big_prec_2 / whole_small_prec_2, ans);
        CHECK_EQ(whole_big_prec_2 / whole_small_prec_10, ans);
        CHECK_EQ(whole_big_prec_10 / whole_small_prec_2, ans);

        CHECK_EQ(whole_big_prec_2 / (-whole_small_prec_2), -ans);
        CHECK_EQ((-whole_big_prec_2) / whole_small_prec_2, -ans);
        CHECK_EQ((-whole_big_prec_2) / (-whole_small_prec_2), ans);
    }

    SUBCASE("Fractional numbers") {
        LongNumber whole_big_prec_10 { 2, 10 };
        LongNumber whole_big_prec_32 { 2, 32 };
        
        LongNumber frac_small_prec_10 { 0.25, 10 };
        LongNumber frac_small_prec_32 { 0.25, 32 };

        LongNumber frac_not_exact_prec_10 { 0.2, 10 };
        LongNumber frac_not_exact_prec_32 { 0.2, 32 };

        LongNumber frac_big_prec_10 { 1.25, 10 };
        LongNumber frac_big_prec_32 { 1.25, 10 };
        
        LongNumber eps { 0.0001 };

        CHECK(abs(frac_small_prec_10 / whole_big_prec_10 - 0.125_longnum) < eps);
        CHECK(abs(frac_small_prec_32 / whole_big_prec_10 - 0.125_longnum) < eps);
        CHECK(abs(frac_small_prec_10 / whole_big_prec_32 - 0.125_longnum) < eps);

        CHECK(abs(frac_not_exact_prec_10 / whole_big_prec_10 - 0.1_longnum) < eps);
        CHECK(abs(frac_not_exact_prec_32 / whole_big_prec_10 - 0.125_longnum) < eps);
        CHECK(abs(frac_not_exact_prec_10 / whole_big_prec_32 - 0.125_longnum) < eps);

        CHECK(abs(frac_not_exact_prec_10 / frac_not_exact_prec_10 - 1) < eps);
        CHECK(abs(frac_not_exact_prec_32 / frac_not_exact_prec_10 - 1) < eps);
        CHECK(abs(frac_not_exact_prec_10 / frac_not_exact_prec_32 - 1) < eps);
        
        CHECK(abs(frac_big_prec_10 / whole_big_prec_10 - 0.625_longnum) < eps);
        CHECK(abs(frac_big_prec_32 / whole_big_prec_10 - 0.625_longnum) < eps);
        CHECK(abs(frac_big_prec_10 / whole_big_prec_32 - 0.625_longnum) < eps);
        
        CHECK(abs(frac_big_prec_10 / frac_not_exact_prec_10 - 6.25_longnum) < eps);
        CHECK(abs(frac_big_prec_32 / frac_not_exact_prec_10 - 6.25_longnum) < eps);
        CHECK(abs(frac_big_prec_10 / frac_not_exact_prec_32 - 6.25_longnum) < eps);
    }
}