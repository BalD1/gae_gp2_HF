#include <iostream>
#include <vector>

#include "List.hpp"
#include "Tree.hpp"


int main()
{
	Tree<float>* tf = new Tree<float>(66.0f);
	Tree<std::string>* ts = new Tree<std::string>("sapin");

	tf->Insert(500);
	tf->Insert(501);
	Tree<float>* tf2 = tf->Search(500);

	tf->Remove(500);
}

/*
int LinkedList()
{
	List<double>* linkedListDouble = new List<double>(10);

	linkedListDouble->PushFirst(5.5);
	linkedListDouble->PushFirst(50);
	linkedListDouble->PushFirst(500);
	linkedListDouble->Remove(10);
	linkedListDouble->PushBack(100);
	linkedListDouble->PrintList();

	List<int>* linkedListInt = new List<int>(12);
	linkedListInt->PushBack(100);
	linkedListInt->PushBack(100);
	linkedListInt->PushFirst(500);
	linkedListInt->PrintList();

	List<std::string>* linkedListString = new List<std::string>("bonjour");
	linkedListString->PushBack("comment");
	linkedListString->PushBack("ca");
	linkedListString->PushBack("va");
	linkedListString->PrintList();

	std::vector<double> vd = { 10, 60.5, 125645 };

	vd.push_back(20);
	vd.push_back(20);

	auto st = vd.begin();

	vd.insert(st, 100);

	printf("\n\n  -------- for loop ------ \n\n ");
	
	for (int i = 0; i < vd.size(); i++)
	{
		printf("%f ", vd[i]);
	}

	printf("\n\n  -------- foreach loop ------ \n\n ");

	for (auto f : vd)
	{
		printf("%f ", f);
	}

	printf("\n\n  -------- for loop with erase ------ \n\n ");

	for (auto iter = vd.begin(); iter != vd.end();)
	{
		printf("%f ", *iter);
		if (*iter == 1.0)
			iter = vd.erase(iter);
		else
			iter++;
	}

}
*/