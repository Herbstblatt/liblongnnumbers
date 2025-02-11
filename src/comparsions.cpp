#include "../include/longnumbers.hpp"

/* Comparsions */

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
    
    if (auto cmp = (first->number.size() - first->precision) <=> (second->number.size() - second->precision); cmp != 0) {
        return cmp;
    }
    
    int this_size = static_cast<int>(first->number.size());
    int other_size = static_cast<int>(second->number.size());
    
    for (int i = this_size, j = other_size; std::max(i, j) >= 0; i--, j--) {
        bool this_val;
        if (i >= 0) this_val = first->number[i];
        else this_val = 0;

        bool other_val;
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