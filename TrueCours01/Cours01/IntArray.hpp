#pragma once

#include <functional>

class IntArray {
public:
	int* data = nullptr;
	int size;

public:

	IntArray()
	{
		data = new int[size = 65536];
	}

	IntArray(int size)
	{
		//faire l'allocation dynamique de 'data' qui sera de taille suffisament grande
		this->size = size;
		data = new int[size];
	};

	~IntArray()
	{
		delete[] data;
	}

	void CheckBounds(int idx)
	{
		if (idx < 0 || idx >= size)
			throw "exception: out of bounds";
	}

	int GetLength()
	{
		return size;
	}

	void set(int idx, int value)
	{
		//récupérer la donée à la case idx et l'affecter
		CheckBounds(idx);
		data[idx] = value;
	};

	int get(int idx)
	{
		//récupérer la donnée à la case idx et la retourner		
		CheckBounds(idx);
		return data[idx];
	};


	void resize(int newSize)
	{
		if (size >= newSize)
			return;
		data = (int*)realloc(data, newSize * sizeof(int));
		memset(data + size, 0, (newSize - size) * sizeof(int));
		size = newSize;
	}

	void insert(int value)
	{
		int index = 0;
		while ((index < size) && (data[index] < value))
			index++;
		insertAt(index, value);
	}

	void insertAt(int index, int value)
	{
		if (index < 0)
			return;

		int oldSize = size;
		int toResize;

		if (index > size)
			toResize = index - size + 1;
		else
			toResize = 1;

		resize(size + toResize);
		//resize(std::max<int>(index+1, size+1));

		for ( ; oldSize >= index; oldSize--)
		{
			data[oldSize] = data[oldSize - 1];
		}

		data[index] = value;
	}

	void qsort();
	void inverseQSort();

	void printArray()
	{
		for (int i = 0; i < size; i++)
		{
			printf("%d : %d \n", i, data[i]);
		}
	}

	int searchValue(int value)
	{
		for (int i = 0; i < size; i++)
		{
			if (data[i] == value)
				return i;
		}
	}


	void reverseArray()
	{
		int tmp;
		for (int i = 0; i < size / 2; i++)
		{
			tmp = data[i];
			data[i] = data[size - i - 1];
			data[size - i - 1] = tmp;
		}
	}

	void iter(std::function<void(int)> f)
	{
		for (int i = 0; i < size; i++)
		{
			f(data[i]);
		}
	}

	static double tempRes;

	double sum()
	{
		tempRes = 0.0;
		std::function<void(int)> add = [](int value)
		{
			tempRes += value;
		};
		iter(add);
		return tempRes;
	}

	static IntArray* fromArray(int* data, int len)
	{
		IntArray* newArray = new IntArray(len);
		
		for (int i = 0; i < len; i++)
			newArray->set(i, data[i]);

		return newArray;
	}


};