#pragma once

template <typename DataType>
class Stack {
private:
	struct Node
	{
		DataType data;
		Node* next;
	};
	Node* head;
public:
	Stack() { head = NULL; }

	void push(DataType element)
	{
		struct Node* newNode;
		newNode = new Node();
		newNode->data = element;
		newNode->next = head;
		head = newNode;
	}

	DataType pop()
	{
		struct Node* temp;
		temp = head;
		DataType poppedValue = head->data;
		head = head->next;
		temp->next = NULL;
		free(temp);
		return poppedValue;
	}

	DataType top()
	{
		return head->data;
	}

	bool empty()
	{
		if (head == NULL)
			return true;
		else 
			return false;
	}
	void print(std::ostream &strm)
	{
		for (Node *p = head; p; p = p->next) {
			strm << p->data << "  ";
		}
		strm << '\n';
	}
};