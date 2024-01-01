/* Phong - self learning data structure STACK
/  1. Implement stack by using vector
/  2. Implement stack by using link list
*/

#include <iostream>
#include <vector>


class Base
{
public:
	Base(){
		std::cout<<"Base constructor\n";
	}
	virtual ~Base(){
		std::cout<<"Base Destructor\n";
	}
};

class Derived : public Base
{
public:
	Derived(){
		std::cout<<"Derived constructor\n";
	}
	~Derived(){
		std::cout<<"Derived Destructor\n";
	}
	void foo(){
		std::cout<<"Derived foo\n";
	}
};
  
int main(int argc, char** argv) {
	std::cout<<" main()\n";
	Base*ptr = new Derived();
	ptr->foo();
	delete ptr;
	
	return 0;
}
