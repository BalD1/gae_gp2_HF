#pragma once
#include <iostream>

template<typename Type>
class LinkedList
{
public:
	Type val = {};
	LinkedList* next = nullptr;
	LinkedList* head = nullptr;

	LinkedList(Type value);

	LinkedList(Type value, LinkedList* _next);

	LinkedList* PushFirst(Type value)
	{
		LinkedList* newNode = new LinkedList(value);
		newNode->next = head;
		head = newNode;

		return head;
	}

	LinkedList* RemoveFirst()
	{
		if (head == nullptr)
			return nullptr;
		if (head->next == nullptr)
			return nullptr;

		LinkedList* nextNode = head->next;
		head->next = nextNode->next;
		return head;
	}

	LinkedList* PushBack(Type value)
	{
		LinkedList* node = head;
		while (node->next != nullptr)
		{
			node = node->next;
		}
		node->next = new LinkedList(value);

		return node;
	}

	void PrintList();
};


