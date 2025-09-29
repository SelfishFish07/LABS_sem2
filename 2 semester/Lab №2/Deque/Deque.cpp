#include <iostream>
#include <cstring>
#include <cassert>

struct Deque {
    size_t element_size;
    size_t capacity;
    size_t read_element_offset;
    size_t write_element_offset;
    void* buffer;
};

void deque_new(Deque* deque, size_t capacity, size_t element_size) {
    if (deque != nullptr) {
        deque->element_size = element_size;
        deque->capacity = capacity;
        deque->read_element_offset = 0;
        deque->write_element_offset = 0;
        deque->buffer = malloc(capacity * element_size);
        if (deque->buffer == nullptr) {
            std::cout << "Try again. Deque == nullptr";
        }
    }
}
void deque_del(Deque* deque) {
    free(deque->buffer);
    deque->buffer = nullptr;
}

bool deque_resize(Deque* deque) {
    size_t new_capacity = deque->capacity * 2;
    void* new_buffer = malloc(new_capacity * deque->element_size);

    if (new_buffer == nullptr) {
        return false;
    }

    size_t read = deque->read_element_offset;
    size_t write = 0;
    size_t total_size = deque->capacity * deque->element_size;

    while (read != deque->write_element_offset) {
        std::memcpy(static_cast<char*>(new_buffer) + write, static_cast<char*>(deque->buffer) + read, deque->element_size);
        read = (read + deque->element_size) % total_size;
        write += deque->element_size;
    }

    free(deque->buffer);

    deque->buffer = new_buffer;
    deque->capacity = new_capacity;
    deque->read_element_offset = 0;
    deque->write_element_offset = write;
    std::cout << "Deque was resized. New capacity: " << new_capacity << std::endl;
    return true;
}

bool deque_empty(Deque* deque) {
    return deque->read_element_offset == deque->write_element_offset;
}

bool deque_full(Deque* deque) {
    size_t total_size = deque->capacity * deque->element_size;
    size_t next_write = (deque->write_element_offset + deque->element_size) % total_size;
    return next_write == deque->read_element_offset;
}

bool deque_push_front(Deque* deque, const void* data) {
    if (deque_full(deque)) {
        if (!deque_resize(deque)) {
            return false;
        }
    }

    size_t total_size = deque->capacity * deque->element_size;
    if (deque->read_element_offset == 0) {
        deque->read_element_offset = total_size - deque->element_size;
    } else {
        deque->read_element_offset = (deque->read_element_offset - deque->element_size) % total_size;
    }

    std::memcpy(static_cast<char*>(deque->buffer) + deque->read_element_offset, data, deque->element_size);
    std::cout << deque->read_element_offset << ' ' << deque->write_element_offset << std::endl;
    return true;
}

bool deque_poll_front(Deque* deque, void* dest) {
    if (deque_empty(deque)) {
        return false;
    }
    std::memcpy(dest, static_cast<char*>(deque->buffer) + deque->read_element_offset, deque->element_size);
    size_t total_size = deque->capacity * deque->element_size;
    deque->read_element_offset = (deque->read_element_offset + deque->element_size) % total_size;
    return true;
}

bool deque_push_back(Deque* deque, const void* data) {
    if (deque_full(deque)) {
        if (!deque_resize(deque)) {
            return false;
        }
    }

    std::memcpy(static_cast<char*>(deque->buffer) + deque->write_element_offset, data, deque->element_size);

    size_t total_size = deque->capacity * deque->element_size;
    deque->write_element_offset = (deque->write_element_offset + deque->element_size) % total_size;
    std::cout << deque->read_element_offset << ' ' << deque->write_element_offset << std::endl;
    return true;
}

bool deque_poll_back(Deque* deque, void* dest) {
    if (deque_empty(deque)) {
        return false;
    }
    
    size_t total_size = deque->capacity * deque->element_size;
    if (deque->write_element_offset == 0) {
        deque->write_element_offset = total_size - deque->element_size;
    } else {
        deque->write_element_offset = (deque->write_element_offset - deque->element_size) % total_size;
    }
    
    std::memcpy(dest, static_cast<char*>(deque->buffer) + deque->write_element_offset, deque->element_size);
    return true;
}

int main() {
    Deque deque;
    deque_new(&deque, 5, sizeof(int));
    
    int value = 20;
    for (int i = 0; i < 15; ++i) {
        int test_value = value + i;
        std::cout <<"Front ";
        deque_push_front(&deque, &test_value);
    }
    for (int i = 0; i < 15; ++i) {
        int test_value = 100 + i;
        std::cout <<"Back ";
        deque_push_back(&deque, &test_value);
    }
    
    int result;
    
    while (deque_poll_back(&deque, &result)) {
        std::cout << "Poll back: " << result << std::endl;
    }

    deque_del(&deque);
    return 0;
}
