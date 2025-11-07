#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>
#include <numeric>

int A(std::vector<int> &array, int key)
{
    int res = -1;
    bool f = false;

    for (size_t i = 0; i != array.size(); ++i)
    {
        if (array[i] == key)
        {
            res = i;
            f = true;
            break;
        }
    }

    if (f)
    {
        std::swap(array[res], array[0]);
        return res;
    }
    else
    {
        return res;
    }
}

int B(std::vector<int> &array, int key)
{
    int res = -1;
    bool f = false;

    for (size_t i = 0; i != array.size(); ++i)
    {
        if (array[i] == key)
        {
            res = i;
            f = true;
            break;
        }
    }

    if (f)
    {
        if (res != 0)
        {
            std::swap(array[res], array[res - 1]);
        }
        return res;
    }
    else
    {
        return res;
    }
}

int C(std::vector<int> &array, std::vector<int> &count, int key)
{
    int res = -1;
    bool f = false;

    for (size_t i = 0; i != array.size(); ++i)
    {
        if (array[i] == key)
        {
            res = i;
            f = true;
            break;
        }
    }

    if (f)
    {
        ++count[res];
        if (res != 0){
            if (count[res] > count[res - 1])
            {
                std::swap(array[res], array[res - 1]);
                std::swap(count[res], count[res - 1]);
            }
        }
        return res;

    }
    else
    {
        return res;
    }
}

int main(){

    std::random_device rd;
    std::mt19937 gen(rd());

    int res, cycles = 1000;

    std::vector<int> number;
    std::vector<long double> timeA, timeB, timeC;
    std::chrono::steady_clock::time_point start, end;
    std::chrono::duration<long double, std::micro> diff;

    int random_el;
    // Равномерное распределение
    std::discrete_distribution<> non_uniform_distrib({1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1}); // Увеличивает вероятность выпадения 5
   

    for (int k = 10; k<=50000; k+=100){

        const int n=k;
        number.push_back(n);

        std::vector<int> array(n);
        std::iota(array.begin(), array.end(), 1); // Заполняем вектор числами от 1 до n

        // A
        start = std::chrono::steady_clock::now();
        for (int i = 0; i != cycles; ++i)
        {
            random_el = non_uniform_distrib(gen);
            res = A(array, random_el);
        }
        end = std::chrono::steady_clock::now();
        diff = (end - start);
        timeA.push_back(diff.count());

        std::iota(array.begin(), array.end(), 1);

        // B
        start = std::chrono::steady_clock::now();
        for (int i = 0; i != cycles; ++i)
        {
            random_el = non_uniform_distrib(gen);
            res = B(array, random_el);
        }
        end = std::chrono::steady_clock::now();
        diff = (end - start);
        timeB.push_back(diff.count());

        std::iota(array.begin(), array.end(), 1);
        std::vector<int> count(n); //Счетчик
        // C
        start = std::chrono::steady_clock::now();
        for (int i = 0; i != cycles; ++i)
        {
            random_el = non_uniform_distrib(gen);
            res = C(array, count, random_el);
        }
        end = std::chrono::steady_clock::now();
        diff = (end - start);
        timeC.push_back(diff.count());

    }

    std::ofstream outFile("Strat_nonuni.csv");
    for (size_t i = 0; i < timeA.size(); ++i) {
        outFile << number[i] << "," << timeA[i] <<"," << timeB[i] <<"," << timeC[i] << std::endl;
    }
    outFile.close();
}



