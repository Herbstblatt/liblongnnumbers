#include "../include/longnumbers.hpp"
#include "helpers.hpp"

/* Ariphmetics */

LongNumber LongNumber::_add(const LongNumber& other) const {
    std::vector<char> num = this->number;
    std::vector<char> other_num = other.number;
    if (this->precision < other.precision) std::swap(num, other_num);
    
    int prec_diff = abs(other.precision - this->precision);
    int to_add = std::max(0, static_cast<int>(other_num.size()) + prec_diff - static_cast<int>(num.size()));
    num.resize(num.size() + to_add, 0);

    perform_action_carrying<char>(num, [&](char t, int ind) {
        if (ind < prec_diff) {
            return static_cast<int>(t);
        }
        int other_val = 0;
        if (ind - prec_diff < other_num.size()) {
            other_val = static_cast<int>(other_num[ind - prec_diff]);
        }
        return static_cast<int>(t) + other_val;
    }, 2);
    
    auto result = LongNumber {num, std::max(this->precision, other.precision), true};
    return result;
}

LongNumber LongNumber::_substract(const LongNumber& other) const {
    /* Invariant: it is guaranteed that this > other, otherwise UB */
    /* This function is hardcoded and would need to be noticeably rewritten upon (potential) base change */
    /* It also contains a lot of repetition. Hence, it is my least favourite function of all in this project */

    const std::vector<char>& num = this->number;
    const std::vector<char>& other_num = other.number;
    size_t result_size;
    if (this->precision <= other.precision) {
        result_size = num.size() - this->precision + other.precision;
    } else {
        result_size = num.size();
    }
    std::vector<char> result(result_size, 0);
    
    int prec_diff = abs(other.precision - this->precision);
    if (this->precision >= other.precision) {
        bool taken_prev = false;
        for (int i = 0; i < result_size; i++) {
            if (i < prec_diff) {
                result[i] = num[i];
                continue;
            }

            int curr_other_num;
            if (i - prec_diff >= other_num.size()) {
                curr_other_num = 0;
            } else {
                curr_other_num = other_num[i - prec_diff];
            }

            result[i] = num[i];
            if (taken_prev && num[i] == 1) {
                result[i] = 0;
                taken_prev = false;
            } else if (taken_prev && num[i] == 0) {
                result[i] = 1;
            }
            if (result[i] < curr_other_num) {
                result[i] = 1;
                taken_prev = true;
            } else {
                result[i] = result[i] - curr_other_num;
            }
        }
        LongNumber num_result = {result, std::max(this->precision, other.precision), true};
        num_result._remove_leading_zeros();
        return num_result;
    } else {
        bool taken_prev = false;
        for (int i = 0; i < result_size; i++) {
            int curr_num;
            if (i < prec_diff) {
                curr_num = 0;
            } else {
                curr_num = num[i - prec_diff];
            }

            int curr_other_num;
            if (i >= other_num.size()) {
                curr_other_num = 0;
            } else {
                curr_other_num = other_num[i];
            }

            result[i] = curr_num;
            if (taken_prev && curr_num == 1) {
                curr_num = 0;
                taken_prev = false;
            } else if (taken_prev && curr_num == 0) {
                curr_num = 1;
            }
            if (curr_num < curr_other_num) {
                result[i] = 1;
                taken_prev = true;
            } else {
                result[i] = curr_num - curr_other_num;
            }
        }
        LongNumber num_result = {result, std::max(this->precision, other.precision), true};
        num_result._remove_leading_zeros();
        return num_result;
    }
}

LongNumber LongNumber::operator-() const {
    LongNumber new_number { *this };
    new_number.is_positive = !new_number.is_positive;
    return new_number;
}

LongNumber abs(LongNumber number) {
    number.is_positive = true;
    return number;
}

LongNumber LongNumber::operator+(const LongNumber& other) const {
    if (!this->is_positive && !other.is_positive) {
        LongNumber result = this->_add(other);
        result.is_positive = false;
        return result;
    } else if (!this->is_positive) {
        return other - (-*this);
    } else if (!other.is_positive) {
        return *this - (-other);
    }
    return this->_add(other);
}

LongNumber LongNumber::operator-(const LongNumber& other) const {
    if (!other.is_positive && !this->is_positive) {
        return (-other) - (-*this);
    }
    if (!other.is_positive) {
        LongNumber result = this->_add(other);
        return result;
    }
    if (!this->is_positive) {
        LongNumber result = this->_add(other);
        result.is_positive = false;
        return result;
    }

    auto cmp = *this <=> other;
    if (cmp == std::strong_ordering::less) {
        LongNumber result = other._substract(*this);
        result.is_positive = false;
        return result;
    } else if (cmp == std::strong_ordering::greater) {
        return this->_substract(other);
    } else {
        return LongNumber { 0, std::max(this->precision, other.precision) };
    }
}

LongNumber LongNumber::operator*(const LongNumber& other) const {
    /* For multiplication, it is reasonable to multiply without regard to the comma, and set prec = prec1 + prec2 then */
    /* However, it's required that prec = max(prec1, prec2), losing precision */
    
    int result_len = static_cast<int>(other.number.size()) + static_cast<int>(this->number.size()) - 1;
    int prec_diff = this->precision + other.precision - std::max(this->precision, other.precision);
    result_len = result_len - prec_diff;

    std::vector<char> result(result_len, 0);
    for (int i = 0; i < other.number.size(); i++) {
        if (other.number[i] == 0) continue;
        perform_action_carrying<char>(result, [&](char t, int ind) {
            int curr_ind = ind + prec_diff - i;
            if (curr_ind < 0 || curr_ind >= this->number.size()) {
                return static_cast<int>(t);
            } else {
                return static_cast<int>(t) + this->number[curr_ind];
            }
        }, 2);
    }

    return LongNumber { 
        result, 
        std::max(this->precision, other.precision), 
        !static_cast<char>(this->is_positive ^ other.is_positive)
    };
}

void LongNumber::_shl() {
    this->number.insert(this->number.begin(), 0);
}

void LongNumber::_shr() {
    this->precision++;
}

LongNumber LongNumber::operator/(const LongNumber& other) const {
    int target_precision = std::max(this->precision, other.precision);
    int target_len = this->number.size() + target_precision - std::max(0, this->precision - other.precision);
    std::vector<char> vec_padded(target_len, 0);
    std::copy_backward(this->number.begin(), this->number.end(), vec_padded.end());
    
    LongNumber remainder = LongNumber { std::vector<char>(target_len, 0), target_precision, true };
    LongNumber quotient =  LongNumber { std::vector<char>(target_len, 0), target_precision, true };
    LongNumber other_abs = abs(other);
    other_abs.precision = 0;
    int curr_pos = target_len;
    remainder.precision = target_len;
    for (int i = target_len - 1; i >= 0; --i) {
        curr_pos--;
        remainder.precision--;
        remainder.number[curr_pos] = vec_padded[i];
        if (remainder >= other_abs) {
            remainder = remainder._substract(other_abs);
            remainder.number.resize(target_len);
            if (target_precision > this->precision) {
                quotient.number[i - this->precision + target_precision] = 1;
            } else {
                quotient.number[i] = 1;
            }
        }
    }
    quotient._remove_leading_zeros();
    quotient.is_positive = !static_cast<bool>(this->is_positive ^ other.is_positive);
    return quotient;
}