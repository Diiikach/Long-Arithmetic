#include <unistd.h>
#include "longnumber.hpp"

#define KARATSUBA_LIMIT 50

namespace longnumber {
    bool LongNumber::operator==(const LongNumber &other) const {
        return sign == other.sign && this->abs_eq(other);
    }

    bool LongNumber::operator!=(const LongNumber &other) const {
        return !(*this == other);
    }

    bool LongNumber::operator<(const LongNumber& other) const {
        if (sign == POS && other.sign == NEG) {
            return false;
        }
        if (sign == NEG && other.sign == POS) {
            return true;
        }
        if (sign == NEG) {
            return other.abs_less(*this);
        }
        return this->abs_less(other);
    }

    bool LongNumber::operator>(const LongNumber& other) const {
        return !(*this < other || *this == other);
    }

    LongNumber LongNumber::operator+(const LongNumber& other) const {
        if (sign != other.sign) {
            if (this->abs_less(other)) {
                return other.dif(*this);
            }
            return this->dif(other);
        }
        return this->sum(other);
    }

    LongNumber LongNumber::operator-(const LongNumber& other) const {
        if (sign == other.sign) {
            if (this->abs_less(other)) {
                return -other.dif(*this);
            }
            return this->dif(other);
        }
        return this->sum(other);
    }

    LongNumber LongNumber::operator*(const LongNumber& other) const {
        // if (std::max(this->integer.size() + this->fraction.size(), other.integer.size() + other.fraction.size()) > KARATSUBA_LIMIT) {
        //     std::vector<bit> ab, cd;
        //     for (int i = this->fraction.size() - 1; i >= 0; i--) {
        //         ab.push_back(this->fraction[i]);
        //     }
        //     for (int i = 0; i < this->integer.size(); i++) {
        //         ab.push_back(this->integer[i]);
        //     }
        //     for (int i = other.fraction.size() - 1; i >= 0; i--) {
        //         cd.push_back(other.fraction[i]);
        //     }
        //     for (int i = 0; i < other.integer.size(); i++) {
        //         cd.push_back(other.integer[i]);
        //     }
        // }
        LongNumber cur_deg = *this;
        LongNumber res(0);
        int start_pos = -1;
        for (int i = other.fraction.size() - 1; i >= 0; i--) {
            if (other.fraction[i] == 1) {
                start_pos = i;
                break;
            }
        }
        for (int i = 0; i < start_pos + 1; i++) {
            cur_deg = cur_deg.right_shift();
        }
        for (int i = start_pos; i >= 0; i--) {
            if (other.fraction[i] == 1) {
                res += cur_deg;
            }
            cur_deg = cur_deg.left_shift();
        }
        for (int i = 0; i < other.integer.size(); i++) {
            if (other.integer[i] == 1) {
                res += cur_deg;
            }
            cur_deg = cur_deg.left_shift();
        }
        if (sign == other.sign) {
            res.sign = POS;
        } else {
            res.sign = NEG;
        }
        res.remove_zeros();
        return res;
    }

    LongNumber LongNumber::operator/(const LongNumber& other) const {
        LongNumber right_bound = other;
        LongNumber left_bound = other;
        if (other.abs_less(LongNumber(1))) {
            while ((right_bound * other).abs_less(*this)) {
                right_bound = right_bound.left_shift();
            }
            right_bound = right_bound.left_shift();
        } else {
            right_bound = *this;
            left_bound = LongNumber(0);
        }
        LongNumber abs_cur = this->abs();
        for (int _ = 0; _ < 344; _++) {
            LongNumber mid = (left_bound + right_bound).right_shift();
            if ((mid * other).abs() < abs_cur) {
                left_bound = mid;
            } else {
                right_bound = mid;
            }
        }
        if (sign != other.sign)
            left_bound.sign = NEG;
        else
            left_bound.sign = POS;
        left_bound.remove_zeros();
        return left_bound;
    }

    LongNumber& LongNumber::operator+=(const LongNumber& other) {
        *this = *this + other;
        return *this;
    }

    LongNumber LongNumber::operator-() const {
        LongNumber new_num = *this;
        if (this->sign == NEG) {
            new_num.sign = POS;
        } else {
            new_num.sign = NEG;
        }
        return new_num;
    }

    LongNumber LongNumber::abs() const {
        LongNumber new_number = *this;
        new_number.sign = POS;
        return new_number;
    }

    LongNumber& LongNumber::operator-=(const LongNumber& other) {
        *this = *this - other;
        return *this;
    }

    LongNumber& LongNumber::operator/=(const LongNumber& other) {
        *this = *this / other;
        return *this;
    }

    LongNumber& LongNumber::operator*=(const LongNumber& other) {
        *this = *this * other;
        return *this;
    }
} // namespace LongNumber