#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <list>

template <typename Elem>
class BinaryTree
{
protected:

	struct Node {
		Elem element;
		Node* parent;
		Node* left;
		Node* right;
		Node() : element(), parent(NULL), left(NULL), right(NULL) { }
	};

public:
	class Position {
	private:
		Node* position;
		int ht;
	public: 
		Position(Node* _pos = NULL) : position(_pos) { }

		Elem& operator*() { return position->element; }

		Position left() const { return Position(position->left); }

		Position right() const { return Position(position->right); }

		Position parent() const { return Position(position->parent); }

		bool isRoot() { return position->parent == NULL; }

		bool isExternal() const { return position->left == NULL && position->right == NULL; }

		bool isInternal() const { return !isExternal(); }

		bool operator==(const Position& comparedPosition) const { return position == comparedPosition.position; }

		bool operator != (const Position comparedPosition) const { return !(*this == comparedPosition); }

		int height() const	{	return ht;	}			// get height

		void setHeight(int h)	{	ht = h;	}			// set height

		friend class BinaryTree;

	};
	typedef std::list<Position> PositionList;

public:
	BinaryTree() : _root(NULL), totalNodes(0) { }

	int size() const
	{
		return totalNodes;
	}

	bool empty() const
	{
		return size() == 0;
	}

	Position root() const { return Position(_root); }

	PositionList positions() const
	{
		PositionList positionList;
		preOrder(_root, positionList);
		return PositionList(positionList);
	}

	void addRoot()
	{
		_root = new Node;
		totalNodes = 1;
	}
	void expandExternal(const Position& currentPosition)
	{
		Node* expandedNode = currentPosition.position;
		expandedNode->left = new Node;
		expandedNode->left->parent = expandedNode;
		expandedNode->right = new Node;
		expandedNode->right->parent = expandedNode;
		totalNodes += 2;
	}
	
	Position removeAboveExternal(const Position& currentPosition)
	{
		Node* currentNode = currentPosition.position;
		Node* currentNodeParent = currentNode->parent;
		Node* sibling = (currentNode == currentNodeParent->left ? currentNodeParent->right : currentNodeParent->left);
		if (currentNodeParent == _root)
		{
			_root = sibling;
			sibling->parent = NULL;
		}
		else
		{
			Node* grandParent = currentNodeParent->parent;
			if (currentNodeParent == grandParent->left)
				grandParent->left = sibling;
			else
				grandParent->right = sibling;
			sibling->parent = grandParent;
		}
		delete currentNode;
		delete currentNodeParent;
		totalNodes -= 2;
		return Position(sibling);
	}

protected:

	void preOrder(Node* currentNode, PositionList& positionList) const
	{
		positionList.push_back(Position(currentNode));
		if (currentNode->left != NULL)
			preOrder(currentNode->left, positionList);
		if (currentNode->right != NULL)
			preOrder(currentNode->right, positionList);
	}

	void inOrder(Node* currentNode, PositionList& positionList) const
	{
		positionList.push_back(Position(currentNode));
		if (currentNode != NULL)
		{
			if (currentNode->left != NULL)
				inOrder(currentNode->left, positionList);
			if (currentNode->right != NULL)
				inOrder(currentNode->right, positionList);
		}
	}

private:
	Node* _root;
	int totalNodes;
};

#endif
