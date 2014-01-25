#include "stdafx.h"

struct Size5
{
	char a;
	int i;
};

Size5 global_size_5;

Size5 &CreateSize5InNotepad()
{
	static Size5 k;
	k.a = (char)0xFF;
	k.i = 0xFFFFFFFF;
	return k;
}