#include <algorithm>

template <typename T>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;

    // RAII

    Grid(T const& t) : y_size(1), x_size(1) {
        data = new T[1];
        data[0] = t;
    }

    Grid(size_type y_size, size_type x_size) : y_size(y_size), x_size(x_size) {
        data = new T[y_size * x_size];
    }

    Grid(size_type y_size, size_type x_size, T const& t) : y_size(y_size), x_size(x_size) {
        data = new T[y_size * x_size];
        for (size_type i=0; i < y_size*x_size; ++i) {
            data[i] = t;
        }
    }

    ~Grid() {
        delete[] data;
    }

    Grid(Grid<T> const& other) : y_size(other.y_size), x_size(other.x_size) {
        data = new T[y_size*x_size];
        for (size_type i = 0; i < y_size*x_size; ++i) {
            data[i] = other.data[i];
        }
    }

    Grid<T>& operator=(Grid<T> const& other) {
        Grid<T> temp(other);
        std::swap(data, temp.data);
        std::swap(y_size, temp.y_size);
        std::swap(x_size, temp.x_size);
        return *this;
    }

    Grid(Grid &&other) : data(other.data), y_size(other.y_size), x_size(other.x_size) noexcept {
        other.data = nullptr;
        other.y_size = 0;
        other.x_size = 0;
        data = std::exchange(other.data, nullptr);
    }

    Grid& operator=(Grid &&other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            y_size = other.y_size;
            x_size = other.x_size;
            other.data = nullptr;
            other.y_size = 0;
            other.x_size = 0;
        }
        return *this;
    }


    T conts& operator() (size_type y, size_type x) const {
        return data[y*x_size + x];
    }

    T& operator() (size_type y, size_type x) {
        return data[y*x_size +x];
    }

    Grid& operator=(T const &t) {
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = t;
        }
        return *this;
    }

    //Indexing 

private:
    class row_proxy {
    private:
        T* row;
    public:
        row_proxy(T* row) : row(row) {}

        T& operator[](size_type x) {
            return row[x];
        }

        T const& operator[](size_type x) const {
            return row[x];
        }
    };

public:


    row_proxy operator[](size_type y) {
        return row_proxy(data + y*x_size);
    }

    row_proxy const operator[](size_type y) const {
        return row_proxy(data + y*x_size);
    }
    
private:
    T* data;
    size_type y_size, x_size;

};