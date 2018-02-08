#include <iostream>
using namespace std;

class Base {
	int i;
public:
	Base(int x) :i(x) {}
	virtual void show() {
		cout << "Base class, i = " << i << endl;
	}

};

class Derived : virtual public Base{
	int j;
public:
	Derived(int x) :Base(x),j(x) {}
	virtual void show1() {
		cout << "Derived class, j = " << j << endl;
	}
};

class Derived1 : virtual public Base {
	int j;
public:
	Derived1(int x) :Base(x), j(x) {}
	virtual void show2() {
		cout << "Derived1 class, j = " << j << endl;
	}
};

class Derived2 : public Derived,Derived1 {
	int j;
public:
	Derived2(int x) :Base(x),Derived(x),Derived1(x),j(x) {}
	void show3() {
		cout << "Derived2 class, j = " << j << endl;
	}
};

