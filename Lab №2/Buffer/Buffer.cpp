#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

void pushback_A(int*& array, int& size, int new_elem) {

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
        capacity += 50;
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

int main(){

    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
    std::chrono::duration<long double, std::micro> diff;
    std::vector<long double> timeA;
    std::vector<long double> timeB;
    std::vector<long double> timeC;
    std::vector<int> number;

    int cycles = 5;


    int* arrayA = nullptr;
    int sizeA = 0;

    int* arrayB = nullptr;
    int sizeB = 0, capacityB = 0;

    int* arrayC = nullptr;
    int sizeC = 0, capacityC = 0;

    int i = 10;
    for (int N = 10; N<=50000; N+=i){ // Количество элементов для добавления
        change_step(N,i);
        number.push_back(N);

        //A
        start = std::chrono::steady_clock::now();
        for (int i=0; i!=cycles; ++i){
            for (int j = 0; j < N; ++j) {
                pushback_A(arrayA,sizeA,j);
            }
            int* arrayA = nullptr;
            sizeA = 0;
        }
        end = std::chrono::steady_clock::now();
        diff = (end - start);
        timeA.push_back(diff.count()/cycles);

        //B
        start = std::chrono::steady_clock::now();
        for (int i=0; i!=cycles; ++i){
            for (int j = 0; j < N; ++j) {
                pushback_B(arrayB,sizeB,capacityB,j);
            }
            int* arrayB = nullptr;
            sizeB = 0, capacityB = 0;
        }
        end = std::chrono::steady_clock::now();
        diff = (end - start);
        timeB.push_back(diff.count()/cycles);

        //C
        start = std::chrono::steady_clock::now();
        for (int i=0; i!=cycles; ++i){
            for (int j = 0; j < N; ++j) {
                pushback_C(arrayC,sizeC,capacityC,j);
            }
            int* arrayC = nullptr;
            sizeC = 0, capacityC = 0;
        }
        end = std::chrono::steady_clock::now();
        diff = (end - start);
        timeC.push_back(diff.count()/cycles);        
    }
    delete[] arrayA;
    delete[] arrayB;
    delete[] arrayC;

    std::ofstream outFile("Buffer.csv");
    for (size_t i = 0; i < timeA.size(); ++i) {
        outFile << number[i] << "," << timeA[i] <<"," << timeB[i] <<"," << timeC[i] << std::endl;
    }
    return 0;
}