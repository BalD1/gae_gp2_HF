// Cours01.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "Toto.h"

/*
int main1()
{
	printf("0: %c \n", '0');
	printf("0.5: %4.1f \n", 0.5);
	printf("toto: %s \n", "toto");

	printf("1...9x2: ");
	for (int j = 0; j < 2; j++)
	{
		for (int i = 1; i < 10; i++)
		{
			printf("%d", i);
		}
	}

	
}
*/

int main()
{
	printf("0\n");

	//allocation statique, sur la pile / stack;
	Toto tStatic;

	printf("%4.2f", tStatic.x);

	//allocation dynamique, sur le tas / heap
	//Toto* tDynamic = new Toto();
}

