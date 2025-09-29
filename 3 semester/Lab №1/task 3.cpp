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

class PenaltyDice : public virtual DiceBase {
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

class BonusDice : public virtual DiceBase {
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

class DoubleDice : public PenaltyDice, public BonusDice {
public:
    DoubleDice(DiceBase &base)
        : DiceBase(), PenaltyDice(base), BonusDice(base), base(base) {}

    unsigned roll() override {
        unsigned p = PenaltyDice::roll();
        unsigned b = BonusDice::roll();
        return (p + b) / 2;
    }

private:
    DiceBase &base;
};


// без множественного наследования
// class DoubleDiceAlt : public DiceBase {
// public:
//     DoubleDiceAlt(DiceBase &base) : pd(base), bd(base) {}

//     unsigned roll() override {
//         return (pd.roll() + bd.roll()) / 2;
//     }

// private:
//     PenaltyDice pd;
//     BonusDice bd;
// };

int main() {
    Dice d100(100, 42);
    DoubleDice doubled(d100);

    std::cout << "Exp. value for DoubleDice(100): " << expected_value(doubled) << "\n";
    
    std::vector<double> hist_dd;
    for (int v = 0; v != 100; v++) {
        hist_dd.push_back(value_probability(v, doubled,10000));
    }

    std::ofstream file("data_3.txt");
    
    for (size_t i = 0; i < hist_dd.size(); ++i) {
        file << hist_dd[i] << std::endl;
    }
    
    file.close();
}
