
#include "pch.h"
#include <iostream>
#include "IntArray.hpp"

double IntArray::tempRes = 0;

void Memcpy(char* dst, const char* src, int len)
{
	for (int i = 0; i < len; i++)
	{
		dst[i] = src[i];
	}
}

void MemcpyWhile(char* dst, const char* src)
{
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
}

const char* StrChr(const char* grange, char chat)
{
	while (*grange)
	{
		if (*grange == chat)
			return grange;

		grange++;
	}

	return nullptr;
}

const char* StrStr(const char* a, const char* b)
{
	size_t lengthOfb = strlen(b);

	while (*a)
	{
		bool found = true;
		for (int i = 0; i < lengthOfb; i++)
		{
			if (a[i] != b[i])
			{
				a++;
				found = false;
				break;
			}
		}
		if (found)
			return a;
	}

	return nullptr;
}

int add(int a, int b)
{
	if (b > 0)
		a = add(++a, --b);

	return a;
}

int add2(int a, int b)
{
	if (b == 0)
		return a;
	else if (b > 0)
		return 1 + add(a , b - 1);
	else
		return -1 + add(a, b + 1);
}

int sub(int a, int b)
{
	return (a, -b);
}

int mul(int a, int b)
{
	if (b == 0 || a == 0)
		return 0;
	if (b < 0)
		return sub(0, mul(a, sub(0, b)));
		//return -mul(a, -b);
	else
		return add(a, mul(a, b - 1));
}

int divInt(int a, int b)
{
	if (a == 0) return 0;
	if (b == 1) return a;
	if (b == 0) throw ("division by zero pas bien");
	if (a < b) return 0;
	
	if (a < 0)
		return sub(0, divInt(sub(0, a), b));
	else
		return 1 + divInt(sub(a, b), b);
}

int main()
{
	/*
	const size_t length = 150;

	//int myArray[length] = {};
	//int* myArray = (int*) malloc(length * sizeof(int));
	int * myArray = new int[length];

	for (int i = 0; i < length; i++)
	{
		myArray[i] = i * i;
	}
	*/

	IntArray myArray(150);

	const size_t arraylength = myArray.GetLength();

	for (int i = 0; i < arraylength; i++)
	{
		myArray.set(i, i*i);
	}

	myArray.reverseArray();

	std::function<void(int)> foo = [](int value)
	{
		printf("%d\n", value);
	};

	myArray.iter(foo);

	printf("%lf \n", myArray.sum());

	int q[4] = { 42, 69, 666, 80082 };
	IntArray* copie = IntArray::fromArray(q, 4);

	copie->printArray();

	printf("--------- \n Memcopy : \n");

	int s[4] = { 0,0,0,0 };
	int t[4] = { 0,1,2,3 };

	MemcpyWhile((char*)s, (char*)t);

	for (int i = 0; i < 4; i++)
		printf("%d : %d \n", i, s[i]);


	printf("---------- \n Search : \n");

	const char* toto = StrStr("sapin", "i");

	printf("---------- \n maths recursives : \n");

	int res = divInt(4, 2);

	printf("%d", res);

	return 0;
}

