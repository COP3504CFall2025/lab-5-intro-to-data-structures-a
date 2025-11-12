#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t curr_size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
        capacity_ = 4;
        curr_size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    explicit ABDQ(std::size_t capacity) {
        capacity_ = capacity;
        curr_size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    ABDQ(const ABDQ& other) {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->data_ = new T[capacity_];
        front_ = other.front_;
        back_ = other.back_;
        
        for (size_t i = 0; i < other.curr_size_; i++) {
            this->data_[i] = other.data_[i];
        }
    }
    ABDQ(ABDQ&& other) noexcept {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->data_ = other.data_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;

        T* newArray = new T[other.capacity_];
        delete[] this->data_;
        this->data_ = newArray;
        
        for (size_t i = 0; i < other.curr_size_; i++) {
            this->data_[i] = other.data_[i];
        }

        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        front_ = other.front_;
        back_ = other.back_;
        return *this;
        
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) return *this;

        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        front_ = other.front_;
        back_ = other.back_;
        delete[] data_;
        data_ = other.data_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.front_ = 0;
        other.back_ = 0;

        return *this;
    }
    ~ABDQ() {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (curr_size_ >= capacity_) {
            capacity_ *= 2;

            T* newData = new T[capacity_];
            for (size_t i = 0; i < curr_size_; i++) {
                newData[i] = data_[i];
            }

            delete[] data_;
            data_ = newData;
        }

        for (size_t i = curr_size_; i > 0; i--) {
            data_[i+1] = data_[i];
        }

        data_[0] = item;
        curr_size_++;
    }
    void pushBack(const T& item) override {
        if (curr_size_ >= capacity_) {
            capacity_ *= 2;

            T* newData = new T[capacity_];
            for (size_t i = 0; i < curr_size_; i++) {
                newData[i] = data_[i];
            }

            delete[] data_;
            data_ = newData;
        }
        
        data_[curr_size_] = item;
        curr_size_++;
    }

    // Deletion
    T popFront() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty container");
        }
        T element = data_[0];
        for (size_t i = 1; i < curr_size_; i++) {
            data_[i-1] = data_[i];
        }
        curr_size_--;
        return element;
    }
    T popBack() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty container");
        }
        T element = data_[curr_size_ - 1];
        curr_size_--;
        return element;
    }

    // Access
    const T& front() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty container");
        }
        return data_[0];
    }
    const T& back() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty container");
        }
        return data_[curr_size_ - 1];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return curr_size_;
    }

    void ensureCapacity() {
        capacity_ *= 2;
    }

    void shrinkIfNeeded() {
        if (curr_size_ <= capacity_ / 2) {
            capacity_ /= 2;
        }
    }

    void PrintForward() const {
        for (T element : data_) {
            std::cout << element << " ";
        }
    }

    void PrintReverse() const {
        for (size_t i = curr_size_; i >= 0; i--) {
            std::cout << data_[i] << " ";
        }
    }

};
