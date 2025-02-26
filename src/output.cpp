#include "longnumber.hpp"

namespace longnumber {
        std::string LongNumber::get_binary() const{
        std::string result;
        for (int i = integer.size() - 1; i >= 0; i--) {
            result += integer[i] + '0';
        }
        result += '.';
        for (int i = 0; i < fraction.size(); i++) {
            result += fraction[i] + '0';
        }
        return result;
    }

    std::vector<char> LongNumber::divide_decimal_by_two(std::vector<char> &num) {
        std::vector<char> new_num(num.size() + 1);
        bool next = false;
        for (int i = 0; i < num.size(); i++) {
            char cur = num[i] + (next * 10);
            new_num[i] = cur / 2;
            next =  ((next) * 10 + cur) % 2;
        }
        if (next) {
            new_num[num.size()] = 5;;
        }
        return new_num;
    }

    std::vector<char> LongNumber::multiply_decimal_by_two(std::vector<char> &num) {
        // num in reversed form of a number. Human-readable = 321, this = 123
        std::vector<char> new_num(num.size());
        bool next = false;
        for (int i = 0; i < num.size(); i++) {
            new_num[i] = (next + (num[i] * 2)) % 10;
            next = (num[i] * 2) / 10;
        }
        if (next) {
            new_num.push_back(1);
        }
        while (new_num.back() == 0) {
            new_num.pop_back();
        }
        return new_num;
    }

    std::vector<char> LongNumber::sum_two_decimal(std::vector<char> &num1, std::vector<char>& num2, int dir = 1) {
        // dir = -1 means that num1 and num2 are fractional
        std::vector<char> new_num(std::max(num1.size(), num2.size()));
        int start{};
        int end{};
        int next{};
        if (dir == 1) {
            start = 0;
            end = std::max(num1.size(), num2.size());
        } else {
            start = std::max(num1.size(), num2.size()) - 1;
            end = -1;
        }
        for (int i = start; i != end; i += dir) {
            int fval{};
            int sval{};
            if (i < num1.size()) {
                fval = num1[i];
            }
            if (i < num2.size()) {
                sval = num2[i];
            }
            new_num[i] = (sval + fval + next) % 10;
            next = (sval + fval + next) / 10;
        }
        if (next) {
            // This statement can be produced when num1 and num2 are integer parts
            new_num.push_back(1);
        }
        return new_num;
    }

    std::string LongNumber::get_decimal() const {
        // fractional part
        std::vector<char> cur_deg = {5};
        std::vector<char> right = {0}, left = {0};
        for (int i = 0; i < fraction.size(); i++) {
            if (fraction[i] == 1) {
                right = sum_two_decimal(right, cur_deg, -1);
            }
            cur_deg = divide_decimal_by_two(cur_deg);
        }
        cur_deg = {1};
        for (int i = 0; i < integer.size(); i++) {
            if (integer[i] == 1) {
                left = sum_two_decimal(left, cur_deg);
            }
            cur_deg = multiply_decimal_by_two(cur_deg);
        }
        while (right.size() >= rounding_pos + 1) {
            right.pop_back();
        }
        bool plus = (right.size() > rounding_pos ? (right[rounding_pos] >= 5) : 0);
        if (plus) {
            right.pop_back();
        }
        for (int i = std::min((signed) rounding_pos - 1, (signed)fraction.size() - 2); i >= 0 && plus; i--) {
            right[i] += plus;
            plus = right[i] / 10;
            right[i] %= 10;
        }
        for (int i = 0; i < left.size(); i++) {
            left[i] += plus;
            plus = left[i] / 10;
            left[i] %= 10;
        }
        std::string result;
        if (sign == NEG)
            result += '-';
        for (int i = left.size() - 1; i >= 0; i--) {
            result += left[i] + '0';
        }
        result += '.';
        for (int i = 0; i < right.size(); i++) {
            result += right[i] + '0';
        }
        return result;
    }
}