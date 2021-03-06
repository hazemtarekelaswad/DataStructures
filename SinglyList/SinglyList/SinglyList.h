#pragma once
#include "Node.h"
#include <initializer_list>
#include <iostream>

template<typename T>
class SinglyList {
private:
	Node<T>* m_head;
	size_t length;

public:
	SinglyList() : m_head(nullptr), length(0) {}

	SinglyList(const std::initializer_list<T>& initList) : m_head(nullptr), length(0) {
		/*typename std::initializer_list<T>::iterator element;
		for (element = initList.begin(); element != initList.end(); ++element)
			PushBack(*element);*/

		for (auto element : initList)
			PushBack(element);
	}

	SinglyList(const SinglyList& sList) : m_head(nullptr), length(0) {
		Node<T>* trav = sList.m_head;
		while (trav) {
			this->PushBack(trav->GetValue());
			trav = trav->GetNextNode();
		}
	}

	SinglyList(SinglyList&& sList) : m_head(nullptr), length(0) {
		m_head = sList.m_head;
		length = sList.length;
		sList.m_head = nullptr;
		sList.length = 0;
	}

	SinglyList& operator=(SinglyList sList) {
		sList.Swap(*this);
		return *this;
	}

	size_t GetLength() const { 
		return length; 
	}

	friend std::ostream& operator<<(std::ostream& out, const SinglyList& sList) {
		Node<T>* trav = sList.m_head;
		while (trav) {
			out << trav->GetValue() << ' ';
			trav = trav->GetNextNode();
		}
		return out;
	}

	void PushBack(const T& value) {
		Node<T>* newNode = new Node<T>(value);

		if (!m_head) {
			m_head = newNode;
			++length;
			return;
		}

		Node<T>* trav = m_head;
		while (trav->GetNextNode())
			trav = trav->GetNextNode();

		trav->SetNextNode(newNode);
		++length;
	}

	void PushFront(const T& value) {
		Node<T>* newNode = new Node<T>(value);
		newNode->SetNextNode(m_head);
		m_head = newNode;
		++length;
	}

	// Returns a boolean value depending on the success of poping operation, if the list is empty it would return false, yet true otherwise.

	bool PopBack() {
		Node<T>* trav = m_head;

		if (!m_head)
			return false;

		if (!m_head->GetNextNode()) {
			delete m_head;
			m_head = nullptr;
			--length;
			return true;
		}

		while (trav->GetNextNode()->GetNextNode())
			trav = trav->GetNextNode();
		delete trav->GetNextNode();
		trav->SetNextNode(nullptr);
		--length;
		return true;
	}

	// Returns a boolean value depending on the success of poping operation, if the list is empty it would return false, yet true otherwise.

	bool PopFront() {
		if (!m_head)
			return false;
		Node<T>* trav = m_head;
		m_head = m_head->GetNextNode();
		delete trav;
		--length;
		return true;
	}

	void Insert(const T& value, size_t index) {
		Node<T>* newNode = new Node<T>(value);
		Node<T>* trav = m_head;

		if (!index || !m_head) {
			delete newNode;
			PushFront(value);
			return;
		}
		while (--index) {
			trav = trav->GetNextNode();
			if (!trav) {
				delete newNode;
				throw "Invalid index passed\n";
			}
		}
		newNode->SetNextNode(trav->GetNextNode());
		trav->SetNextNode(newNode);
		++length;
	}

	void Delete(size_t index){
		Node<T>* travPrev = m_head;
		if (!index) {
			PopFront();
			return;
		}
		while (--index) {
			travPrev = travPrev->GetNextNode();
			if (!travPrev)
				throw "Invalid index passed\n";
		}
		if(!travPrev->GetNextNode())
			throw "Invalid index passed\n";

		Node<T>* nodeToDelete = travPrev->GetNextNode();
		travPrev->SetNextNode(nodeToDelete->GetNextNode());
		delete nodeToDelete;
		--length;
	}

	T operator[](size_t index) {
		if (!m_head)
			throw "invalide index passed\n";
		Node<T>* trav = m_head;
		while (index--) {
			trav = trav->GetNextNode();
			if(!trav)
				throw "invalide index passed\n";
		}
		return trav->GetValue();
	}

	bool IsEmpty() const {
		return m_head == nullptr;
	}

	void Reverse() {
		if (!m_head->GetNextNode())
			return;

		Node<T>* prevTrav = nullptr;
		Node<T>* currTrav = m_head;
		Node<T>* nextTrav = m_head;

		while (nextTrav) {
			nextTrav = nextTrav->GetNextNode();
			currTrav->SetNextNode(prevTrav);
			
			prevTrav = currTrav;
			currTrav = nextTrav;
		}
		m_head = prevTrav;
	}

	void Swap(SinglyList& sList) {
		Node<T>* tempHead = m_head;
		m_head = sList.m_head;
		sList.m_head = tempHead;

		size_t tempLength = length;
		length = sList.length;
		sList.length = tempLength;
	}

	~SinglyList() {
		if (!m_head)
			return;
		if (!m_head->GetNextNode()) {
			delete m_head;
			m_head = nullptr;
			return;
		}
		Node<T>* trav = m_head;
		while (trav) {
			Node<T>* tempHead = trav;
			trav = trav->GetNextNode();
			delete tempHead;
		}
		m_head = nullptr;
	}
};