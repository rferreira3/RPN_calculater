//This is a file for the stack used in the binary tree 
#ifndef DEFINED_STACK_H_
#define DEFINED_STACK_H_

//  Represents a generic stack abstract data type
//  A stack can hold up to N objects of type T
template <typename T, int N>
class Stack {
	// Add your code here . . .
	T stack[N]; //declares stack to be member of stack class 
	//int size;
	int counter;
public:
	Stack()
	{
		counter = 0;
	}

	bool push(T element)
	{
		if (counter < N)
		{
			stack[counter] = element;
			counter++;
			return true;
		}
		return false;
	}
	T pop()
	{
		if (counter >= 0)
		{
			counter--;
			auto temp = stack[counter];
			//delete stack[counter];
			return temp;

		}
	}
	T top(const T&)
	{
		if (counter > -1)
		{
			return stack[counter];
		}
	}
	bool full(const T&)
	{
		return counter == N - 1;
	}
	bool empty(const T&)
	{
		return counter == -1;
	}


};

#endif
