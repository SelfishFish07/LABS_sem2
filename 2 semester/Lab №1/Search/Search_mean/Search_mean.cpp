#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>

int per(const std::vector<int>& array,int key){
    int res=-1;
    for (size_t i = 0; i != array.size(); ++i) {
        if (array[i] == key){
            res=i;
            break;
        }
    }
    return res;    
}

int bin(const std::vector<int>& array,int key){
    int res=-1;
    size_t l=0,r=array.size()-1, mid;

    while (l<=r){
        mid = l+(r-l)/2;
        if (key < array[mid]){
            r = mid -1;
        } else if (key > array[mid]) {
            l = mid + 1;
        } else {
            res = mid;
            break;
        }
    }
    return res;    
}

int change_step (int k, int& i){
    if (k < 100) {
        i = 10;
    } else if (k < 1000) {
        i = 100;
    } else if (k < 10000) {
        i = 500;
    } else {
        i = 5000;
    }
    return i;
}
int main() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0,9);
    int res;
    int cycles = 50; //Число повторений операций поиска

    std::vector<int> number;
    std::vector<long double> time1;
    std::vector<long double> time2;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
    std::chrono::duration<long double, std::micro> diff;

    int i = 10; //step
    for (int k = 10; k<=1000000; k+=i){
        change_step(k,i);

        const int n=k;
        number.push_back(n);
        std::vector<int> array(n);
        for (int i = 0; i != n; ++i) {
            array[i] = distrib(gen);
        }

        std::uniform_int_distribution<> distrib_index(0,n);
        size_t random_index = distrib_index(gen);
        int random_el = array[random_index];

        //Перебор
        start = std::chrono::steady_clock::now();
        for (int i=0; i!=cycles; ++i){
            res=per(array,random_el);
        }
        end = std::chrono::steady_clock::now();
        diff = (end - start);
        time1.push_back(diff.count()/cycles);

        std::sort(array.begin(), array.end());
        //Бинарный поиск
        start = std::chrono::steady_clock::now();
        for (int i=0; i!=cycles; ++i){
            res=bin(array,random_el);
        }
        end = std::chrono::steady_clock::now();
        diff = (end - start);
        time2.push_back(diff.count()/cycles);
    }

    std::ofstream outFile("Search_mean.csv");
    for (size_t i = 0; i < time1.size(); ++i) {
        outFile << number[i] << "," << time1[i] <<"," << time2[i] << std::endl;
    }
    outFile.close();
}
