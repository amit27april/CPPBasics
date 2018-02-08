#include <iostream>
#include "MyClass.h"

ExOp::ExOp() {
	i = 0;
	ptr = NULL;
}
ExOp::ExOp(const char* p=NULL) {
	i = strlen(p);
	ptr = new char[i+1];
	strcpy(ptr, p);
}

ExOp::~ExOp() {
	//std::cout << "Destructor called" << std::endl;
	delete[] ptr;
}
ExOp::ExOp(const ExOp& obj) {
	i = obj.i;
	ptr = new char[i + 1];
	strcpy(ptr, obj.ptr);
}

void ExOp::displayStr()
{
	std::cout << "String is " << ptr << " and length is " << i << std::endl;
}
ExOp& ExOp::operator=(const ExOp& obj) {
	if (this != &obj)
	{
		delete[] ptr;
		i = obj.i;
		ptr = new char[i + 1];
		strcpy(ptr, obj.ptr);
	}

	return *this;
}

ExOp ExOp::operator+(const ExOp& obj) {
	ExOp obj1("");
	obj1.i = i + obj.i;
	obj1.ptr = new char[obj1.i + 1];
	strcpy(obj1.ptr, ptr);
	strcpy(obj1.ptr + i, obj.ptr);

	return obj1;
}

bool ExOp::operator==(const ExOp& obj) {
	if (i == obj.i)
	{
		std::cout << "both object has same length string" << std::endl;
		return true;
	}
	return false;
}

void ExOp::change(const char* p = NULL) {
	delete[] ptr;
	i = strlen(p);
	ptr = new char[i + 1];
	strcpy(ptr, p);
}

ostream& operator<<(ostream& x, const ExOp& obj)
{
	x << "enjoy you have done it, object string " << obj.ptr <<endl;
	return x;
}

ExOp& ExOp::operator++()
{
	std::cout << "prefix overloading" << std::endl;
	return *this;
}

ExOp ExOp::operator++(int x)
{
	ExOp obj=*this;
	std::cout << "postfix overloading" << std::endl;
	return obj;
}

char& ExOp::operator[](int xx)
{
	std::cout << "subscript operator" << endl;
	if (xx > this->i)
	{
		std::cout << "Error out of bound" << endl;
	}
	return this->ptr[xx];
}

ExOp& ExOp::operator*() {
	cout << "Overloaded astric operator" << endl;
	return *this;
}

ExOp* ExOp::operator->(){
	std::cout << "overloaded arrow operator" << std::endl;
	return this;
}