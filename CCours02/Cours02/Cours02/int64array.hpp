#pragma once

#include <stdint.h>

class Int64Array
{
public:
	int64_t* data;

	int maxSize;
	int curSize;

	Int64Array(int size = 0);

	void setZero(int idx, int nbElement);

	void setZeroOpti(int index, int nbElement);

	~Int64Array();

	void ensure(int size);

	void checkBounds(int pos);

	void set_unsafe(int pos, int64_t value);

	void set(int pos, int64_t value);

	int64_t& get(int pos);

	int64_t& operator[](int idx)
	{
		return get(idx);
	}

	void pushfront(int64_t value);

	void pushback(int64_t value);


	void shiftright(int pos);

	void insert(int pos, int64_t value);

	void insert_ordered(int64_t value);

	int search(int64_t value, int index = 0);

	void clear();

	 void insertionSort(const int64_t* arr, int size);

	void load(const int64_t* arr, int size);

	void append_sorted(const int64_t* arr, int size);

	void printArray(int pos = 0);

	void arraySize();

	int binary_search(int64_t value);


protected:
	void shift_from_to(int target, int index);

	int get_pos_of(int64_t value, int index);

};