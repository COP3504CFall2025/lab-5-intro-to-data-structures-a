#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() {
        list.head = nullptr;
        list.tail = nullptr;
        list.count = 0;
    }

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        T val = (list.getHead())->data;
        list.removeHead();
        return val;
    }
    T popBack() override {
        T val = (list.getTail())->data;
        list.removeTail();
        return val;
    }

    // Element Accessors
    const T& front() const override {
        return (list.getHead())->data;
    }
    const T& back() const override {
        return (list.getTail())->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};






