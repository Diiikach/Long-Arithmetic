#include <iostream>
#include "longnumber.hpp"
#include <string>
#include <chrono>

using namespace longnumber;

class TimerGuard {
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::ostream& outt;
    std::string msg;

public:
    TimerGuard(std::string message, std::ostream& out) : outt(out), msg(message) {
        this->start_time = std::chrono::high_resolution_clock::now();
    }

    ~TimerGuard() {
        auto duration = std::chrono::high_resolution_clock::now() - start_time;
        outt << msg << " " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()/1000 << "s" << std::endl;
    }
};

LongNumber get_pi(int ac) {
    std::ios_base::sync_with_stdio(false);
    LongNumber::rounding_pos = ac;
    int N1{}, N2{};
    if (ac <= 10) {
        N1 = 20;
        N2 = 15;
    } else if (ac <= 40) {
        N1 = 40;
        N2 = 20;
    }
    else {
        N1 = 73;
        N2 = 21;
    }
    LongNumber left(0), right(0);
    left.ac = 344, right.ac = 344;
    LongNumber deg = LongNumber(1) / LongNumber(5);
    LongNumber x = deg;
    LongNumber deg2 = deg * deg;
    LongNumber denominator = 1.0_longnum;
    const LongNumber two = 2.0_longnum;
    for (int i = 1; i <= N1; ++i) {
        if (i % 2 == 0)
            left -= x / denominator;
        else
            left += x / denominator;
        x *= deg2;
        denominator += two;
    }
    deg = LongNumber(1) / LongNumber(239);
    x = deg;
    deg2 = deg * deg;
    denominator = 1.0_longnum;
    for (int i = 1; i <= N2; i++) {
        if (i % 2 == 0)
            right -= x / denominator;
        else
            right += x / denominator;
        x *= deg2;
        denominator += two;
    }
    return (LongNumber(16) * left - LongNumber(4) * right);
}

int main() {
    std::cout << "Введите количество десятичных знаков после запятой" << std::endl;
    unsigned ac;
    std::cin >> ac;
    auto vb = TimerGuard("Calc pi number", std::cout);
    std::cout << get_pi(ac).get_decimal() << std::endl;
}