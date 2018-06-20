#ifndef STACK_H
#define STACK_H

template<typename T>
class Stack
{
public:
	Stack();
	bool isEmpty() const;
	T peek() const;
	void push(T value);
	T pop();
	int getSize() const;
	~Stack();

private:
	T *elements;
	int size;
	int capacity;
	void ensureCapacity();
};

template<typename T>
Stack<T>::Stack(): size(0), capacity(16)
{
	elements = new T[capacity];
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	return size == 0;
}

template<typename T>
T Stack<T>::peek() const
{
	return (size > 0) ? elements[size - 1] : -1;
}

template<typename T>
void Stack<T>::push(T value)
{
	ensureCapacity();
	elements[size++] = value;
}

template<typename T>
void Stack<T>::ensureCapacity()
{
	if (size >= capacity)	//사이즈가 지금 용량과 같거나 지금 용량보다 크면
	{
		T *old = elements;	//old 배열 생성 & 현재 elements 배열 복사
		capacity = 2 * size;	// 배열 최대 크기를 2배 시킨다.
		elements = new T[size * 2];	// elements를 배열 크기 2배짜리로 생성

		for (int i = 0; i < size; i++)
			elements[i] = old[i];	// 새로 만든 elements에 기존 배열 정보를 다시 채워 넣는다.

		delete[] old;	//사용이 끝난 old를 폐기한다.
	}
}

template<typename T>
T Stack<T>::pop()
{
		return elements[--size];
}

template<typename T>
int Stack<T>::getSize() const
{
	return size;
}

template<typename T>
Stack<T>::~Stack<T>()
{
}

#endif