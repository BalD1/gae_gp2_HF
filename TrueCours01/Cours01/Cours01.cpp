
#include "pch.h"
#include <iostream>
#include "IntArray.hpp"

double IntArray::tempRes = 0;

#pragma region str func

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

#pragma endregion

#pragma region  RecursivesMaths

int add(int a, int b) { //avec que des +1,-1, return, apppels recursifs{
	if (b == 0)
		return a;
	else if (b > 0)
		return 1 + add(a, b - 1);
	else
		return -1 + add(a, b + 1);
}
int sub(int a, int b) {
	return add(a, -b);
}

int mul(int a, int b) { // avec des additions
	if (b == 0) return 0;
	if (a == 0) return 0;
	if (b < 0)
		//return sub(0, mul(a, sub(0, b)));
		return -mul(a, -b);
	else
		return add(a, mul(a, b - 1));
}

int mulExplicit(int a, int b, int tempResult = 0)
{
	if (a == 0) return tempResult;
	if (b == 0) return tempResult;

	if (b > 0)
		return mulExplicit(a, b - 1, tempResult + a);
	else
		return mulExplicit(a, -b, -tempResult);
}

int divInt(int a, int b) // avec des soustractions utiliser une fonction intermédiaire 
{
	if (a == 0) return 0;
	if (b == 1) return a;
	if (b == 0) throw "division by zero";
	if (a < 0)  return sub(0, divInt(sub(0, a), b));
	if (a < b)  return 0;
	return 1 + divInt(sub(a, b), b);
}

int divIntExplicit(int a, int b, int tempResult = 0)
{
	if (a == 0) return 0;
	if (b == 1) return a;
	if (b == 0) throw "division by zero";

}

int mod(int a, int b)
{
	return sub(a, mul(divInt(a, b), b));
}

int mod2(int a, int b)
{
	return a - divInt(a, b) * b;
}

int sqr(int a)
{
	return mul(a, a);
}

int lenManhattan(int vecX, int vecY)
{
	return add(vecX, vecY);
}

#pragma endregion

#pragma region  Recursive str

int recStrLen(const char* str)
{
	if (nullptr == str)
		return 0;
	if (*str == 0)
		return 0;
	if (str)
		return 1 + recStrLen(str + 1);
}

void recStrnCpy(const char* src, char* dst, int nbChar)
{
	if (*src != '\0' && nbChar > 0)
	{
		*dst = *src;
		recStrnCpy(src + 1, dst + 1, nbChar - 1);
	}
}

void recStrCpy(const char* src, char* dst)
{
	recStrnCpy(src, dst, recStrLen(src));
}

void recZeroMemory(void* bloc, int nbByte)
{
	char* src = (char*)bloc;
	if (src != nullptr && nbByte > 0)
	{
		src[0] = 0;
		recZeroMemory(++src, --nbByte);
	}
}

void recStrMemCpy(const void* src, void* dst, size_t num)
{
	const char* cSrc = (char*)src;
	char* cDst = (char*)dst;
	/*
	if (*cSrc != '\0' && num > 0)
	{
		*cDst = *cSrc;
		recStrMemCpy(cSrc + 1, cDst + 1, num - 1);
	}
	*/
	recStrnCpy(cSrc, cDst, num);
}

const char* recStrChr(const char* str, char token)
{
	if (*str != '\0')
	{
		if (*str == token)
			return str;

		return recStrChr(++str, token);
	}

	return nullptr;
}

bool isPrefix(const char* str, const char* sub)
{
	if (sub == nullptr)
		return false;
	if (str == nullptr)
		return false;
	if (*sub == '\0')
		return true;

	if (*str != *sub)
		return false;

	return isPrefix(++str, ++sub);
}


const char* recStrStr(const char* a, const char* b)
{	
	if (*a != '\0')
		return isPrefix(a, b) ? a : recStrStr(++a, b);

	return nullptr;
}

char* findEnd(char* str)
{
	if (str == nullptr)
		return nullptr;
	if (*str == '\0')
		return str;
	return findEnd(++str);
}

char* recStrCat(char* dst, const char* src)
{
	if (nullptr == dst)
		return nullptr;
	if (nullptr == src)
		return nullptr;

	char* dstEnd = findEnd(dst);
	recStrCpy(src, dstEnd);
	return dst;
}

int recStrCmp(const char* a, const char* b)
{
	if (a == nullptr && b == nullptr)
		return 0;
	if (a == nullptr)
		return -1;
	if (b == nullptr)
		return 1;

	if (*a != '\0' && *b != '\0')
	{
		if (*a > * b)
			return +1;
		if (*a < *b)
			return -1;

		if (*a == *b)
			recStrCmp(++a, ++b);
	}
}


#pragma endregion


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

#pragma region n func

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

#pragma endregion

#pragma region maths rec	
	
	printf("---------- \n maths recursives : \n");

	int res = mulExplicit(-27, 98);

	printf("%d \n", res);

#pragma endregion

#pragma region str rec

	printf("---------- \n str recursives : \n");

	int len = recStrLen("bonjour");
	printf("str len : %d \n", len);

	char dst[256] = {};
	recStrCpy("yo les djeuns ca se pose oklm ou oiq \n", dst);

	printf("str cpy : %s", dst);

	recZeroMemory(dst, 256);

	recStrMemCpy("wesh la mif", dst,  11);
	printf("str memcpy : %s \n", dst);

	const char* chr = recStrChr(dst, 'm');
	printf("str chr : %s \n", chr);

	bool isPartof = isPrefix(dst, "wesh");
	printf("str is prefix : %s \n", isPartof?"true":"false");

	printf("str str : %s \n", recStrStr(dst, "la"));

	printf("str cmp : %d \n", recStrCmp("bjr", "bJr"));

#pragma endregion

	return 0;
}

