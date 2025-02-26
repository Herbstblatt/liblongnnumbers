#include "longnumbers.hpp"

namespace longnumbers {

    std::strong_ordering LongNumber::operator<=>(const LongNumber& other) const {
        if (!this->is_positive && other.is_positive) {
            return std::strong_ordering::less;
        } else if (this->is_positive && !other.is_positive) {
            return std::strong_ordering::greater;
        }
        
        const LongNumber* first = this;
        const LongNumber* second = &other;
        if (!this->is_positive && !other.is_positive) {
            std::swap(first, second);
        }

        int first_non_zero = static_cast<int>(first->number.size()) - 1;
        while (first_non_zero >= 0 && first->number[first_non_zero] == 0) {
            first_non_zero--;
        }
        
        int second_non_zero = static_cast<int>(second->number.size()) - 1;
        while (second_non_zero >= 0 && second->number[second_non_zero] == 0) {
            second_non_zero--;
        }
        
        if (first_non_zero < 0 && second_non_zero < 0) return std::strong_ordering::equal;
        if (first_non_zero < 0) {
            if (other.is_positive) return std::strong_ordering::less;
            else return std::strong_ordering::greater;
        } else if (second_non_zero < 0) {
            if (this->is_positive) return std::strong_ordering::greater;
            return std::strong_ordering::less;
        }
        
        if (auto cmp = (first_non_zero - first->precision) <=> (second_non_zero - second->precision); cmp != 0) {
            return cmp;
        }
        
        for (int i = first_non_zero, j = second_non_zero; std::max(i, j) >= 0; i--, j--) {
            char this_val;
            if (i >= 0) this_val = first->number[i];
            else this_val = 0;

            char other_val;
            if (j >= 0) other_val = second->number[j];
            else other_val = 0;

            if (auto cmp = this_val <=> other_val; cmp != 0) {
                return cmp;
            }
        }
        return std::strong_ordering::equal;
    }

    bool LongNumber::operator==(const LongNumber& other) const {
        return (*this <=> other) == std::strong_ordering::equal;
    }

}