#include "int64array.hpp"
#include <stdint.h>
#include <iostream>


Int64Array::Int64Array(int size)
{
	if (size < 0) size = 0;
	this->curSize = size;
	if (size <= 0)
		maxSize = 16;
	else
		maxSize = size;

	data = (int64_t*)malloc(maxSize * sizeof(int64_t));
	setZeroOpti(0, maxSize);
}

void Int64Array::setZero(int idx, int nbElement)
{
	if (idx <= maxSize)
	{
		data[idx] = 0;
		setZero(++idx, maxSize);
	}
}

void Int64Array::setZeroOpti(int index, int nbElement)
{
	for (int i = index; i < nbElement; i++)
		data[index] = 0;
}


Int64Array::~Int64Array()
{
	free(data);
	data = nullptr;
	maxSize = 0;
	curSize = 0;
}

void Int64Array::ensure(int size)
{
	if (size < maxSize)
		return;

	int oldSize = maxSize;
	maxSize = size * 1.75;

	data = (int64_t*)realloc(data, maxSize * sizeof(int64_t));
	setZeroOpti(oldSize, maxSize - oldSize);
}

void Int64Array::checkBounds(int pos)
{
	if (pos < 0)
		throw ("exception : negative index");
	if (pos > curSize)
		ensure(pos);
}

void Int64Array::set_unsafe(int pos, int64_t value)
{
	data[pos] = value;
}

void Int64Array::set(int pos, int64_t value)
{
	checkBounds(pos + 1);

	data[pos] = value;
	if (pos >= curSize)
		curSize = pos + 1;
}

int64_t& Int64Array::get(int pos)
{
	ensure(pos + 1);
	if (pos >= curSize)
		curSize = pos + 1;
	return data[pos];
}

void Int64Array::pushfront(int64_t value)
{
	insert(0, value);
}

void Int64Array::pushback(int64_t value)
{
	set(curSize, value);
}

void Int64Array::shiftright(int pos)
{
	if (pos < 0)
		pos = 0;

	ensure(pos);
	shift_from_to(pos, maxSize);
}

void Int64Array::insert(int pos, int64_t value)
{
	if (pos < 0)
		pos = 0;

	shiftright(pos);
	set((pos), value);
}

void Int64Array::insert_ordered(int64_t value)
{
	int pos = search(value);
	insert(pos, value);
}

int Int64Array::search(int64_t value, int index)
{
	if (index >= curSize)
		return curSize;

	if (data[index] > value)
		return index;

	return search(value, ++index);
}

void Int64Array::clear()
{
	curSize = 0;
}

void Int64Array::append_sorted(const int64_t* arr, int size)
{
	if (size <= 0)
		return;
	insert_ordered(arr[0]);
	append_sorted(arr + 1, size - 1);
}

void Int64Array::insertionSort(const int64_t* arr, int size)
{
	clear();
	load(arr, size);

	for (int i = 1; i <= size-1; i++)
	{
		int j = i;
		while ((j > 0) && (data[j] < data[j - 1]))
		{
			int64_t tmp = data[j];
			data[j] = data[j-1];
			data[j-1] = tmp;
			j--;
		}
	}
}

void Int64Array::load(const int64_t* arr, int size)
{
	if (size == 0)
		return;
	set(curSize, arr[0]);
	load(arr + 1, size - 1);
}

int Int64Array::binary_search(int64_t value)
{
	return get_pos_of(value, curSize / 2);

	return -1;
}

void Int64Array::printArray(int pos)
{
	if (pos < curSize)
	{
		printf("%d : %d \n", pos, data[pos]);
		printArray(++pos);
	}
}

void Int64Array::arraySize()
{
	printf("current size : %d \nmax size : %d\n", curSize, maxSize);
}

void Int64Array::shift_from_to(int target, int index)
{
	set(index, data[index - 1]);
	if (index != target)
	{
		if (index > 0)
			shift_from_to(target, --index);
	}

	return;
}

int Int64Array::get_pos_of(int64_t value, int index)
{
	if (data[index] == value)
		return index;
	if (index <= 0 || index >= curSize - 1)
		return -1;

	if (data[index] > value)
		return get_pos_of(value, index / 2);

	if (data[index] < value)
		return get_pos_of(value, ((index + curSize) / 2));

}
