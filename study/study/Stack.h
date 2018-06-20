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
	if (size >= capacity)	//����� ���� �뷮�� ���ų� ���� �뷮���� ũ��
	{
		T *old = elements;	//old �迭 ���� & ���� elements �迭 ����
		capacity = 2 * size;	// �迭 �ִ� ũ�⸦ 2�� ��Ų��.
		elements = new T[size * 2];	// elements�� �迭 ũ�� 2��¥���� ����

		for (int i = 0; i < size; i++)
			elements[i] = old[i];	// ���� ���� elements�� ���� �迭 ������ �ٽ� ä�� �ִ´�.

		delete[] old;	//����� ���� old�� ����Ѵ�.
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