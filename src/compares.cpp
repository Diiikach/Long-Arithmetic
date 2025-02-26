#include "longnumber.hpp"

namespace longnumber {
    bool LongNumber::abs_less(const LongNumber& other) const {
        // compares absolute values of tho long numbers like |this| < |other|
        int si1 = integer.size(), si2 = other.integer.size(); // size  of integer array 1, 2
        int sf1 = fraction.size(), sf2 = other.fraction.size(); // size of fraction array 1, 2
        int max_n = std::max(si1, si2);
        int max_m = std::max(sf1, sf2);

        for (int i = max_n - 1; i >= 0; i--) {
            char first_val = i < si1 ? integer[i] : 0, second_val = i < si2 ? other.integer[i] : 0;
            if (first_val < second_val) {
                return true;
            }
            if (first_val > second_val) {
                return false;
            }
        }

        for (int i = 0; i < max_m; i++) {
            char first_val = i < sf1 ? fraction[i] : 0, second_val = i < sf2 ? other.fraction[i] : 0;
            if (first_val < second_val) {
                return true;
            }
            if (first_val > second_val) {
                return false;
            }
        }
        return false;
    }

    bool LongNumber::abs_eq(const LongNumber& other) const {
        int si1 = integer.size(), si2 = other.integer.size(); // size  of integer array 1, 2
        int sf1 = fraction.size(), sf2 = other.fraction.size(); // size of fraction array 1, 2
        int max_n = std::max(si1, si2);
        int max_m = std::max(sf1, sf2);

        for (int i = max_n - 1; i >= 0; i--) {
            char first_val = i < si1 ? integer[i] : 0, second_val = i < si2 ? other.integer[i] : 0;
            if (first_val != second_val) {
                return false;
            }
        }

        for (int i = 0; i < max_m; i++) {
            char first_val = i < sf1 ? fraction[i] : 0, second_val = i < sf2 ? other.fraction[i] : 0;
            if (first_val != second_val) {
                return true;
            }
        }
        return true;
    }
} // LongNumber