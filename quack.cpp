// add code to these functions to make Quack do something useful

#include "quack.h"
#include <iostream>

using namespace std;

// change the value of this variable to be your own name instead of "I. Forgot"
const char	Quack::YOUR_NAME[]{"Julian Kaufman"};

// change the value of this variable to true if you're doing the Premium version
const bool	Quack::PREMIUM_VERSION{true};

Quack::Quack(int capacity, int growBy) :
	// replace these initializations with the ones you actually need
	items{new char[capacity]},
	capacity{capacity},
	growBy{growBy},
	front{0},
	back{0},
	count{0}
{
	initArray();	// you are required to call this function here, and
					// it must be the first thing in the constructor body
}

Quack::~Quack(void)
{
	delete[] items;
}

// items are pushed to successively LOWER slots in the circular array
// (except for when the beginning of the array "wraps around" to the end)
bool Quack::pushFront(const char ch)
{
	
	if (count == 0)
	{
		items[count] = ch;
		count++;
		return true;
	}
	else
	{
		if (front == 0)
			front = capacity - 1;
		else
			front = front - 1;
		items[front] = ch;
		count++;
		return true;
	}
	
	//return false;
}

// items are pushed to successively HIGHER slots in the circular array
// (except for when the end of the array "wraps around" to the beginning)
bool Quack::pushBack(const char ch)
{
	if (count == 0)
	{
		items[count] = ch;
		++count;
		return true;
	}
	else if (count < capacity)
	{
		if (back == capacity -1)
			back = 0;
		else
			++back;
		items[back] = ch;
		count++;
		return true;
	}
	else if (count == capacity)
	{
		newArr = new char[capacity + growBy];
		for (int i = 0; i < (capacity + growBy); i++)
			newArr[i] = '\0';

		for (int i = front, j = 0; j < capacity; i = (i + 1) % capacity, j++)
			newArr[j] = items[i];

		front = 0;
		back = count;
		newArr[back] = ch;
		count++;

		delete [] items;
		capacity = capacity + growBy;
		items = newArr;
		return true;
	}
	else
		return false;
}

bool Quack::popFront(char& ch)
{
	if (count == 0)
	{
		return false;
	}
	else
	{
		if (front == capacity)
			--front;

		ch = items[front];
		front = (front + 1) % capacity;
	}
	count--;
	return true;
}

bool Quack::popBack(char& ch)
{
	if (count == 0)
	{
		return false;
	}
	else
	{
		ch = items[back];
		back = (back == 0 ? capacity - 1 : back - 1);
		--count;
		return true;
	}
}

void Quack::rotate(int r)
{
	
	char ch;
	int i;
	if (count == capacity)
	{
		front = (front + r) % (capacity);
		back = (back + r) % (capacity);
	}
	else if (r > 0)
	{ 
		for (i = 0; i < r; i++)
		{ 
			ch = items[front];
			back = (back + 1) % capacity;
			items[back] = ch;
			front = (front + 1) % capacity;
		}
	}
	else if (r < 0)
	{	
		r = -r;
		for (i = 0; i < r; i++)
		{
			ch = items[back];
			front = (front == 0 ? capacity - 1 : front - 1);
			items[front] = ch;
			back = (back == 0 ? capacity  - 1 : back - 1);
			
			
		}
	}

}

void Quack::reverse(void)
{
	

	int i, temp;
	for (i = 0; i < (capacity/2); i++)
	{
		temp = items[capacity - i - 1];
		items[capacity - i - 1] = items[i];
		items[i] = temp;
	}
}

int	Quack::itemCount(void)
{
	return count;
}

ostream& operator<<(ostream& out, Quack *q)
{
	if (q->count == 0)
	{
		out << "quack: empty" << endl << endl;
		return out;
	}
	int capacity = q->capacity;
	out << "quack: ";
	for (int i = q->front, j = 0; j < q->count; i = (i+1) % capacity, j++)
	{
		
		out << q->items[i];
		//<< ", "

		if (i != q->back)
			out << ", ";
		
	}
	out << endl << endl;
	// returning out is ALWAYS required for an operator<< overload
	return out;
}
