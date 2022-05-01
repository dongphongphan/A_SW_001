/* Phong - self learning data structure STACK
/  1. Implement stack by using vector
/  2. Implement stack by using link list
*/

#include <iostream>
#include <vector>

template <typename T>
class myStack
{
public:
	myStack(){}
	~myStack(){}
	void push(T in)
	{
		element.push_back(in);
	}
	T pop()
	{
		if(isEmpty()) 
		{
			std::cout<<"error pop empty stack"<<std::endl;
			return -1;
		}
		T ret = element.back();
		element.pop_back();
		return ret;
	}
	int top()
	{
		return element.back();
	}
	bool isEmpty()
	{
		return(element.empty());
	}
	void display()
	{
		for(auto i : element) std::cout << i <<" ";
		std::cout << std::endl;
	}
private:
	std::vector<T> element;
};

int main(int argc, char** argv) {
	
	myStack<int> stk;
	stk.push(1);
	stk.push(10);
	stk.push(4);
	stk.display();
	stk.pop();
	stk.display();
	stk.push(7);
	stk.push(8);
	stk.display();
	std::cout <<"top "<<stk.top() <<std::endl;
	stk.pop();
	stk.pop();
	stk.pop();
	stk.pop();
	stk.pop();
	return 0;
}
