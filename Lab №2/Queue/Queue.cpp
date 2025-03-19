#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>


void queue_new(std::size_t &read, std::size_t &write, int* &data, std::size_t &capacity){
    read = 0;
    write = 0;
    capacity = 1;
    data = new int[capacity];
}

bool queue_poll(std::size_t &read, std::size_t &write, int* &data, int &element, std::size_t &capacity){
    if (read==write){
        return false;
    }
    element = data[read];
    read = (read + 1) % (capacity);
    return true;
}

bool queue_push(std::size_t &read, std::size_t &write, int* &data, int &element, std::size_t &capacity){
    if ((write + 1) % capacity == read) {

        std::size_t new_capacity = capacity * 2;
        int* new_data = new (std::nothrow) int[new_capacity];

        if (!new_data) {
            return false;
        }
        
        std::size_t i = 0;
        while (read != write) {
            new_data[i] = data[read];
            read = (read + 1) % capacity;
            ++i;
        }
        delete[] data;
        data = new_data;
        read = 0;
        write = i;
        capacity = new_capacity;
    }
    data[write] = element;
    write = (write + 1) % capacity;
    return true;
}

void queue_del(int* &data){
    delete [] data;
    data = nullptr;
}

int change_step (int k, int& i){
    if (k < 100) {
        i = 10;
    } else if (k < 1000) {
        i = 100;
    } else if (k < 10000) {
        i = 500;
    } else {
        i = 1000;
    }
    return i;
}

double measure_time(bool (*func)(std::size_t &, std::size_t &, int *&, int &, std::size_t &), std::size_t& read, std::size_t& write, int*& data, int element, std::size_t& capacity) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();    
    bool result = func(read, write, data, element, capacity);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<long double, std::micro> diff = end-start;
    return diff.count();
}
int main(){

    std::vector<long double> time_push;
    std::vector<long double> time_poll;
    long double time_push_cycles,time_poll_cycles;
    std::vector<int> number;

    int cycles = 50;

    int* data = nullptr;
    size_t read = 0, write= 0, capacity = 1;

    int i = 10;
    for (int N = 10; N<=100000; N+=i){
        change_step(N,i);
        number.push_back(N);

        for (int i=0; i!=cycles; ++i){
            queue_new(read,write,data,capacity);
            for (int i = 0; i < N; ++i) {
                time_push_cycles += measure_time(queue_push, read, write, data, i, capacity);
            }
        
            for (int i = 0; i < N; ++i) {
                int element;
                time_poll_cycles += measure_time(queue_poll, read, write, data, element, capacity);
            }
            queue_del(data);
        }

        time_push.push_back(time_push_cycles/(cycles*N));  
        time_poll.push_back(time_poll_cycles/(cycles*N));      

    }

    std::ofstream outFile("Queue.csv");
    for (size_t i = 0; i < time_push.size(); ++i) {
        outFile << number[i] << "," << time_push[i] <<"," << time_poll[i] << std::endl;
    }
    return 0;
}