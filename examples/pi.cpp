#include "longnumbers.hpp"
#include <iostream>
#include <iomanip>

longnumbers::LongNumber calc_pi(int prec) {
    using longnumbers::LongNumber;
    
    LongNumber pi { 0, prec };
    LongNumber n0 { 1, prec };
    LongNumber n { 16, prec };

    LongNumber a0 { 4, prec };
    LongNumber b0 { 2, prec };
    LongNumber c0 { 1, prec };
    LongNumber d0 { 1, prec };

    LongNumber a { 1, prec };
    LongNumber b { 4, prec };
    LongNumber c { 5, prec };
    LongNumber d { 6, prec };

    LongNumber dif { 8, prec };

    for (int k = 0; k < prec; k++) {
        pi = pi + n0 * (a0 / a - b0 / b - c0 / c - d0 / d);
        n0 = n0 / n;
        a = a + dif;
        b = b + dif;
        c = c + dif;
        d = d + dif;
    }

    return pi;
}

int main(int argc, char* argv[]) {
    int prec{};
    if (argc <= 1) {
        prec = 100;
    } else {
        std::istringstream in(argv[1]);
        if (!(in >> prec && in.eof())) {
            std::cerr << "Need to pass a valid integer" << std::endl;
            return 1;
        }
    }
    std::cout << calc_pi(std::max(4 * prec, 32)).to_string(prec, true) << std::endl;
    return 0;
}