#pragma once

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
		//r?cup?rer la don?e ? la case idx et l'affecter
		CheckBounds(idx);
		data[idx] = value;
	};

	int get(int idx)
	{
		//r?cup?rer la donn?e ? la case idx et la retourner		
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

	IntArray reverseArray()
	{
		IntArray result(size);
		for (int i = 0; i < size - 1; i++)
		{
			result.set(i, data[size - i]);
		}
		return result;
	}
};