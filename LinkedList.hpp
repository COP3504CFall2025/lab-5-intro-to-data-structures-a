#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;

	Node(const T& data) : data(data), prev(nullptr), next(nullptr) {};
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
		Node<T>* curr = head;
		while (curr->next != nullptr) {
			std::cout << curr->data << " ";
		}

		std::cout << tail->data;
	}
	void printReverse() const {
		Node<T>* curr = tail;
		while (curr->prev != nullptr) {
			std::cout << curr->data << " ";
		}

		std::cout << head->data;
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node<T>* getHead() {
		return head;
	}
	const Node<T>* getHead() const {
		return head;
	}
	Node<T>* getTail() {
		return tail;
	}
	const Node<T>* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		Node<T>* newHead = new Node<T>(data);

		if (head == nullptr) {
			head = newHead;
			tail = newHead;
		}
		else {
			newHead->next = head;
			newHead->prev = nullptr;

			head->prev = newHead;
			head = newHead;
		}
		count++;
	}
	void addTail(const T& data) {
		Node<T>* newTail = new Node<T>(data);

		if (tail == nullptr) {
			head = newTail;
			tail = newTail;
		}
		else {
			newTail->next = nullptr;
			newTail->prev = tail;

			tail->next = newTail;
			tail = newTail;
		}
		count++;
	}

	// Removal
	bool removeHead() {
		if (count == 0) return false;

		Node<T>* deleteMe = head;
		head = head->next;
		head->prev = nullptr;

		delete deleteMe;
		count--;

		return true;
	}
	bool removeTail() {
		if (count == 0) return false;

		Node<T>* deleteMe = tail;
		tail = tail->prev;
		tail->next = nullptr;

		delete deleteMe;
		count--;

		return true;
	}
	void clear() {
		Node<T>* curr = head;

		while (curr != nullptr) {
			Node<T>* next = curr->next;
			delete curr;
			curr = next;
		}

		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) return *this;

		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;

		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) return *this;

		clear();

		head = new Node<T>(rhs.head->data);
		Node<T>* curr = head;
		Node<T>* currOther = rhs.head->next;

		while(currOther != nullptr) {
			Node<T>* currNext = new Node<T>(currOther->data);
			curr->next = currNext;
			currNext->prev = curr;
			curr = currNext;
			currOther = currOther->next;
		}

		tail = curr;
		count = rhs.count;
		return *this;

	}

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {};
	LinkedList(const LinkedList<T>& list) {
		head = new Node<T>(list.head->data);
		Node<T>* curr = head;
		Node<T>* currOther = list.head->next;

		while(currOther != nullptr) {
			Node<T>* currNext = new Node<T>(currOther->data);
			curr->next = currNext;
			currNext->prev = curr;
			curr = currNext;
			currOther = currOther->next;
		}

		tail = curr;
		count = list.count;
	}
	LinkedList(LinkedList<T>&& other) noexcept {
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {
		clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;

};