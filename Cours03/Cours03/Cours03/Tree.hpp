#pragma once

template<typename Value>
class Tree
{
public:
	Value data = {};
	Tree* leftChild = nullptr;
	Tree* rightChild = nullptr;

	Tree(Value val)
	{
		this->data = val;
	}

	/*
	Tree* Insert(Value val, Tree* node)
	{
		if (val < data)
		{
			if (leftChild == nullptr)
			{
				leftChild = new Tree(val);
				return leftChild;
			}
			else
				return Insert(val, leftChild);
		}
		else
		{
			if (rightChild == nullptr)
			{
				rightChild = new Tree(val);
				return rightChild;
			}
			else
				return Insert(val, rightChild);
		}

		return nullptr;
	}
	*/
	Tree* Insert(Value val)
	{
		if (val < data)
		{
			if (leftChild)
				leftChild->Insert(val);
			else
				leftChild = new Tree(val);
		}
		else
		{
			if (rightChild)
				rightChild->Insert(val);
			else
				rightChild = new Tree(val);
		}

		return this;
	}

	Tree* Remove(Value o)
	{
		if (data == o)
		{
			auto _l = leftChild;
			auto _r = rightChild;
			if (!leftChild)
			{
				delete this;
				return _r;
			}
			else if (!rightChild)
			{
				delete this;
				return _l;
			}
			else
			{
				leftChild->Merge(rightChild);
				delete this;
				return _l;
			}
		}
		else
		{
			if (o < data)
			{
				if (leftChild)
					leftChild = leftChild->Remove(o);
			}
			else
			{
				if (rightChild)
					rightChild = rightChild->Remove(o);
			}
			return this;
		}
	}

	Tree* Merge(Tree* other)
	{
		Value vo = other->data;

		Insert(vo);

		if (other->leftChild)
			Merge(other->leftChild);
		if (other->rightChild)
			Merge(other->rightChild);

		delete other;

		return this;
	}

	Tree* Search(Value val)
	{
		if (val == this->data)
			return this;

		if (leftChild == nullptr && rightChild == nullptr)
			return nullptr;

		if (val < data)
		{
			if (leftChild)
				return leftChild->Search(val);
		}
		else
		{
			if (rightChild)
				return rightChild->Search(val);
		}

		return nullptr;
	}
};