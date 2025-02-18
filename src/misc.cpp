#include "../include/longnumbers.hpp"

void LongNumber::_remove_leading_zeros() {
    while (this->number.size() - this->precision > 1 && this->number.back() == 0) {
        this->number.pop_back();
    }
}