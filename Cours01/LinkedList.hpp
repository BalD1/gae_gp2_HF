#pragma once



class  MyLinkedList
{
public:
	struct  Node
	{
		int data;
		Node *next;

		Node(int newData, Node *newNext = NULL)
		{
			data = newData;
			next = newNext;
		}
	};


private:
	Node *head, *tail;


public:
	MyLinkedList(int firstData)
	{
		Node *firstNode = new Node(firstData);

		head = firstNode;
		tail = firstNode;
	}

	void AddLast(int newData)
	{
		Node *newNode = new Node(newData);

		tail->next = newNode;
		tail = tail->next;
	}

	void AddAfter(int searchedData, int newData)
	{
		Node *newNode = new Node(newData);
		Node *checkNode = head;


		while (checkNode->data != searchedData)
		{
			checkNode = checkNode->next;
		}

		SwapNodes(newNode, checkNode);
	}
	void AddAfter(Node *searchedNode, int newData)
	{
		Node *newNode = new Node(newData);
		Node *checkNode = head;

		while (checkNode != searchedNode)
		{
			checkNode = checkNode->next;
		}

		SwapNodes(newNode, checkNode);
	}

	void AddFirst(int newData)
	{

	}

	void PrintList()
	{
		Node *checkNode = head;

		while (checkNode != NULL)
		{
			printf("%d, ", checkNode->data);
			checkNode = checkNode->next;
		}
	}

private:
	void SwapNodes(Node *first, Node *second)
	{
		first->next = second->next;
		second->next = first;
	}

};
