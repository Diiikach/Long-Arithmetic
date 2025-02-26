#include "longnumber.hpp"
#include <iomanip>


namespace longnumber {
    LongNumber::LongNumber(std::vector<bit> integer, std::vector<bit> fraction, const Sign s = POS, unsigned ac) {
        this->integer = std::move(integer);
        this->fraction = std::move(fraction);
        this->sign = s;
        this->ac = ac;
    }

    LongNumber::LongNumber(long double num) {
        if (num < 0)
            sign = NEG;
        else {
            sign = POS;
        }
        unsigned long long left = std::abs(num);
        for (int i = 0; i < 63; i++) {
            if (((unsigned long long)  1 << i) & left) {
                integer.push_back(1);
            } else {
                integer.push_back(0);
            }
        }
        while (integer.size() && integer.back() == 0) {
            integer.pop_back();
        }
        if (num < 0) {
            num *= -1;
        }
        long double right = num - left;
        long double cur = 0.5;
        int ac_k = ac; // coefficient of accurancy
        while (right > 0 && ac_k--) {
            if (right >= cur) {
                right -= cur;
                fraction.push_back(1);
            } else {
                fraction.push_back(0);
            }
            cur /= 2;
        }
    }

    void LongNumber::remove_zeros() {
        // removes external zeros
        while (!integer.empty() && integer.back() == static_cast<bit>(0)) {
            integer.pop_back();
        }
        while (!fraction.empty() && fraction.back() == static_cast<bit>(0) && fraction.size() > ac) {
            fraction.pop_back();
        }
    }

} // namespace LongNumber