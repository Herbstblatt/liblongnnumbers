#include "longnumbers.hpp"

namespace longnumbers {

    int LongNumber::get_precision() const {
        return this->precision;
    }

    void LongNumber::_remove_leading_zeros() {
        while (this->number.size() - this->precision > 1 && this->number.back() == 0) {
            this->number.pop_back();
        }
    }

}