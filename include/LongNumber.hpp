#include <iostream>
#include <vector>

using bit = char;

#ifndef LN_IN
#define LN_IN


namespace LongNumber {
    enum Sign {
        NEG,
        POS,
    };

    class LongNumber {
    public:
        unsigned rounding_pos = 10;
        unsigned ac {50};
        Sign sign = POS; // default value for non-negative numbers
        std::vector<bit> integer;
        std::vector<bit> fraction;

        LongNumber(std::vector<bit> integer, std::vector<bit> other, Sign s, unsigned ac = 40);

        explicit LongNumber(long double num);

        bool operator<(const LongNumber& other) const;
        bool operator>(const LongNumber& other) const;
        bool operator==(const LongNumber& other) const;
        bool operator!=(const LongNumber& other) const;

        LongNumber operator-() const;
        LongNumber operator+(const LongNumber& other) const;
        LongNumber operator-(const LongNumber& other) const;
        LongNumber operator*(const LongNumber& other) const;
        LongNumber operator/(const LongNumber& other) const;

        LongNumber& operator+=(const LongNumber& other);
        LongNumber& operator-=(const LongNumber& other);
        LongNumber& operator*=(const LongNumber& other);
        LongNumber& operator/=(const LongNumber& other);
        [[nodiscard]] LongNumber abs() const;

        [[nodiscard]] std::string get_decimal() const;
        [[nodiscard]] std::string get_binary() const;

    private:
        static std::vector<char> divide_decimal_by_two(std::vector<char>& num);
        static std::vector<char> multiply_decimal_by_two(std::vector<char>& num);
        static std::vector<char> sum_two_decimal(std::vector<char>& num1, std::vector<char>& num2, int dir);

        [[nodiscard]] bool abs_less(const LongNumber& other) const;
        [[nodiscard]] bool abs_eq(const LongNumber& other) const;

        [[nodiscard]] LongNumber sum(const LongNumber& other) const;
        [[nodiscard]] LongNumber dif(const LongNumber& other) const;
        [[nodiscard]] LongNumber left_shift() const;
        [[nodiscard]] LongNumber right_shift() const;

        void remove_zeros();

    };

    inline LongNumber operator""_longnum(long double number) {
        return LongNumber(number);
    }
} // namespace LongNumber
#endif