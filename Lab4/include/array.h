#pragma once
#include <memory>
#include <stdexcept>

template <class T>
class Array {
private:
    size_t capacity;
    size_t size;
    std::unique_ptr<std::shared_ptr<T>[]> data;

    void resize() {
        size_t new_capacity = capacity * 2;
        std::unique_ptr<std::shared_ptr<T>[]> new_data(new std::shared_ptr<T>[new_capacity]);
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        data = std::move(new_data);
        capacity = new_capacity;
    }

public:
    Array() : capacity(4), size(0), data(new std::shared_ptr<T>[capacity]) {}

    void push_back(std::shared_ptr<T> value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = std::move(value);
    }

    void remove_at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        data[size - 1].reset();
        --size;
    }

    size_t get_size() const {
        return size;
    }

    std::shared_ptr<T> &operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        return data[index];
    }

    const std::shared_ptr<T> &operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        return data[index];
    }
};
