#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
		Node* curr = head;
		while (next != nullptr) {
			std::cout << curr->data << " ";
		}

		std::cout << tail->data;
	}
	void printReverse() const {
		Node* curr = tail;
		while (prev != nullptr) {
			std::cout << curr->data << " ";
		}

		std::cout << head->data;
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node* getHead() {
		return head;
	}
	const Node* getHead() const {
		return head;
	}
	Node* getTail() {
		return tail;
	}
	const Node* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		Node* newHead = new Node(data);
		newHead->next = head;
		newHead->prev = nullptr;

		head->prev = newHead;
		head = newHead;
		count++;
	}
	void addTail(const T& data) {
		Node* newTail = new Node(data);
		newTail->next = nullptr;
		newTail->prev = tail;

		tail->next = newTail;
		tail = newTail;
		count++;
	}

	// Removal
	bool removeHead() {
		if (count == 0) return false;

		Node* deleteMe = head;
		head = head->next;
		head->prev = nullptr;

		delete deleteMe;
		count--;

		return true;
	}
	bool removeTail() {
		if (count == 0) return false;

		Node* deleteMe = tail;
		tail = tail->prev;
		tail->next = nullptr;

		delete deleteMe;
		count--;

		return true;
	}
	void Clear() {
		Node* curr = head;

		while (curr != nullptr) {
			Node* next = curr->next;
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

		Clear();

		head = new Node(rhs.head->data);
		Node* curr = head;
		Node* currOther = rhs.head->next;

		while(currOther != nullptr) {
			Node* currNext = new Node(currOtherNext->data);
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
		head = new Node(list.head->data);
		Node* curr = head;
		Node* currOther = list.head->next;

		while(currOther != nullptr) {
			Node* currNext = new Node(currOtherNext->data);
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
		Clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};

template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
};