#pragma once
#include <iostream>
#include <string>

typedef char Elem;
class NodeList
{
private:
	struct Node
	{
		Elem data;
		Node* prev;
		Node* next;
	};
public:
	class Iterator
	{
	public:
		Elem& operator*();
		bool operator==(const Iterator& current) const;
		bool operator!=(const Iterator& current) const;
		Iterator& operator++();
		Iterator& operator--();
		friend class NodeList;
	private:
		Node* position;
		Iterator(Node* nodeList);
	};
	NodeList();
	NodeList(std::string startingString);
	int size() const;
	bool empty() const;
	bool isAtEnd(Iterator iterator);
	Iterator begin() const;
	Iterator end() const;
	void insertFront(const Elem& item);
	void insertBack(const Elem& item);
	void insert(const Iterator& iteratorPosition, const Elem& item);
	void eraseFront();
	void eraseBack();
	void erase(const Iterator& iteratorPosition);
	void print(Iterator iterator, NodeList list);
	void indexOf(int indexPosition, Iterator& iterator);
	int atIndex(Iterator iterator, NodeList list);
private:
	int sizeOfList;
	Node* header;
	Node* trailer;
};

NodeList::Iterator::Iterator(Node* nodeList)
{
	position = nodeList;
}

Elem& NodeList::Iterator::operator*()
{
	return position->data;
}

bool NodeList::Iterator::operator==(const Iterator& current) const
{
	return position == current.position;
}

bool NodeList::Iterator::operator!=(const Iterator& current) const
{
	return position != current.position;
}

NodeList::Iterator& NodeList::Iterator::operator++()
{
	position = position->next;
	return *this;
}

NodeList::Iterator& NodeList::Iterator::operator--()
{
	position = position->prev;
	return *this;
}

NodeList::NodeList()
{
	sizeOfList = 0;
	header = new Node;
	trailer = new Node;
	header->next = trailer;
	trailer->prev = header;
}

NodeList::NodeList(std::string startingString)
{
	header = new Node;
	trailer = new Node;
	header->next = trailer;
	trailer->prev = header;
	Iterator i = 0;
	for (std::string::size_type i = 0; i < startingString.length(); i++)
	{
		insertBack(startingString[i]);
		sizeOfList == i;
	}
}

int NodeList::size() const
{
	return sizeOfList;
}

bool NodeList::empty() const
{
	return (sizeOfList == 0);
}

NodeList::Iterator NodeList::begin() const
{
	return Iterator(header->next);
}

NodeList::Iterator NodeList::end() const
{
	return Iterator(trailer);
}

void NodeList::insertFront(const Elem& item)
{
	insert(begin(), item);
}

void NodeList::insertBack(const Elem& item)
{
	insert(end(), item);
}

void NodeList::insert(const Iterator& iteratorPosition, const Elem& item)
{
	Node* currentPosition = iteratorPosition.position;
	Node* iteratorsPrevious = currentPosition->prev;
	Node* newItem = new Node;
	newItem->data = item;
	newItem->next = currentPosition;
	currentPosition->prev = newItem;
	newItem->prev = iteratorsPrevious;
	iteratorsPrevious->next = newItem;
	sizeOfList++;
}

void NodeList::eraseFront()
{
	erase(begin());
}

void NodeList::eraseBack()
{
	erase(--end());
}

void NodeList::erase (const Iterator& iteratorPosition)
{
	Node* positionToErase = iteratorPosition.position;
	Node* iteratorsNext = positionToErase->next;
	Node* iteratorsPrevious = positionToErase->prev;
	iteratorsPrevious->next = iteratorsNext;
	iteratorsNext->prev = iteratorsPrevious;
	delete positionToErase;
	sizeOfList--;
}

void NodeList::print(Iterator iterator, NodeList list)
{
	Iterator printIterator = list.begin();
	int index = 0;
	for (printIterator; printIterator != list.end(); ++printIterator)
	{
		if (printIterator == iterator)
			std::cout << ">";
		std::cout << *printIterator;
	}
	if (iterator == list.end())
		std::cout << "> ";
	std::cout << "\n";
}

int NodeList::atIndex(Iterator iterator, NodeList list)
{
	Iterator currentIterator = list.begin();
	int currentIndex = 0;
	for (currentIterator; currentIterator != list.end(); ++currentIterator)
	{
		if (currentIterator == iterator)
			break;
		currentIndex++;
	}
	return currentIndex;
}

void NodeList::indexOf(int indexPosition, Iterator& iterator)
{
	Iterator iteratorIndex(this->begin());
	for (int i = 0; i != indexPosition; i++)
		++iteratorIndex;
	iterator = iteratorIndex;
}

bool NodeList::isAtEnd(Iterator iterator)
{
	Iterator checkIterator = this->end();
	if (*iterator == *checkIterator)
		return true;
	else
		return false;
}
