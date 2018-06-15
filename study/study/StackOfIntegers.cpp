#include "stdafx.h"
#include "StackOfIntegers.h"


StackOfIntegers::StackOfIntegers()
{
	size = 0;
}

bool StackOfIntegers::isEmpty() const
{
	return size==0;
}

int StackOfIntegers::peek() const
{
	return (size > 0) ? elements[size - 1] : -1;
}

void StackOfIntegers::push(int value)
{
	(size < 100) ? elements[size++] = value : elements[size] = value;	
}

int StackOfIntegers::pop()
{
	if(!isEmpty() && size > 0)
		return elements[--size];
	else
		return -1;
}

int StackOfIntegers::getSize() const
{
	return size;
}

StackOfIntegers::~StackOfIntegers()
{
}
