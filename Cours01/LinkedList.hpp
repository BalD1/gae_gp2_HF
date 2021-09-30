#pragma once

#include <initializer_list>

class  MyLinkedList
{
public:
	struct Node
	{
		int data;
		Node* next;

		/// <summary>
		/// Creates a new Node
		/// </summary>
		/// <param name="newData"> : the new node's data</param>
		/// <param name="(opt)newNext"> : the node pointed by the new node</param>
		Node(int newData, Node* newNext = NULL)
		{
			data = newData;
			next = newNext;
		}
	};

private:
	Node* head, * tail;


public:

	/// <summary>
	/// Creates a new Linked List
	/// </summary>
	/// <param name="firstVal"> : the very first value of the list</param>
	MyLinkedList(int firstVal)
	{	
		Node* newNode = new Node(firstVal);
		head = newNode;
		tail = newNode;
	}
	/// <summary>
	/// Creates a new Linked List
	/// </summary>
	/// <param name="a_args"> : the first N values of the list</param>
	MyLinkedList(std::initializer_list<int> a_args)
	{
		Node* newNode = new Node(0);
		for (auto i : a_args)
		{
			if (head == NULL)
			{
				newNode = new Node(i);

				head = newNode;
				tail = newNode;
			}
			else
			{
				newNode->next = new Node(i);
				newNode = newNode->next;
			}
		}
	}
	
	
	/// <summary>
	/// Returns the length of the LinkedList
	/// </summary>
	/// <returns>The list length, duh</returns>
	int GetLength()
	{
		int length = 0;
		Node* checkNode = head;

		while (checkNode->next != NULL)
		{
			checkNode = checkNode->next;
			length++;
		}
		return length;
	}
	/// <summary>
	/// Adds a new data to the beginning of the list
	/// </summary>
	/// <param name="newData"> : the data that should be added</param>
	void AddFirst(int newData)
	{
		Node* newNode = new Node(newData);
		newNode->next = head;
		head = newNode;
	}
	/// <summary>
	/// Adds a new data to the end of the list
	/// </summary>
	/// <param name="newData"> : the data that should be added</param>
	void AddLast(int newData)
	{
		Node* newNode = new Node(newData);

		tail->next = newNode;
		tail = tail->next;
	}

	/// <summary>
	/// Adds a new data after a given one
	/// </summary>
	/// <param name="searchedData"> : the data after which you wish to add <paramref name="newData"/></param>
	/// <param name="newData"> : the data that should be added</param>
	void AddAfter(int searchedData, int newData)
	{
		Node* newNode = new Node(newData);
		Node* checkNode = head;


		while (checkNode->data != searchedData && checkNode->next != NULL)
		{
			checkNode = checkNode->next;
		}
		if (checkNode->data == searchedData)
			SwapNodes(newNode, checkNode);
		else
		{

		}
	}	
	/// <summary>
	/// Adds a new data after a given node
	/// </summary>
	/// <param name="searchedData"> : the node after which you wish to add <paramref name="newData"/></param>
	/// <param name="newData"> : the data that should be added</param>
	void AddAfter(Node* searchedNode, int newData)
	{
		Node* newNode = new Node(newData);
		Node* checkNode = head;

		while (checkNode != searchedNode)
		{
			checkNode = checkNode->next;
		}

		SwapNodes(newNode, checkNode);
	}

	/// <summary>
	/// Get the first element of the LinkedList, optionnaly destroy it
	/// </summary>
	/// <param name="(opt)destroy"> : should the element be destroyed ?</param>
	/// <returns> returns the first value </returns>
	int ExtractFirst(bool destroy = false)
	{
		if (destroy)
		{
			int value = head->data;
			head = head->next;
			return value;
		}

		return head->data;
	}

	/// <summary>
	/// Get the last element of the LinkedList, optionnaly destroy it
	/// </summary>
	/// <param name ="(opt)destroy"> : should the element be destroyed ?</param>
	/// <returns> returns the last value </returns>
	int ExtractLast(bool destroy = false)
	{
		if (destroy)
		{
			int value = tail->data;
			Node* checkNode = head;

			while (checkNode->next != tail)
				checkNode = checkNode->next;

			tail = checkNode;
			tail->next = NULL;

			return value;
		}
		return tail->data;
	}

