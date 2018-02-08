/* Created this class to illustrate function pointer and static 
implementation */

#include <iostream>
using namespace std;

class MyClass
{
	static int i;
	int j;
public:
	MyClass() : j(1) {};
	~MyClass(){}
	void doJobA() { cout << "From A" << endl; }
	void doJobB() { cout << "From B" << endl; }
	static void show() { cout << "inside show" << i<< endl; }
};

int MyClass::i = 12;
typedef void (MyClass::*fnToPtr) (); //Decleartaion

int main()
{
  fnToPtr arFp[2] = { &MyClass::doJobA ,&MyClass::doJobB }; //Assignment
	MyClass obj;

	(obj.*arFp[1])(); //calling 

	obj.show();
	cin.get();
  return 0;
}
