#pragma once

#include <initializer_list>

class  MyLinkedList
{
public:
	struct Node
	{
		int data;
		Node* next;

		Node(int newData, Node* newNext = NULL)
		{
			data = newData;
			next = newNext;
		}
	};

private:
	Node* head, * tail;


public:

	MyLinkedList(int firstVal)
	{
		Node* newNode = new Node(firstVal);
		head = newNode;
		tail = newNode;
	}
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
	/// Returns length of the LinkedList
	/// </summary>
	/// <returns></returns>
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
	/// Adds "newData" to the very beginning of the LinkedList
	/// </summary>
	/// <param name="newData"></param>
	void AddFirst(int newData)
	{
		Node* newNode = new Node(newData);
		newNode->next = head;
		head = newNode;
	}
	/// <summary>
	/// Adds "newData" to the very end of the LinkedList
	/// </summary>
	/// <param name="newData"></param>
	void AddLast(int newData)
	{
		Node* newNode = new Node(newData);

		tail->next = newNode;
		tail = tail->next;
	}

	/// <summary>
	/// Adds "newData" after the first found "searchedData"
	/// </summary>
	/// <param name="searchedData"></param>
	/// <param name="newData"></param>
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
	/// <param name="destroy"> (deletes the element)</param>
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
	/// <param name ="destroy"> (deletes the element) </param>
	/// </summary>
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
	/// <param name ="destroy"> (deletes the element) </param>
	/// </summary>
	int ExtractAt(int index, bool destroy = false)
	{
		int length = GetLength();
		if (index > length)
			return 0;

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
	/// <returns></returns>
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
		return 0;
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

		delete(checkNode);
	}

private:
	void SwapNodes(Node* first, Node* second)
	{
		first->next = second->next;
		second->next = first;
	}

};
