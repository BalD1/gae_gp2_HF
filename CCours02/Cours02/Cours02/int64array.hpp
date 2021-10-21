#pragma once

#include <stdint.h>

class Int64Array
{
public:
	int64_t* data;

	int maxSize;
	int curSize;

	Int64Array(int size = 0)
	{
		if (size < 0) size = 0;
		this->curSize = size;
		if (size <= 0)
			maxSize = 16;
		else
			maxSize = size;

		data = (int64_t*)malloc(maxSize * sizeof(int64_t));

		setZero(0, maxSize);
	}

	void setZero(int idx, int nbElement)
	{
		if (idx <= maxSize)
		{
			data[idx] = 0;
			setZero(++idx, maxSize);
		}
	}

	~Int64Array()
	{
		free(data);
		data = nullptr;
		maxSize = 0;
		curSize = 0;
	}

	void ensure(int size)
	{
		if (size < maxSize)
			return;

		int oldSize = maxSize;

		maxSize = size;
		data = (int64_t*)realloc(data, maxSize * sizeof(int64_t));
		setZero(oldSize, maxSize);
	}

	void checkBounds(int pos)
	{
		if (pos < 0)
			throw ("exception : negative index");
		if (pos > curSize)
			ensure(pos);
	}

	void set_unsafe(int pos, int64_t value)
	{
		data[pos] = value;
	}

	void set(int pos, int64_t value)
	{
		checkBounds(pos + 1);

		data[pos] = value;
		if (pos >= curSize)
			curSize = pos + 1;
	}

	int64_t& get(int pos)
	{
		ensure(pos + 1);
		if (pos >= curSize)
			curSize = pos + 1;
		return data[pos];
	}

	int64_t& operator[](int idx)
	{
		return get(idx);
	}

	void pushfront(int64_t value)
	{
		insert(0, value);
	}

	void pushback(int64_t value)
	{
		set(curSize, value);
	}

	void shiftright(int pos)
	{
		ensure(pos);
		set(pos, data[pos - 1]);
		if (pos > 0)
			shiftright(--pos);
	}

	void insert(int pos, int64_t value)
	{
		shiftright(curSize - pos);
		set(pos, value);
	}

	void printArray(int pos = 0)
	{
		if (pos <= maxSize)
		{
			printf("%d : %d \n", pos, data[pos]);
			printArray(++pos);
		}
	}


};