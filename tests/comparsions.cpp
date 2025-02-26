#include "doctest.h"
#include "longnumbers.hpp"


TEST_CASE("Long number comparsion") {
    using namespace longnumbers;
    using namespace longnumbers::literals;
    LongNumber whole_small_prec_2 { 5, 2 };
    LongNumber whole_small_prec_10 { 5, 10 };

    LongNumber whole_big_prec_2 { 100, 2 };
    LongNumber whole_big_prec_10 { 100, 10 };

    LongNumber frac_small_prec_5 { 0.25, 5 };
    LongNumber frac_small_prec_10 { 0.25, 10 };
    
    LongNumber frac_big_prec_5 { 0.75, 5 };
    LongNumber frac_big_prec_10 { 0.75, 10 };

    LongNumber frac_not_exact_prec_5 {0.2, 5};
    LongNumber frac_not_exact_prec_10 {0.2, 10};

    LongNumber zero_prec_5 {0, 2};
    LongNumber zero_prec_10 {0, 10};

    LongNumber very_small { 0.00001 };

    SUBCASE("Compare equal whole numbers") {
        CHECK(whole_small_prec_2 == whole_small_prec_2);
        CHECK(whole_small_prec_2 == whole_small_prec_10);
    }
    
    SUBCASE("Compare whole numbers") {
        CHECK_MESSAGE(whole_small_prec_2 < whole_big_prec_2, "Same precision");
        CHECK_MESSAGE(whole_small_prec_10 < whole_big_prec_10, "Same precision");

        CHECK_MESSAGE(whole_small_prec_2 < whole_big_prec_10, "Different precision");
        CHECK_MESSAGE(whole_small_prec_10 < whole_big_prec_2, "Different precision");
    }

    SUBCASE("Compare fractional numbers") {
        CHECK_MESSAGE(frac_small_prec_5 < frac_big_prec_5, "Same precision");
        CHECK_MESSAGE(frac_small_prec_10 < frac_big_prec_10, "Same precision");

        CHECK_MESSAGE(frac_small_prec_5 < frac_big_prec_10, "Different precision");
        CHECK_MESSAGE(frac_small_prec_10 < frac_big_prec_5, "Different precision");

        CHECK_MESSAGE(frac_not_exact_prec_5 < frac_big_prec_5, "Unexact, same precision");
        CHECK_MESSAGE(frac_not_exact_prec_5 < frac_big_prec_10, "Unexact, different precision");
        CHECK_MESSAGE(frac_not_exact_prec_10 < frac_big_prec_5, "Unexact, different precision");
    }

    SUBCASE("Compare with zero") {
        CHECK(zero_prec_5 < whole_small_prec_10);
        CHECK(zero_prec_5 < frac_small_prec_5);

        CHECK(zero_prec_5 < frac_small_prec_5);
        CHECK(zero_prec_5 < frac_small_prec_10);
        CHECK(zero_prec_10 < frac_small_prec_5);

        CHECK(zero_prec_5 < frac_not_exact_prec_5);
        CHECK(zero_prec_5 < frac_not_exact_prec_10);
        CHECK(zero_prec_10 < frac_not_exact_prec_5);

        CHECK(zero_prec_5 < very_small);
        CHECK(zero_prec_10 < very_small);
    }

}