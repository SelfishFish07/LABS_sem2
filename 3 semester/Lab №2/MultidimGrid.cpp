#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

template <typename T, unsigned N>
class Grid;

template <typename T>
class Grid<T, 1> {
public:
    using value_type = T;
    using size_type = unsigned;

private:
    T* data;
    size_type size;

public:

    Grid(size_type size) : size(size) {
        data = new T[size];
    }

    Grid(size_type size, T const &t) : size(size) {
        data = new T[size];
        for (size_type i = 0; i < size; ++i) {
            data[i] = t;
        }
    }

    ~Grid() { 
        delete[] data;
     }

    Grid(Grid const &other) : size(other.size) {
        data = new T[size];
        for (size_type i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    Grid& operator=(Grid const &other) {
        Grid temp(other);
        std::swap(data, temp.data);
        std::swap(size, temp.size);
        return *this;
    }

    Grid(Grid &&other) : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    Grid& operator=(Grid &&other) {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    T operator()(size_type x) const {
        return data[x];
    }

    T& operator()(size_type x) {
        return data[x];
    }

    T& operator[](size_type x) {
        return data[x];
    }

    T operator[](size_type x) const {
        return data[x];
    }
};

template <typename T, unsigned N>
class Grid {
public:
    using size_type = unsigned;

private:
    Grid<T, N-1>** data;
    size_type size;

public:
    template <typename... Args>
    Grid(size_type size, Args... args) : size(size) {
        data = new Grid<T, N-1>*[size];
        for (size_type i = 0; i < size; ++i) {
            data[i] = new Grid<T, N-1>(args...);
        }
    }

    ~Grid() {
        for (size_type i = 0; i < size; ++i)
            delete data[i];
        delete[] data;
    }

    Grid(Grid const &other) : size(other.size) {
        data = new Grid<T, N-1>*[size];
        for (size_type i = 0; i < size; ++i)
            data[i] = new Grid<T, N-1>(*other.data[i]);
    }

    Grid& operator=(Grid const &other) {
        Grid tmp(other);
        std::swap(data, tmp.data);
        std::swap(size, tmp.size);
        return *this;
    }

    Grid(Grid &&other) : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    Grid& operator=(Grid &&other) {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    Grid<T, N-1>& operator[](size_type i) { 
        return *data[i]; 
    }
    Grid<T, N-1> const& operator[](size_type i) const { 
        return *data[i];   
    }

    template <typename... Args>
    T& operator()(size_type i, Args... args) {
         return (*data[i])(args...); 
        }

    template <typename... Args>
    T operator()(size_type i, Args... args) const { 
        return (*data[i])(args...); 
    }
};
