#pragma once
#include <iostream>

class BasicProgram
{
	char* str;
	int iLength;
public:
  //Default Constructor
	BasicProgram() {
		iLength = 0;
		str = NULL;
	}

  //Parameterized Constructor
	BasicProgram(const char* pStr = NULL) {
		iLength = strlen(pStr);
		str = new char[iLength + 1];
		strcpy(str, pStr);
	}
  
  //Copy constructor
	BasicProgram(const BasicProgram& other) {
		iLength = other.iLength;
		str = new char[iLength + 1];
		strcpy(str, other.str);
	}
  
  //Destructor
	~BasicProgram() {
		if (!str)
			delete[] str;
	}
  
  //Assignment Operator overloading
	BasicProgram& operator=(const BasicProgram& other) {
		if (this != &other)
		{
			iLength = other.iLength;
			str = new char[iLength + 1];
			strcpy(str, other.str);
		}

		return *this;
	}
	
	void displayStr() {
		std::cout << "String is " << str << std::endl;
	}
  
	void change(const char* pStr) {
		delete[] str;
		iLength = strlen(pStr);
		str = new char[iLength + 1];
		strcpy(str, pStr);
	}
};

//Driver function
int main()
{
	//To check BasicProgram
	BasicProgram bp("GitHub");
	bp.displayStr();
  BasicProgram bp1(bp);
  bp1.displayStr();
  BasicProgram bp2;
  bp2 = bp;
  bp2.displayStr();
  bp.change("Programming");
  bp.displayStr();
  	
	cin.get();
	return 0;
}
