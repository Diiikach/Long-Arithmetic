#include "longnumber.hpp"

namespace longnumber {
   LongNumber LongNumber::sum(const LongNumber& other) const {
        int max_n = std::max(integer.size(), other.integer.size());
        int max_m = std::max(fraction.size(), other.fraction.size());
        std::vector<bit> new_integer(max_n), new_fraction(max_m);
        bool next_digit = false;
        for (int i = max_m - 1 ; i >= 0; i--) {
            int cur = 0;
            if (i < fraction.size()) {
                cur += fraction[i];
            }
            if (i < other.fraction.size()) {
                cur += other.fraction[i];
            }
            cur += next_digit;
            new_fraction[i] = cur & 1;
            next_digit = cur >> 1;
        }
        for (int i = 0; i < max_n; i++) {
            int cur = 0;
            if (i < integer.size()) {
                cur += integer[i];
            }
            if (i < other.integer.size()) {
                cur += other.integer[i];
            }
            cur += next_digit;
            new_integer[i] = cur & 1;
            next_digit = cur >> 1;
        }
        if (next_digit) {
            new_integer.push_back(1);
        }
        return LongNumber(new_integer, new_fraction, sign);
}

LongNumber LongNumber::dif(const LongNumber& other) const {
    // other LongNumber must be less than this by the absolute value
    int max_n = std::max(integer.size(), other.integer.size());
    int max_m = std::max(fraction.size(), other.fraction.size());
    std::vector<bit> new_integer(max_n), new_fraction(max_m);
    bool next_digit = false;
    for (int i = max_m - 1 ; i >= 0; i--) {
        int cur = 0;
        if (i < fraction.size()) {
            cur += fraction[i];
        }
        if (i < other.fraction.size()) {
            cur -= other.fraction[i];
        }
        if (cur == -1) {
            new_fraction[i] = 1 - next_digit;
            next_digit = true;
        } else if (cur == 1) {
            new_fraction[i] = cur - next_digit;
            next_digit = false;
        } else if (cur == 0) {
            if (next_digit) {
                new_fraction[i] = 1;
            } else {
                new_fraction[i] = 0;
            }
        }
    }
    for (int i = 0; i < max_n; i++) {
        int cur = 0;
        if (i < integer.size()) {
            cur += integer[i];
        }
        if (i < other.integer.size()) {
            cur -= other.integer[i];
        }
        if (cur == -1) {
            new_integer[i] = 1 - next_digit;
            next_digit = true;
        } else if (cur == 1) {
            new_integer[i] = cur - next_digit;
            next_digit = false;
        } else if (cur == 0) {
            if (next_digit) {
                new_integer[i] = 1;
            } else {
                new_integer[i] = 0;
            }
        }
    }
    return {new_integer, new_fraction, sign};
}

LongNumber LongNumber::left_shift() const {
    std::vector<bit> new_integer(integer.size() + 1);
    std::vector<bit> new_fraction(fraction.size());
    for (int i = new_integer.size() - 1; i > 0; i--) {
        new_integer[i] = integer[i - 1];
    }
    new_integer[0] = (fraction.size() > 0 ? fraction[0] : 0);
    for (int i = fraction.size() - 2; i >= 0; i--) {
        new_fraction[i] = fraction[i + 1];
    }
    return LongNumber(new_integer, new_fraction, sign);
}

LongNumber LongNumber::right_shift() const {
    std::vector<bit> new_integer(integer.size());
    std::vector<bit> new_fraction(fraction.size() + 1);
    for (int i = new_fraction.size() - 1; i > 0; i--) {
        new_fraction[i] = fraction[i - 1];
    }
    new_fraction[0] = (integer.size() > 0 ? integer[0] : 0);
    for (int i = integer.size() - 2; i >= 0; i--) {
        new_integer[i] = integer[i + 1];
    }
    return LongNumber(new_integer, new_fraction, sign);
}
} // namespace LongNumber