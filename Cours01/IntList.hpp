#pragma once

struct IntList
{
	int value = 0.0;
	IntList* next;
};

static IntList* appendFirst(IntList* l, int value)
{
	IntList* v = (IntList*)malloc(sizeof(IntList));
	v->value = value;
	v->next = l;
	return v;
}

static IntList* appendLast(IntList* l, int value)
{
	if (!l)
		return appendFirst(l, value);

	if (l->next)
		appendLast(l->next, value);
	else
		l->next = appendFirst(nullptr, value);

	return l;
}

static IntList* remove(IntList* l, int value, bool every = false)
{
	if (!l)
		return l;


	if (l->value == value)
	{
		IntList* rest = l->next;
		free(l);
		if (!every)
			return rest;
		return rest = remove(rest, value, every);
	}
	else
	{
		l->next = remove(l->next, value, every);
		return l;
	}

	return l;
}

static int length(IntList* l)
{
	if (!l) return 0;
	else    return 1 + length(l->next);
}

static void printList(IntList* l)
{
	if (!l)
		return;

	if (l->next)
		printf("%d ==> ", l->value);
	else
		printf("%d", l->value);
	printList(l->next);

}
