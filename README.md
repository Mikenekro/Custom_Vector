# Projects
Mikenekro (2017)
C++

Vector.h Readme

// About ============================================================================================
Vector.h is intended to be an alternative to the default vector class that C++ offers us in the standard library. 
It is not meant to be a replacement or perform better by any means but more as a learning tool to practice some techniques 
such as generics or operator overloading. During a few testing scenarios in the release build my Vector has performed
either as good as the default vector or takes a bit more time depending on what the CPU god decides.

// Usage ============================================================================================
Currently you can use Vector.h much in the same basic ways you can use the normal vector class in C++. It supports Initialization lists,
has a built in iterator class, can use brackets to access an item in the Vector, etc. and also has some other functionality that the
normal vector class does not have. This extra functionality may require some extra work on the programmers end but nothing that
is complicated (See Requirements for details).

Here are some included uses for the Vector class:

"Initialization":   Vector< int > vec1 { 35, 12, 12, 23, 54, 23 }; // Initializes Vector of ints

"Iteration":        for (Vector< int >::iterator it = vec1.Begin(); it < vec1.End(); ++it) 
                    { cout << *it << " "; } // displays each int in Vector

"Gets":         int *pos = vec1.Gets(12); // Returns a pointer array of each position in vec1 containing "12" (NOTE: The first value in pos is the number of items in the array)

"Pops":         vec1.Pops(12); // Removes every occurence of "12" from the Vector

"Pop_Back":     vec1.Pop_Back(); // Removes the element from the end of the Cector (23 in this case)

"Pop":          vec1.Pop(23); // Removes the first occurence of the value found in the Vector

"Pop_At":       vec1.Pop_At(1); // Removes the element at the indicates position in the Vector

"Insert":       vec1.Insert(25, 2); // Inserts an element (25) in the indicated position (2)

"Push_Back":    vec1.Push_Back(25); // Inserts an element (25) to the back of the Vector

"Get":          vec1.Get(35); // Gets the position of the first occurence of the indicated element (35, Would return 0 in the Initialization Vector above)

"At":           vec1.At(3); OR vec1[3]; // Returns the value at the insicated position (3)

"Size":         vec1.Size(); // Returns the current number of elements in the Vector

"Capacity":     vec1.Capacity(); // Returns the current max number of free store space the Vector is using

"Set":          vec1.Set(3, 55); // Sets the Value at position 3 to 55 because... why not

"Front & Back": vec1.Front(); AND vec1.Back(); // Returns the Front and Back element in the Vector respectively

"First & Last": vec1.First(); AND vec1.Last(); // Returns the First and Last position in the Vector respectively

"Begin & End":  vec1.Begin(); AND vec1.End(); // Returns the Beginning and Ending Iterators for Iteration (See Iteration Above)



// Requirements ============================================================================================
I put Vector.h in the "std"andard namespace to easily remember. 
The only requirements to use Vector.h are:
1. The obvious include statements

2.(Conditional) If you are using Vector.h to store class objects, you must overload the equality operator "==" to test against a value
of your choice from your class. This is ONLY needed if you wish to use the "Pops" and "Gets" functions.

NOTE: This is NOT needed for basic data types such as string, int, double, etc. You ONLY need to add equality operator overloading
for custom classes you want to access "Pops" and "Gets"

// Using Custom Classes ============================================================================================
Using custom classes with Vector.h is as easy as using the default vector class. The only difference is with the "Gets" and "Pops" functions.

Here are is some basic code for using Vector.h with a custom class:

'''cpp
class Person
{
	std::string name;
public:
	Person() { name = "Mike"; }
	Person(string n) { name = n; }
	
	std::string getName() { return name; }
	void setName(std::string n) { name = n; }
	
	// Equality Operator Overload (for "Gets" and "Pops")
	const bool operator==(Person& right) const
	{
		bool isEqual = false;
		
		if (name == right.getName())
			isEqual = true;
	
		return isEqual;
	}
};
'''

'''cpp
#include < iostream >
#include < string >
#include "Vector.h"

using namespace std;

void main()
{
	Vector<Person> people { Person(), Person2("Allen Pearson"), Person("Jim Buck"), Person("Saad Yousuf") };

	for (Vector<Person>::iterator it = people.Begin(); it < people.End(); ++it)
	{
		cout << it->getName() << ", ";
	}
	cout << endl;

	people.Push_Back(Person("Dave"));
	people.Insert(Person("Dave"), 5);
	
	cout << people.At(4).getName() << ", ";
	cout << people.At(5).getName() << endl;

	// Gets each position of the person in the Person Class (As per the Operator Overload in the Person Class)
	int *pos = people.Gets(people[4]);

	// NOTE: The following "cout" and "for" loop is the correct way to use the pointer returned by "Gets()"
	cout << "Number of " << people[5].getName() << "'s in the Vector: " << pos[0] << endl;
	for (int i = 1; i <= pos[0]; ++i)
	{
		cout << pos[i] << " in the Vector is " << people[pos[i]].getName() << endl; // Display each person at the position
	}

	// Removes each of the people with the same name (As per the Operator Overload in the Person Class)
	people.Pops(people.At(pos[1]));

	for (int i = 0; i < (int)people.Size(); ++i)
	{
		cout << people[i].getName() << endl;
	}

	system("pause");
    return 0;
}
'''




