// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "Vector.h"

using namespace std;

int main()
{
	Vector<string> vec{ "one", "two", "Three", "Four" };
	int i = 0;

	vec.Push_Back("Five");

	cout << "First Vector =====================================================" << endl;
	for (Vector<string>::iterator it = vec.Begin(); it < vec.End(); ++it)
	{
		cout << "Position " << i << ": " << *it << endl;

		++i;
	}

	// New initialization list. Any vector function names (such as pop at or pops) will use that
	// function to remove or edit that item in the list
	vec = {"New", "Vector", "Remove This", "Pops", "Stuff", "Pop At", "Pops", "Pops", "Pop Back"};

	i = 0;
	cout << "After First Changes ====================================================" << endl;
	for (Vector<string>::iterator it = vec.Begin(); it < vec.End(); ++it)
	{
		cout << "Position " << i << ": " << *it << endl;

		++i;
	}

	string pops = "Pops";

	cout << "Single Changes ===================================================" << endl;

	// The following shows the correct way to access different functions of the Vector Class

	// Some of the normal functions of the Vector Class
	cout << "vec[1] = " << vec[1] << endl;
	cout << "vec.At(2) = " << vec.At(2) << endl;
	cout << "vec.Front() = " << vec.Front() << endl;
	cout << "vec.Back() = " << vec.Back() << endl;
	cout << "vec.First() = " << vec.First() << endl;
	cout << "vec.Last() = " << vec.Last() << endl;
	cout << "vec.Size() = " << vec.Size() << endl;
	cout << "vec.Capacity() = " << vec.Capacity() << endl;
	cout << "vec.Get(""Pops"") = " << vec.Get(pops) << endl;
	
	// The following 6 lines of code shows you how to access different elements with 
	// the pointer returned from vec.Gets() function
	int *values = vec.Gets((string)"Pops");
	int len = values[0];
	cout << "vec.Gets(""Pops"") Pointer Location = " << values << endl;
	cout << "vec.Gets(""Pops"") Length = " << len << endl;
	for (int i = 1; i <= len; ++i)
		cout << "vec.Gets(""Pops"")[" << i << "] Value = " << values[i] << endl;
	
	// 
	vec.Insert((string)"Something", 3);
	vec.Pop((string)"Remove This");
	vec.Pops(pops);
	vec.Pop_At(4);
	vec.Pop_Back();
	vec.Push_Back("One of The Last Elements");
	vec.Set(1, (string)"Changed Vector");
	vec[0] = (string)"Changed " + (string)"New";
	
	vec = vec + (string)"Element Added to the end of Vector";
	vec += (string)"Plus Equals";
	++vec;
	vec++;
	vec--;

	Vector<string> vec2{"none", "other", "than", "this", "though", "all", "of", "them", "are", "here"};
	Vector<string> vec3 = vec;
	Vector<string> vec4 = { "1", "2", "3", "@" };

	if (vec == vec2)
		cout << "Vector 1 = Vector 2" << endl;
	else
		cout << "Vector 1 != Vector 2" << endl;

	if (vec == vec3)
		cout << "Vector 1 = Vector 3" << endl;
	else
		cout << "Vector 1 != Vector 3" << endl;

	vec = vec + vec4;

	i = 0;
	cout << "After Changes ====================================================" << endl;
	for (Vector<string>::iterator it = vec.Begin(); it < vec.End(); ++it)
	{
		cout << "Position " << i << ": " << *it << endl;

		++i;
	}

	system("pause");
    return 0;
}

