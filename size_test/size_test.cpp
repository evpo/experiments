// size_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
#include "windows.h"

struct Alignment4
{
	char a;
	char b; 
	//char[2]
	int i; // max alignment 4
	Alignment4():a(1),b(2),i(3){}
}; // size is 8

struct Alignment8
{
	int i; 
	//char[4]
	double d; // max alignment 8
	short s;
	//char[6]
	Alignment8():i(1), d(2), s(3){}
}; // size is 24

struct BetterAlignment8
{
	int i;
	short s;
	//char[2]
	double d; // max alignment 8
	BetterAlignment8():i(1), d(2), s(3){}
}; // size is 16

struct Size8
{
	char a;
	char b;
	double i;
	char c;
	Size8():a(1), b(2), c(3), i(0){}
};

#pragma pack(push, 1)
struct Size7
{
	char a;
	char b;
	double i;
	char c;
	Size7():a(1), b(2), c(3), i(0){}
};

struct Size5
{
	char a;
	int i;
};
#pragma pack(pop)

struct __declspec(align(8)) Size6
{
	char a;
	int i;
	Size6():a(1), i(2){}
};

using namespace std;

template<typename T>
void* TestType()
{
	T *p1 = new T[2];
	T *p2 = p1 + 1;
	
	ostringstream stm;
	stm << "alignment=" << alignment_of<T>::value << endl;
	stm << "sizeof=" << sizeof(T) << endl;

	OutputDebugStringA(stm.str().c_str());
	return p1;
}

extern Size5 global_size_5;

int _tmain(int argc, _TCHAR* argv[])
{
	OutputDebugStringA("6:\n");
	void* ms7 = TestType<Size6>();
	OutputDebugStringA("8:\n");
	void *ms8 = TestType<BetterAlignment8>();

	// conflict without warning
	Size5 &CreateSize5InNotepad();
	Size5 &k = CreateSize5InNotepad(); //k.i has garbage
	Size5 local_size5;
	local_size5.a = (char)0xFF;
	local_size5.i = 0xFFFFFFFF;
	
	// conflict with warning
	int i_from_global = global_size_5.i;
	
	return 0;
}

