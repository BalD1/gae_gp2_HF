#include "LinkedList.hpp"

template<typename Type>
LinkedList<Type>::LinkedList(Type value)
{
	val = value;
	head = this;
}

template<typename Type>
LinkedList<Type>::LinkedList(Type value, LinkedList* _next)
{
	val = value;
	next = _next;
	head = this;
}

template<typename Type>
void LinkedList<Type>::PrintList()
{
	LinkedList* newNode = head;

	while (newNode != nullptr)
	{
		std::cout << newNode->val << "---->" << '\n';
		newNode = newNode->next;
	}
}
