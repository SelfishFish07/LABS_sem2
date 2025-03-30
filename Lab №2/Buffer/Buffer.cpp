#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

void pushback_A(int*& array, int& size, int& capacity, int new_elem) {

    int* new_array = new int[size+1];
    for (int i = 0; i < size; ++i) {
        new_array[i] = array[i];
    }
    delete[] array;
    array = new_array;
    array[size] = new_elem;
    ++size;
}

void pushback_B(int*& array, int& size, int& capacity, int new_elem) {
    if (size >= capacity) {
        capacity += 100;
        int* new_array = new int[capacity];
        for (int i = 0; i < size; ++i) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
    }
    array[size] = new_elem;
    ++size;
}

void pushback_C(int*& array, int& size, int& capacity, int new_elem) {
    if (size >= capacity) {
        if (capacity==0){
            capacity = 1;
        } else {
            capacity *= 2;
        }
        int* new_array = new int[capacity];
        for (int i = 0; i < size; ++i) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
    }
    array[size] = new_elem;
    ++size;
}

long double measure_time(void (*func)(int*&, int&, int&, int), int*& array, int& size, int& capacity, int new_elem) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();    
    func(array,size,capacity,new_elem);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<long double, std::micro> diff = end-start;
    return diff.count();
}

int change_step (int k, int& i){
    if (k < 100) {
        i = 1;
    } else if (k < 1000) {
        i = 1;
    } else if (k < 10000) {
        i = 1;
    } else {
        i = 1;
    }
    return i;
}

int main(){
    std::vector<long double> timeA;
    std::vector<long double> timeB;
    std::vector<long double> timeC;
    std::vector<int> number;
    double time_push_cycles;

    int cycles = 1;


    int* arrayA = nullptr;
    int sizeA = 0, capacityA = 0;

    int* arrayB = nullptr;
    int sizeB = 0, capacityB = 0;

    int* arrayC = nullptr;
    int sizeC = 0, capacityC = 0;

    int i = 10;
    for (int N = 10; N<=5000; N+=i){ // Количество элементов для добавления
        change_step(N,i);
        number.push_back(N);

        //A
        time_push_cycles = 0;
        for (int i=0; i!=cycles; ++i){
            for (int j = 0; j < N; ++j) {
                time_push_cycles+=measure_time(pushback_A,arrayA,sizeA,capacityA,j);
            }
            int* arrayA = nullptr;
            sizeA = 0;
        }
        timeA.push_back(time_push_cycles/(cycles*N));

        //B
        time_push_cycles = 0;
        for (int i=0; i!=cycles; ++i){
            for (int j = 0; j < N; ++j) {
                time_push_cycles+=measure_time(pushback_B,arrayB,sizeB,capacityB,j);
            }
            int* arrayB = nullptr;
            sizeB = 0,capacityB=0;
        }
        timeB.push_back(time_push_cycles/(cycles*N));

        //C
        time_push_cycles = 0;
        for (int i=0; i!=cycles; ++i){
            for (int j = 0; j < N; ++j) {
                time_push_cycles+=measure_time(pushback_C,arrayC,sizeC,capacityC,j);
            }
            int* arrayC = nullptr;
            sizeC = 0,capacityC=0;
        }
        timeC.push_back(time_push_cycles/(cycles*N));      
    }
    delete[] arrayA;
    delete[] arrayB;
    delete[] arrayC;

    std::ofstream outFile("Buffer2.csv");
    for (size_t i = 0; i < timeA.size(); ++i) {
        outFile << number[i] << "," << timeA[i] <<"," << timeB[i] <<"," << timeC[i] << std::endl;
    }
    return 0;
}