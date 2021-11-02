#pragma once

template<typename Type>
class List
{
public: 
	Type val = {};
	List* next = nullptr;
	List* head = nullptr;

	List(Type value)
	{
		val = value;
		head = this;
	}

	List(Type value, List* _next)
	{
		val = value;
		next = _next;
		head = this;
	}

	List* PushFirst(Type value)
	{
		List* newNode = new List(value);
		newNode->next = head;
		head = newNode;

		return head;
	}

	List* Remove(Type value)
	{
		return RemoveAfter(value, this->head);
	}
	List* RemoveAfter(Type value, List* node)
	{
		if (node == nullptr)
			return NULL;
		if (node->next == nullptr)
			return NULL;

		List* nextNode = node->next;
		if (nextNode->val == value)
		{
			node->next = nextNode->next;
			return node;
		}

		return RemoveAfter(value, nextNode);
	}

	List* PushBack(Type value)
	{
		List* node = head;
		while (node->next != nullptr)
		{
			node = node->next;
		}
		node->next = new List(value);

		return node;
	}

	List* FindValue(Type value, List* node)
	{
		if (node == nullptr)
			return nullptr;

		if (node->val == value)
			return node;

		if (node->next != nullptr)
			return FindValue(value, node->next);

		return nullptr;
	}

	void PrintList()
	{
		List* newNode = head;

		while (newNode != nullptr)
		{
			std::cout << newNode->val << "---->";
			newNode = newNode->next;
		}
		printf("\n");
	}
};