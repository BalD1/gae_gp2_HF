// Cours01.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "Toto.h"
#include "IntArray.hpp"
#include "LinkedList.hpp"
#include "binaryHeap.hpp"
//#include <SFML/Graphics.hpp>

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

#pragma region Vecs

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

#pragma endregion

#pragma region  fonctionExos



int monstrlen(const char* chaine)
{
	int index = 0;
	while (chaine[index] != 0)
	{
		index++;
	}
	return index;
}

int strlenPointer(const char* chaine)
{
	int index = 0;
	while (*chaine != '\0')
	{
		chaine++;
		index++;
	}

	return index;
}

int forstrlen(const char* chaine)
{
	int length = 1;
	for (int i = 0; i < length; i++)
	{
		if (chaine[i] != 0)
		{
			length++;
		}
	}

	return length - 1;
}

int CountC(const char* maChaine, char c)
{
	int res = 0;
	int len = forstrlen(maChaine);

	for (int i = 0; i < len; i++)
		if (maChaine[i] == c)
			res++;

	return res;
}

void strCopy(char* final, const char *source)
{
	int len = 0;
	for (len = 0; source[len] != '\0'; len++)
		final[len] = source[len];
	final[len] = 0;


}
void strCopy(char* final, const char *source, int nbChar)
{
	int len = 0;
	for (len = 0; source[len] != '\0' && len < nbChar; len++)
		final[len] = source[len];
	final[len] = 0;
}
void strCopyFast(char* dst, const char* src)
{
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
}void strCopyFast(char* dst, const char* src, int nbChar)
{
	while (*src && nbChar > 0)
	{
		*dst = *src;
		dst++;
		src++;
		nbChar--;
	}
	*dst = 0;
}

#pragma endregion

#pragma region tests

int* init()
{
	int i = 10;			//int normal
	int* adrr = &i;		//récupère l'adresse
	return adrr;		//return l'adresse
};

void swap(int* a, int* b)		// swap les valeurs de a et de b sur le tas ?
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubbleSort(int array[], const int arraySize)
{
	int tmp = 0;

	for (int i = 0; i < arraySize - 1; i++)
	{
		for (int j = 0; j < arraySize - i - 1; j++)
		{
			if (*(array + j) > *(array + (j + 1)))
			{
				tmp = *(array + j);
				*(array + j) = *(array + (j + 1));	//this brûle mes eyes 
				*(array + (j + 1)) = tmp;
			}
		}
	}
}

void printArray(int array[], const int arraySize)
{
	if (arraySize == 0)
		return;

	printf("{ \n");
	for (int i = 0; i < arraySize; i++)
		printf("%d : %d \n", i, array[i]);
	printf("} \n");

}

#pragma endregion

static int cmp(const void * v0, const void * v1)
{
	if (*(int*)v0 < *(int*)v1) return -1;
	if (*(int*)v0 > *(int*)v1) return 1;
	return 0;
}
static int inverseCmp(const void * v0, const void * v1)
{
	if (*(int*)v0 > *(int*)v1) return -1;
	if (*(int*)v0 < *(int*)v1) return 1;
	return 0;
}

void IntArray::qsort()
{
	::qsort(data, size, sizeof(int), cmp);

}
void IntArray::inverseQSort()
{
	::qsort(data, size, sizeof(int), inverseCmp);
}

int main()
{

#pragma region  incrementation

	/*
	int tab[] = {0,1,2,3,4 };
	int * c = &tab[0];
	*c = 0;
	*/

	//printf("*c++ : %d \n", *c++);       //incrémente c et prend le contenu
	//printf("(*c)++ : %d \n", (*c)++);   //prend le contenu de c et incrémente le
	//printf("*++c : %d \n", *++c);       //incrémente c et prend le contenu
	//printf("++*c : %d \n", ++*c);		  //prend le contenu de c et incrémente le

#pragma endregion

#pragma region Vecs

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

	/*
	Vec4 time = { 5, 6, 7, 8 };
	time.printVec();

	Vec4 timeb = { 12, time.y, time.z * 2, time.w };
	timeb.printVec();
	*/

#pragma endregion

#pragma region  array

	/*
		IntArray myArray(16);

		for (int i = 0; i < myArray.GetLength(); i++)
		{
			myArray.set(i, i * i);
		}

		myArray.printArray();


		printf("value is at : %d", myArray.searchValue(100));

		//IntArray myArray2 = myArray.reverseArray();
		//myArray2.printArray();
		*/

#pragma endregion

#pragma region  fonctionsExo

	IntArray toto(10);
	int ran = rand() % 100 + 1;
	for (int i = 0; i < 10; i++)
	{
		ran = rand() % 100 + 1;
		toto.set(i, ran);
	}
	toto.qsort();
	toto.printArray();
	toto.inverseQSort();
	toto.printArray();



#pragma region SFML

	/*
	sf::RenderWindow window(sf::VideoMode(200, 200, 64), "test");
	window.setFramerateLimit(30);

	sf::CircleShape shape(10);
	shape.setFillColor(sf::Color::Magenta);
	shape.setPosition(sf::Vector2f(window.getSize().x / 4, window.getSize().y / 4));
	sf::err().rdbuf(NULL);
	shape.move(100, 100);

	sf::Texture mapimage;
	mapimage.loadFromFile("Images/map.png");

	sf::Sprite sprite(mapimage);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			shape.move(sf::Vector2f(-0.5f, 0));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			shape.move(sf::Vector2f(0.5f, 0));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			shape.move(sf::Vector2f(0, -0.5f));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			shape.move(sf::Vector2f(0., 0.5f));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			shape.setFillColor(sf::Color::Transparent);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			shape.setFillColor(sf::Color::Magenta);

		window.clear();
		window.draw(sprite);
		window.draw(shape);
		window.display();
	}
	*/

#pragma endregion


#pragma endregion

#pragma region  tests

	/*
	int a = 10;
	int b = 20;

	printf("a = %d  b = %d \n", a, b);

	swap(&a, &b);		// on envoie l'adresse

	printf("a = %d  b = %d \n", a, b);

	const int arraySize = 5;

	int array[arraySize] = { 10, 20, 5, 18, 100 };
	printf("%d \n", *array);   //array est un pointeur; équivalent de array[0]

	int* arrPoint = array;

	printf("%d \n", *++arrPoint);	//équivalent de array[0 + 1]

	printArray(array, arraySize);

	bubbleSort(array, arraySize);

	printArray(array, arraySize);

	*/

#pragma endregion


}

