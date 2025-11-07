#include <stdio.h>
#include <stdlib.h>
#include<cmath>
#include <iostream>
#include <string>

#include "my_math.hpp"

int main(){
    std::string function;
    std::cout << "Choose trigonometry function:";
    std::cin >> function;
    std::cout << "Write argument:";
    double x;
    std::cin >> x;
    std::cout << function << "("<<x<<") = ";
    if (function == "sin") {
        std::cout << my_sin(x).func << std::endl;
    } else if (function == "cos") {
        std::cout << my_cos(x).func << std::endl;
    } else if (function == "tg") {
        std::cout << my_tg(x).func << std::endl;
    } else if (function == "ctg") {
        std::cout << my_ctg(x).func << std::endl;
    } else if (function == "arcsin") {
        std::cout << my_arcsin(x).func << std::endl;
    } else if (function == "arccos") {
        std::cout << my_arccos(x).func << std::endl;
    } else if (function == "arctg") {
        std::cout << my_arctg(x).func << std::endl;
    } else if (function == "arcctg") {
        std::cout << my_arcctg(x).func << std::endl;
    } else {
        std::cout << "Wrong function!" << std::endl;
    }
}