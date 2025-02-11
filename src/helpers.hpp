#pragma once

#ifndef LONGNUMBER_HELPERS_H
#define LONGNUMBER_HELPERS_H

#include <functional>
#include <iostream>
#include "../include/longnumbers.hpp"

template <typename T>
void perform_action_carrying(std::vector<T>& vec, const std::function<int(T, int)>& fn, int carry_mod = 10) {
    static_assert(std::is_convertible_v<T, int>);
    static_assert(std::is_convertible_v<int, T>);

    int carry { 0 };
    for (int j = 0; j < vec.size(); j++) {
        int curr = static_cast<int>(vec[j]);
        curr = fn(curr, j);
        curr += carry;
        carry = 0;
        if (curr >= carry_mod) {
            carry = curr / carry_mod;
            curr = curr % carry_mod;
        }
        vec[j] = static_cast<T>(curr);
    }
    while (carry > 0) {
        vec.push_back(static_cast<T>(carry % carry_mod));
        carry /= carry_mod;
    }
}

template <typename T>
void print_vector(const std::vector<T>& vec) {
    for (auto s: vec) {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}

inline LongNumber binpow(LongNumber n, int k) {
    if (k == 0) {
        return LongNumber { 1 };
    }
    if (k == 1) {
        return n;
    }
    LongNumber interm = binpow(n, k / 2);
    if (k % 2 == 1) {
        return interm * interm * n;
    } else {
        return interm * interm;
    }
}

#endif