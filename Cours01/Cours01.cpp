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

/*
int main()
{
	
	printf("0\n");

	//allocation statique, sur la pile / stack;
	Toto tStatic;

	printf("%4.2f", tStatic.x);

	//allocation dynamique, sur le tas / heap
	//Toto* tDynamic = new Toto();
	
}
*/

struct  Vec
{
	float x;
	float y;
	float z;
};

struct  Vec4
{
	float x;
	float y;
	float z;
	float w;

	void add(float amount)
	{
		x += amount;
		y += amount;
		z += amount;
		w += amount;
	};

	void incr(Vec4 b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		w += b.w;
	};

	void div(float amount)
	{
		x /= amount;
		y /= amount;
		z /= amount;
		w /= amount;
	};
	void div(Vec4 b)
	{
		x /= b.x;
		y /= b.y;
		z /= b.z;
		w /= b.w;
	};

	void mult(float amount)
	{
		x *= amount;
		y *= amount;
		z *= amount;
		w *= amount;
	};
	void mult(Vec4 b)
	{
		x *= b.x;
		y *= b.y;
		z *= b.z;
		w *= b.w;
	};

	void printVec()
	{
		printf("x : %f\ny : %f\nz : %f\nw : %f\n", x, y, z, w);
	};

};

struct  IntArray
{
	int array[];

	int get(int index)
	{
		return array[index];
	}
	void set(int index, int value)
	{
		array[index] = value;
	}
};
int main()
{
	int tab[] = {0,1,2,3,4 };
	int * c = &tab[0];
	*c = 0;

	//printf("*c++ : %d \n", *c++);       //incrémente c et prend le contenu
	//printf("(*c)++ : %d \n", (*c)++);   //prend le contenu de c et incrémente le
	//printf("*++c : %d \n", *++c);       //incrémente c et prend le contenu
	//printf("++*c : %d \n", ++*c);		  //prend le contenu de c et incrémente le
	/*
	Vec* toto = new Vec();

	toto->y = 67;
	(*toto).x = (*toto).y;
	toto->z = toto->y + (*toto).x;

	printf("%f %f %f", toto->x, (*toto).y - 1, toto->z);
	*/

	/*
	Vec4* time = new Vec4();
	time->x = 5;
	time->y = 6;
	time->z = 7;
	time->w = 8;

	time->printVec();
	time->add(1);
	time->printVec();
	*/

	Vec4 time = { 5, 6, 7, 8 };
	time.printVec();
	
	Vec4 timeb = { 12, time.y, time.z * 2, time.w }; 
	timeb.printVec();

}

