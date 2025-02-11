#include "../include/longnumbers.hpp"
#include "helpers.hpp"
#include <string>

/* Conversions */

std::vector<int> LongNumber::_to_vec_integral() const {
    /* Convert int part */
    std::vector<int> int_result {0};
    for (int i = this->number.size(); i >= this->precision; i--) {
        perform_action_carrying<int>(int_result, [&](int t, int idx){ return t * 2; });
        perform_action_carrying<int>(int_result, [&](int t, int idx){ 
            if (idx == 0) return t + this->number[i]; 
            else return t;
        });
        //print_vector(int_result);
    }
    
    return int_result;
}

std::string LongNumber::to_string(int precision) const {
    auto int_result { this->_to_vec_integral() };

    /* Convert double part */
    LongNumber frac{};
    int fst_one_pos = 0;
    for (int i = 0; i < this->precision; i++) {
        if (this->number[i] == 1 && fst_one_pos == 0) {
            fst_one_pos = 1;
        }
        if (this->number[i] == 1) frac = frac + binpow(2, i - fst_one_pos);
    }

    frac = frac * binpow(5, this->precision - fst_one_pos);

    auto db_result = frac._to_vec_integral();
    size_t prev_size = db_result.size();

    //print_vector(db_result);

    perform_action_carrying<int>(db_result, [&](int t, int ind) {
        if (ind == this->precision - precision - 1) {
            if (t >= 5) return 10;
            else return 0;
        }
        return t;
    });

    //print_vector(db_result);

    if (db_result.size() > prev_size) {
        /* No double part, increment int part to 1 */
        perform_action_carrying<int>(int_result, [&](int t, int ind) {
            if (ind == 0) return t + 1;
            return t;
        });
    }

    std::string result{};
    if (!this->is_positive) result.push_back('-');
    for (auto it = int_result.rbegin(); it != int_result.rend(); it++) {
        result.push_back(*it + '0');
    }
    result.push_back('.');
    for (int i = prev_size - 1; i >= 0; i--) {
        if (prev_size - i > precision) break;
        result.push_back(db_result[i] + '0');
    }

    return result;
}

std::ostream& operator<<(std::ostream& out, const LongNumber& num) {
    out << num.to_string(out.precision());
    return out;
}