	/// <summary>
	/// Get the N element of the LinkedList, optionnaly destroy it
	/// </summary>
	/// <param name="index"> : where is located the wanted value </param>
	/// <param name="(opt)destroy"> : should the element be destroyed ?</param>
	/// <param name="(opt)length"> : the length of the list </param>
	/// <returns> returns value if <paramref name = "index"/> is comrpised in the <paramref name = "length"/>, NULL otherwise </returns>
	int ExtractAt(int index, bool destroy = false, int length = -1)
	{
		if (length <= 0)
			length = GetLength();
		if (index > length)
			return NULL;

		if (index == 0)
			return ExtractFirst(destroy);

		if (index == length)
			return ExtractLast(destroy);
		

		Node* checkNode = head;
		Node* pastNode = head;
		int i = 0;
		do
		{
			i++;
			checkNode = checkNode->next;
			if (i == index)
			{
				if (destroy)
				{
					int value = checkNode->data;

					pastNode->next = checkNode->next;
					length--;
					return value;
				}
				return checkNode->data;
			}
			pastNode = pastNode->next;

		} while (checkNode->next != NULL);
	}

	/// <summary>
	/// Returns the index of the first found occurence of value
	/// </summary>
	/// <param name="value"></param>
	/// <returns>positive index if <paramref name="value"/> exists, -1 if not</returns>
	int FindFirst(int value)
	{
		int index = 0;
		Node* newNode = head;
		while (newNode != NULL)
		{
			if (newNode->data == value)
				return index;
			index++;
			newNode = newNode->next;
		}
		return -1;
	}

	/// <summary>
	/// Deletes every occurence of the given value
	/// </summary>
	/// <param name="value"></param>
	void DeleteEvery(int value)
	{
		Node* tempNode = head;

		while (head->data == value)
		{
			ExtractFirst(true);
		}

		while (tempNode->next != NULL)
		{
			if (tempNode->next->data == value)
			{
				tempNode->next = tempNode->next->next;
			}
			else
			{
				tempNode = tempNode->next;
			}
		}
	}

	/// <summary>
	/// Sorts the linked list
	/// </summary>
	/// <param name="(opt)ascending"> : Should the list be ascending ? </param>
	void Sort(bool ascending = true)
	{
		MergeSort(&head, ascending);
	}

	/// <summary>
	/// Prints the LinkedList in console
	/// </summary>
	void PrintList()
	{
		Node* checkNode = head;

		printf("{ ");
		while (checkNode->next != NULL)
		{
			printf("%d ==> ", checkNode->data);
			checkNode = checkNode->next;
		}
		printf("%d } \n", checkNode->data);

	}

private:
	void SwapNodes(Node* first, Node* second)
	{
		first->next = second->next;
		second->next = first;
	}

	//j'ai mal à la tête
	void MergeSort(Node** headRef, const bool ascending)
	{
		Node* nHead = *headRef;
		Node* low;
		Node* high;

		if ((nHead == NULL) || (nHead->next == NULL)) {
			return;
		}

		FrontBackSplit(nHead, &low, &high);

		MergeSort(&low, ascending);
		MergeSort(&high, ascending);

		*headRef = SortedMerge(low, high, ascending);
	}

	Node* SortedMerge(Node* first, Node* second, const bool ascending)
	{
		Node* result = NULL;

		if (first == NULL)
			return (second);
		else if (second == NULL)
			return (first);

		if (ascending)
		{
			if (first->data <= second->data) {
				result = first;
				result->next = SortedMerge(first->next, second, ascending);
			}
			else {
				result = second;
				result->next = SortedMerge(first, second->next, ascending);
			}
		}
		else
		{
			if (first->data >= second->data) {
				result = first;
				result->next = SortedMerge(first->next, second, ascending);
			}
			else {
				result = second;
				result->next = SortedMerge(first, second->next, ascending);
			}
		}
		return (result);
	}

	void FrontBackSplit(Node* source,
		Node** frontRef, Node** backRef)
	{
		Node* fast;
		Node* slow;
		slow = source;
		fast = source->next;

		while (fast != NULL) {
			fast = fast->next;
			if (fast != NULL) {
				slow = slow->next;
				fast = fast->next;
			}
		}

		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}


};
