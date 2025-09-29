#include <iostream>
#include <vector>
#include <random>
#include <fstream>

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

class PenaltyDice : public DiceBase {
public:
    PenaltyDice(DiceBase &base) : base(base) {}

    unsigned roll() override {
        unsigned a = base.roll();
        unsigned b = base.roll();
        return std::min(a, b);
    }

private:
    DiceBase &base;
};


class BonusDice : public DiceBase {
public:
    BonusDice(DiceBase &base) : base(base) {}

    unsigned roll() override {
        unsigned a = base.roll();
        unsigned b = base.roll();
        return std::max(a, b);
    }

private:
    DiceBase &base;
};

double value_probability(unsigned value, DiceBase &d, unsigned number_of_rolls = 1) {
    unsigned count = 0;
    for (unsigned i = 0; i < number_of_rolls; ++i) {
        if (d.roll() == value){
            count++;
        }
    }
    return static_cast<double>(count) / static_cast<double>(number_of_rolls);
}

int main() {
    Dice d100(100, 42);
    PenaltyDice pd(d100);
    BonusDice bd(d100);
    ThreeDicePool threed(6, 1, 2, 3);

    std::cout << "Exp. value for PenaltyDice(100): " << expected_value(pd,10000) << "\n";
    std::cout << "Exp. value for BonusDice(100): " << expected_value(bd,10000) << "\n";

    std::vector<double> hist_d100;
    for (int v = 1; v != 101; v++) {
        hist_d100.push_back(value_probability(v, d100,10000));
    }

    std::vector<double> hist_pd100;
    for (int v = 1; v != 101; v++) {
        hist_pd100.push_back(value_probability(v, pd,10000));
    }

    std::vector<double> hist_bd100;
    for (int v = 1; v != 101; v++) {
        hist_bd100.push_back(value_probability(v, bd,10000));
    }

    std::vector<double> hist_3d100;
    for (int v = 1; v != 19; v++) {
        hist_3d100.push_back(value_probability(v, threed,100000));
    }

    std::ofstream file("data_2.txt");
    
    for (size_t i = 0; i < hist_d100.size(); ++i) {
        file << hist_d100[i] << " " << hist_pd100[i] << " " << hist_bd100[i]<< " " << hist_3d100[i] << std::endl;
    }
    
    file.close();
}
