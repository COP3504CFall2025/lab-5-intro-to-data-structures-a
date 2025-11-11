#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface {
    void virtual push(const T& item);
    T virtual pop();
    T virtual peek() const;
    std::size_t virtual getSize() const noexcept;
};


template <typename T>
class QueueInterface {
    void virtual enqueue(const T& item);
    T virtual dequeue();
    T virtual peek() const;
    std::size_t virtual getSize() const noexcept;
};


template <typename T>
class DequeInterface {
    void virtual pushFront(const T& item);
    void virtual pushBack(const T& item);
    T virtual popFront();
    T virtual popBack();
    const T& virtual front() const;
    const T& virtual back() const;
    std::size_t virtual getSize() const noexcept;
};

