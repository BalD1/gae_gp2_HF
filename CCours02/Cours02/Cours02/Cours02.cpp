// Cours02.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "int64array.hpp"

#pragma region  rec str

int recStrlen(const char* src)
{
	if (*src != '\0')
		return 1 + recStrlen(++src);

	return 0;
}

int recStrCmp(const char* a, const char* b)
{
	if (a == nullptr && b == nullptr) return 0;
	if (*a == 0 && *b == 0) return 0;

	if (*a == 0)
		return -1;

	if (*b == 0)
		return 1;

	if (*a == *b)
		return recStrCmp(++a, ++b);

	if (*a > *b)
		return +1;

	if (*a < *b)
		return -1;
}

void recStrCpy(const char* src, char* dst)
{
	if (dst == nullptr) return;

	if (*src != '\0')
	{
		*dst = *src;
		recStrCpy(++src, ++dst);
	}
}

const char* recStrChr(const char* src, char c)
{
	if (*src != '\0')
	{
		if (*src == c)
			return src;

		return recStrChr(++src, c);
	}

	return nullptr;
}

const char* recStrStr(const char* src, const char* search)
{
	if (src == nullptr) return nullptr;
	if (*src == '\0') return nullptr;

	if (0 == strcmp(src, search))
		return src;
	else
		return recStrStr(src + 1, search);
}

const char* recStrEnd(const char* src)
{
	if (src == nullptr) return nullptr;
	if (*src != '\0')
		return recStrEnd(++src);

	return src;

	return nullptr;
}

void recStrCat(const char* src, char* dst)
{
	if (src == nullptr) return;
	if (dst == nullptr) return;

	if (*dst == 0)
		recStrCpy(src, dst);
	else
		return recStrCat(src, dst + 1);
}

#pragma endregion

#pragma region int array



#pragma endregion


int main()
{
	printf("-------- recursive str \n\n");
#pragma region  rec str len

	int len = recStrlen("bonjour");
	printf("strlen : %d \n", len);

	printf("strcmp : %d \n", recStrCmp("a", "a"));

	char cpy[10] = { '\0' };
	recStrCpy("salut", cpy);
	printf("strcpy : %s \n", cpy);

	const char* chr = recStrChr("bonjour", 'b');
	printf("strchr : %s \n", chr);

	printf("strstr : %s \n", recStrStr("bonjour", "qsdqsdqsd"));

	printf("strEnd : %s \n", recStrEnd("bonjour"));

	char cpy2[20] = { '\0' };
	recStrCat("bonjour", cpy2);
	recStrCat("salut", cpy2);
	printf("strCat : %s \n", cpy2);

#pragma endregion

	printf("\n-------- int array \n\n");

#pragma region int array

	Int64Array* intArray = new Int64Array(100);

	for (int i = 0; i <= 100; i++)
		intArray->set(i, i);

	intArray->pushfront(50);
	intArray->pushfront(70);
	intArray->pushfront(90);

	intArray->insert(50, 1000);
 
	intArray->printArray();

#pragma endregion

}