#include <iostream>
#include <random>

class DiceBase {
public:
    virtual unsigned roll() = 0;
    virtual ~DiceBase() = default;
};

class Dice : public DiceBase {
public:
    Dice(unsigned max, unsigned seed) : dstr(1, max), reng(seed) {}

    unsigned roll() override {
        return dstr(reng);
    }

private:
    std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
};

class ThreeDicePool : public DiceBase {
public:
    ThreeDicePool(unsigned max, unsigned seed_1, unsigned seed_2, unsigned seed_3)
        : d1(max, seed_1), d2(max, seed_2), d3(max, seed_3) {}

    unsigned roll() override {
        return d1.roll() + d2.roll() + d3.roll();
    }

private:
    Dice d1, d2, d3;
};

double expected_value(DiceBase &d, unsigned number_of_rolls = 1) {
    unsigned long long accum = 0;
    for (unsigned cnt = 0; cnt < number_of_rolls; ++cnt) {
        accum += d.roll();
    }
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

int main() {
    Dice d(6, 42);
    ThreeDicePool threed(6, 1, 2, 3);

    std::cout << "E[Dice(6)] ≈ " << expected_value(d,1000) << "\n";
    std::cout << "E[ThreeDicePool(6)] ≈ " << expected_value(threed,1000) << "\n";
}
