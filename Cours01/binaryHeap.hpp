#pragma once

#include <initializer_list>
#include <string>

class MyBinaryHeap
{
public:
	struct Node
	{
		int data;
		Node* leftChild;
		Node* rightChild;

		Node(int newData, Node* newLeft = nullptr, Node* newRight = nullptr)
		{
			data = newData;
			leftChild = newLeft;
			rightChild = newRight;
		}
	};

private:
	Node* head;

public:

	MyBinaryHeap(int firstVal)
	{
		head = new Node(firstVal);
	}
	MyBinaryHeap(std::initializer_list<int> a_args)
	{
		Node* newNode = new Node(0);
		for (auto i : a_args)
		{
			if (head == NULL)
			{
				newNode = new Node(i);

				head = newNode;
			}
			else
			{
				AddValue(i);
			}
		}
	}

	void AddValue(int newData)
	{
		Node* newNode = new Node(newData);
		Node* cursorNode = head;
		Node* previousNode;

		do
		{
			previousNode = cursorNode;
			if (newData > cursorNode->data)
			{
				cursorNode = cursorNode->rightChild;
				if (cursorNode == NULL)
				{
					previousNode->rightChild = newNode;
					break;
				}
			}
			else
			{
				cursorNode = cursorNode->leftChild;
				if (cursorNode == NULL)
				{
					previousNode->leftChild = newNode;
					break;
				}
			}
		} while (cursorNode != NULL);
	}

	int FindMax()
	{
		Node* cursorNode = head;
		do
		{
			cursorNode = cursorNode->rightChild;
		} while (cursorNode->rightChild != nullptr);

		return cursorNode->data;
	}

	int FindMin()
	{
		Node* cursorNode = head;
		do
		{
			cursorNode = cursorNode->leftChild;
		} while (cursorNode->leftChild != nullptr);

		return cursorNode->data;
	}

	void printTree(const std::string& output, Node* cursorNode, bool isLeft)
	{
		if (cursorNode != nullptr)
		{

			std::cout << output;
			std::cout << (isLeft ? "L---" : "R---");

			std::cout << cursorNode->data << std::endl;

			printTree(output + (isLeft ? "|   " : "    "), cursorNode->leftChild, true);
			printTree(output + (isLeft ? "|   " : "    "), cursorNode->rightChild, false);
		}

	}
	void printTree()
	{
		printTree("", head, false);
	}

};