// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "Vector.h"

using namespace std;

/*
	By: Mike Glidden
	Description:
	This program demonstrates some of the potential uses for my Custom Vector Class header file.
	It goes over using initialization lists, how to use some functions, iterators, incrementing the vector,
	and a few other things.

*/

// Test class to demonstrate using Vector with Custom Types
class TestClass
{
public:
	TestClass();
	TestClass(int, string, double[2]);

	int val1;
	string val2;
	double val3[2];
	

private:

};

TestClass::TestClass()
{
	val1 = 1;
	val2 = "Random String";
	val3[0] = 521.231;
	val3[1] = 2.12;
	
}

TestClass::TestClass(int v1, string v2, double v3[2])
{
	val1 = v1;
	val2 = v2;
	for (int i = 0; i < 2; ++i)
		val3[i] = v3[i];
}

int main()
{
	// Initialize the Vector "vec" as a string collection with 4 elements 
	Vector<string> vec{ "one", "two", "Three", "Four" };

	// You can also initialize the vector with any other type (Including custom types)
	// and do not need to specify an initialization list
	Vector<int> vecInt = Vector<int>();

	// Adding integers to the vecInt vector
	vecInt.Push_Back(5);
	vecInt.Push_Back(23);
	vecInt.Push_Back(1);
	vecInt.Insert(2, 0);

	// Demonstrating using Custom Types with Vector Class
	double dArr[2]{12.32, 34.23};
	TestClass t1 = TestClass();
	TestClass t2 = TestClass(500, "Second Object", dArr);

	// Creating a Vector using Custom Types with my Custom Vector header file
	Vector<TestClass> custTypeCol{ t1, t2 };

	// Outputting the values stored in the Generic Collection
	cout << "Custom Type Vector Output =========================================" << endl;
	for (int i = 0; i < custTypeCol.Size(); ++i)
	{
		cout << "Integer Value: " << custTypeCol[i].val1 << ", String Value: " << custTypeCol[i].val2 << ", Double Array:";
		for (int j = 0; j < 2; ++j)
			cout << " At " << j << ": " << custTypeCol[i].val3[j];

		cout << endl;
	}

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

