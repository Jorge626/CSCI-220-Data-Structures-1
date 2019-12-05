#pragma once
#pragma warning( disable )
#ifndef BST_H
#define BST_H

#include "BinaryTree.h"
#include "RuntimeException.h"

template <typename BinaryTreeElement>
class SearchTree
{
public:
	typedef typename BinaryTreeElement::CountyCode C;
	typedef typename BinaryTreeElement::CountyPopulation P;
	typedef typename BinaryTreeElement::CountyName N;

	class Iterator;

	SearchTree() : binaryTree(), totalEntries(0)
	{
		binaryTree.addRoot();
		binaryTree.expandExternal(binaryTree.root());
	};

	int size() const {
		return totalEntries;
	}

	bool empty() const {
		return totalEntries == 0;
	}

	Iterator find(const C& code)
	{
		TPos positionToFind = finder(code, root());
		if (!positionToFind.isExternal())
			return Iterator(positionToFind);
		else
			return end();
	}

	Iterator insert(const C& c, const P& p, const N& n)
	{
		TPos tempInsert = inserter(c, p, n);
		setHeight(tempInsert);
		rebalance(tempInsert);
		return Iterator(tempInsert);
	}

	void erase(const C& c) throw(NonexistentElement)
	{
		TPos v = finder(c, root());			// find in base tree
		if (Iterator(v) == end())			// not found?
			throw NonexistentElement("Erase of nonexistent");
		TPos w = eraser(v);					// remove it
		rebalance(w);					// rebalance if needed
	}

	void erase(const Iterator& currentPosition)
	{
		eraser(currentPosition.position);
	}

	Iterator begin()
	{
		TPos currentPosition = root();
		while (currentPosition.isInternal())
			currentPosition = currentPosition.left();
		return Iterator(currentPosition.parent());
	}

	Iterator end()
	{
		return Iterator(binaryTree.root());
	}

protected:
	typedef BinaryTree<BinaryTreeElement> linkedBinaryTree;
	typedef typename linkedBinaryTree::Position TPos;
	TPos root() const { return binaryTree.root().left(); }

	TPos finder(const C& code, TPos currentPosition)
	{
		if (currentPosition.isExternal())
			return currentPosition;
		if (code < (*currentPosition).countyCode())
			return finder(code, currentPosition.left());
		else if ((*currentPosition).countyCode() < code)
			return finder(code, currentPosition.right());
		else return currentPosition;
	}

	TPos inserter(const C& code, const P& population, const N& name)
	{
		TPos currentPosition = finder(code, root());
		if (!currentPosition.isExternal())
		{
			(*currentPosition).setCountyPopulation(population);
			(*currentPosition).setCountyName(name);
		}
		else
		{
			binaryTree.expandExternal(currentPosition);
			(*currentPosition).setCountyCode(code);
			(*currentPosition).setCountyPopulation(population);
			(*currentPosition).setCountyName(name);
			totalEntries++;
		}
		return currentPosition;
	}

	TPos eraser(TPos& currentPosition)
	{
		TPos tempPosition;
		if (currentPosition.left().isExternal())
			tempPosition = currentPosition.left();
		else if (currentPosition.right().isExternal())
			tempPosition = currentPosition.right();
		else
		{
			tempPosition = currentPosition.right();
			do
			{
				tempPosition = currentPosition.right();
			} while (!tempPosition.isExternal());
			TPos newPosition = tempPosition.parent();
			(*currentPosition).setCountyCode((*newPosition).countyCode());
			(*currentPosition).setCountyPopulation((*newPosition).countyPopulation());
			(*currentPosition).setCountyName((*newPosition).countyName());
		}
		totalEntries--;
		return binaryTree.removeAboveExternal(tempPosition);
	}

	int height(const TPos& currentPosition) const
	{
		return (currentPosition.isExternal() ? 0 : currentPosition.height());
	}

	void setHeight(TPos currentPosition)
	{
		int hl = height(currentPosition.left());
		int hr = height(currentPosition.right());
		currentPosition.setHeight(1 + std::max(hl, hr));
	}

	bool isBalanced(const TPos& v) const
	{
		int bal = height(v.left()) - height(v.right());
		return ((-1 <= bal) && (bal <= 1));
	}

	void rebalance(const TPos& v)
	{
		TPos z = v;
		while (!(z == root())) {			// rebalance up to root
			z = z.parent();
			setHeight(z);					// compute new height
			if (!isBalanced(z)) {				// restructuring needed
				TPos x = tallGrandchild(z);
				z = restructure(x);				// trinode restructure
				setHeight(z.left());				// update heights
				setHeight(z.right());
				setHeight(z);
			}
		}
	}

	TPos tallGrandchild(const TPos& z) const {
		TPos zl = z.left();
		TPos zr = z.right();
		if (height(zl) >= height(zr))			// left child taller
			if (height(zl.left()) >= height(zl.right()))
				return zl.left();
			else
				return zl.right();
		else 						// right child taller
			if (height(zr.right()) >= height(zr.left()))
				return zr.right();
			else
				return zr.left();
	}

	TPos restructure(const TPos x)
	{
		if (x.isExternal())
			binaryTree.expandExternal(x);
		
		TPos y = x.parent();
		TPos z = y.parent();
		TPos a, b, c, T0, T1, T2, T3;

		if (z.left() == y && y.left() == x)
		{
			a = x;
			b = y;
			c = z;
			T0 = a.left();
			T1 = a.right();
			T2 = b.right();
			T3 = c.right();
		}

		else if (z.right() == y && y.right() == x)
		{
			a = z;
			b = y;
			c = x;
			T0 = a.left();
			T1 = b.left();
			T2 = c.left();
			T3 = c.right();
		}

		else if (z.left() == y && y.right() == x)
		{
			a = x;
			b = y;
			c = z;
			T0 = a.left();
			T1 = b.left();
			T2 = b.right();
			T3 = c.right();
		}

		else if (z.right() == y && y.left() == x)
		{
			a = x;
			b = y;
			c = z;
			T0 = z.left();
			T1 = b.left();
			T2 = b.right();
			T3 = c.right();
		}

		if (z.isRoot())
			b = root();

		b.left() = a;
		b.right() = c;
		a.parent() = b;
		c.parent() = b;
		a.left() = T0;
		a.right() = T1;
		T0.parent() = a;
		T1.parent() = a;
		c.left() = T2;
		c.right() = T3;

		return b;
	}

private:
	linkedBinaryTree binaryTree;
	int totalEntries, ht;
	std::string countyCode, countyName, countyPopulation;

public:
	class Iterator
	{
	private:
		TPos position;
	public:
		Iterator(const TPos& currentPosition) :position(currentPosition) { };

		BinaryTreeElement operator*()
		{
			return *position;
		}

		bool operator==(const Iterator& comparedPosition) const
		{
			return position == comparedPosition.position;
		}

		bool operator!=(const Iterator& comparedPosition) const
		{
			return !(*this == comparedPosition);
		}

		Iterator& operator++()
		{
			TPos tempPosition = position.right();
			if (tempPosition.isInternal())
			{
				do
				{
					position = tempPosition;
					tempPosition = tempPosition.left();
				} while (tempPosition.isInternal());
			}
			else
			{
				tempPosition = position.parent();
				while (position == tempPosition.right())
				{
					position = tempPosition;
					tempPosition = tempPosition.parent();
				}
				position = tempPosition;
			}
			return *this;
		}

		friend class SearchTree;
	};

};

#endif
