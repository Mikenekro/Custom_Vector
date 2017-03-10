#pragma once
#include <iostream>
#include <initializer_list>

namespace std
{
	/*
	Custom Generic Vector Class to hold Elements of Type "T"
	Slowly adding more functionality to this class to behave more like the generic vector class
	*/
	template<class T>
	class Vector
	{
	public:
		typedef typename std::size_t uint;

	private:
		uint size;
		uint capacity;
		T *element;

		// Increases the capacity of the underlying array to be sz
		// If sz is smaller than the current capacity then nothing is done
		void allocate(uint sz)
		{
			try
			{
				if (sz <= capacity)
					return;
				if (sz > std::numeric_limits<uint>::max())
					throw std::out_of_range("Vector Capacity limit has been reached.\nMax Capacity is: MAXSIZE_T");

				// allocate a new array on the free store
				T *new_element = new T[sz];

				// copy old vector into new one
				for (int i = 0; (uint)i < size; ++i)
				{
					new_element[i] = element[i];
				}
				// set the new capacity
				capacity = sz;

				// delete the old vector
				delete[] element;
				// Assign element to the new element
				element = new_element;
			}
			catch (const std::out_of_range& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// Decreases the capacity of the array to be sz
		// If sz is larger than the current capacity, nothing is done
		void deallocate(uint sz)
		{
			try
			{
				if (sz >= capacity)
					return;

				T *new_element = new T[sz];

				for (int i = 0; (uint)i < size; ++i)
				{
					new_element[i] = element[i];
				}

				capacity = sz;
				delete[] element;
				element = new_element;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// =========================================================================================
		// Iterator for VectorCustom
		class Iterator
		{
		public:
			typedef std::size_t uint;
			typedef Iterator self;
			typedef T type;
			typedef T& reference;
			typedef T* pointer;

			// Constructors
			Iterator() {}
			Iterator(T* _ptr) : ptr(_ptr) { }

			self operator++() { ++ptr; return *this; } // PREFIX
			self operator++(int junk) { self i = *this; ptr++; return i; } // POSTFIX
			reference operator*() { return *ptr; }
			type* operator->() { return ptr; }
			type& operator=(const type& s) { ptr = s.ptr; return *this; }
			bool operator==(const self& s) { return ptr == s.ptr; } const
			bool operator!=(const self& s) { return ptr != s.ptr; } const
			bool operator<(const self& s) { return ptr < s.ptr; } const
			bool operator>(const self& s) { return ptr > s.ptr; } const

			type operator-(const self& s) const { return this->ptr - s.ptr; }

		private:
			pointer ptr;

		};
		// Constant Iterator for VectorCustom
		const class ConstIterator
		{
		public:
			typedef std::size_t uint;
			typedef ConstIterator self;
			typedef T type;
			typedef T& reference;
			typedef T* pointer;

			// Constructors
			ConstIterator() {}
			ConstIterator(T* _ptr) : ptr(_ptr) { }

			self operator++() { ++ptr; return *this; } // PREFIX
			self operator++(int junk) { self i = *this; ptr++; return i; } // POSTFIX
			reference operator*() { return *ptr; }
			const type* operator->() { return ptr; }
			const type& operator=(const type& s) { ptr = s.ptr; return *this; }
			bool operator==(const self& s) { return ptr == s.ptr; } const
			bool operator!=(const self& s) { return ptr != s.ptr; } const
			bool operator<(const self& s) { return ptr < s.ptr; } const
			bool operator>(const self& s) { return ptr > s.ptr; } const

			type operator-(const self& s) const { return this->ptr - s.ptr; }

		private:
			pointer ptr;
		};
		// ===============================================================================
	


		// private reset constructors
		void Reset(std::initializer_list<T> const &s)
		{
			size = s.size();
			capacity = 10;
			int i = 0;

			while (capacity < size)
				capacity *= 2;

			element = new T[capacity];

			for (auto it = s.begin(); it < s.end(); ++it)
			{
				element[i] = *it;
				++i;
			}
		}
		// Private reset constructor for Vectors
		void Reset(const Vector<T> &s)
		{
			size = s.Size();
			capacity = 10;
			int i = 0;

			while (capacity < size)
				capacity *= 2;

			element = new T[capacity];

			for (i = 0; i < s.size; ++i)
				element[i] = s[i];
		}

	public:

		// ===============================================================================
		// Iterator Typedef
		typedef Iterator iterator;
		// Constant Iterator Typedef
		typedef ConstIterator constIterator;
		// ===============================================================================

		// Default constructor with no initialization
		Vector() : capacity(10), size(0)
		{
			element = new T[capacity];
		}
		// Overloaded constructor for use with an initialization list
		// IE: Vector<int> d = {10, 5, 10}; or
		// Vector<int> d{10, 5, 10};
		Vector(std::initializer_list<T> const &s)
		{
			// Just call the Reset Function to create the Vector from the Initialization List
			Reset(s);
		}
		// Copy Constructor
		Vector(const Vector<T> &obj)
		{
			element = new T[obj.size];
			size = obj.size;
			capacity = obj.capacity;
			
			for (uint i = 0; i < obj.size; ++i)
				element[i] = obj[i];
		}
		// Free up resources when Vector is lost
		~Vector()
		{
			delete[] element;
		}

		// Overload the assignment operator to Re-Assign the Vector to a new initialization list
		Vector<T>& operator=(const std::initializer_list<T> &s)
		{
			Reset(s);
			return *this;
		}

		// Overloads the Brackets to Get/Set an element at position i
		T& operator[](uint i)
		{
			try
			{
				if (i >= 0 && i < size)
					return element[i];
				else 
					throw std::out_of_range("Out Of Range Exception: Defined Vector Position does not fall within the Vector Elements Range.");
					
			}
			catch (const std::out_of_range& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			return element[0];
		}
		// Overloads the Brackets to Get/Set an element at position i
		const T& operator[](uint i) const
		{
			try
			{
				if (i >= 0 && i < size)
					return element[i];
				else
					throw std::out_of_range("Out Of Range Exception: Defined Vector Position does not fall within the Vector Elements Range.");
			}
			catch (const std::out_of_range& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// Equality Operator
		const bool operator==(Vector<T>& right) const 
		{ 
			if (size != right.size)
				return false;
			else 
			{
				for (uint i = 0; i < Size(); i++) 
				{ 
					if (element[i] != right[i])
						return false;
				}
			}

			return true;
		} 

		// Plus Equals Operator
		// Adds each element from the "a" vector to the current vector
		Vector<T>& operator+=(const Vector<T>& a) 
		{
			T* p = new T[size + a.Size()];

			for (int i = 0; i < size; i++)
				p[i] = element[i];

			for (int i = size, ctr = 0; i < size + a.Size(); i++, ctr++)
				p[i] = a[ctr];

			delete[] element;
			element = p;
			size += a.Size();
			return *this;
		}

		// Plus Equals Operator
		// Adds an element of type T to the end of the Vector
		Vector<T>& operator+=(const T a)
		{
			if (size + 1 >= capacity)
				allocate(2 * capacity);

			element[size] = a;
			size++;

			return *this;
		}

		// (PREFIX) Add One to the current Vector Size
		const Vector<T>& operator++() 
		{
			T item;
			Push_Back(item);
			return *this;
		}
		// (POSTFIX) Add One to the current Vector Size
		const Vector<T>& operator++(int junk)
		{
			Vector<T> i = *this;
			T item;
			Push_Back(item);
			return i;
		}

		// (PREFIX) Minus One Element from the current Vector
		const Vector<T>& operator--() 
		{
			size -= 1;
			return *this;
		}
		// (POSTFIX) Minus One Element from the current Vector
		const Vector<T>& operator--(int junk)
		{
			Vector<T> i = *this;
			size -= 1;
			return i;
		}

		// Adds an element to the end of a Vector
		const Vector<T>& operator+(T& x) 
		{
			Push_Back(x);
			return *this;
		}

		// Returns the size of this vector (starting at 1)
		const uint Size() const
		{
			try
			{
				return size;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		// The capacity of the current Generic Vector list
		const uint Capacity() const
		{
			try
			{
				return capacity;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// Sets the position "pos" to the value of "item"
		void Set(uint pos, T &item)
		{
			try
			{
				if (pos >= 0 && pos < size)
					element[pos] = item;
				else
					throw std::out_of_range("Out Of Range Exception: Defined Vector Position does not fall within the Vector Elements Range.");
			}
			catch (const std::out_of_range& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// Gets an element from position "pos"
		T At(int pos)
		{
			try
			{
				if (pos >= 0 && (uint)pos < size)
					return element[pos];
				else
					throw std::out_of_range("Out Of Range Exception: Defined Vector Position does not fall within the Vector Elements Range.");
			}
			catch (const std::out_of_range& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}

			return element[0];
		}

		// Returns the position in the Vector of first found value of item
		// NOTE: Returns -1 if the element was not found
		int Get(T &item)
		{
			int pos = -1;

			try
			{
				for (uint i = 0; i < size; ++i)
				{
					if (element[i] == item)
					{
						pos = i;
						break;
					}
				}

				return pos;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// Gets will return a pointer containing the length of the array in the first position and each position in the current vector where this item is found
		// Ex: if item = 5 and the current Vector = {1, 3, 5, 3, 4, 5, 5, 5},
		// This function will return {4, 2, 5, 6, 7}
		int* Gets(T &item)
		{
			int *arr = new int[1];
			bool firstRun = true;
			int num = 0;

			try
			{
				for (uint i = 0; i < size; ++i)
				{
					if (At(i) == item && firstRun)
					{
						num++;
					}
					else if (At(i) == item && !firstRun)
					{
						arr[num] = i;
						num++;
					}

					if (i == size-1 && firstRun)
					{
						arr = new int[num];
						arr[0] = num;
						i = 0;
						num = 1;
						firstRun = !firstRun;
					}
				}

				// Return a pointer to this array
				return arr;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}

			return new int[0];
		}

		// Adds an element of Type "item" to the end of the vector
		void Push_Back(T &&item)
		{
			try
			{
				// Increase the capacity of the Vector if the 
				// size is at least the same size as capacity
				if (size >= capacity)
					allocate(2 * capacity);

				// Set the element at position "size" 
				// to the item passed in the variable
				element[size] = item;
				++size;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		// Adds an element of Type "item" to the end of the vector
		void Push_Back(T &item)
		{
			try
			{
				// Increase the capacity of the Vector if the 
				// size is at least the same size as capacity
				if (size >= capacity)
					allocate(2 * capacity);

				// Set the element at position "size" 
				// to the item passed in the variable
				element[size] = item;
				++size;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// Adds an element of Type "item" to the position "pos"
		void Insert(T &item, uint pos)
		{
			try
			{
				// Increase the capacity if we need to
				if (size >= capacity)
					allocate(2 * capacity);

				// Loop from 1 past the end of the Vector elements 
				// to the position we are adding an element to
				for (uint i = size; i > pos; i--)
				{
					// Move the item up 1 position (Starting from the top of the Vector)
					element[i] = element[i - 1];
				}
				// Add 1 to the size of the Vector
				++size;

				// Finally, Add the item to the specified position
				element[pos] = item;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// Removes the element from the end of the Vector
		void Pop_Back()
		{
			try
			{
				// Decrease the size if it is greater than or equal to zero
				if (size >= 0)
					size--;
					

				// Decrease the capacity if the size is less than x% the capacity
				if (size < capacity / 10 && capacity > 10)
					deallocate(capacity / 10);
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// Removes the first Value found of the item from the Vector
		void Pop(T &item)
		{
			try
			{
				// Gets the position of the first element "item"
				int pos = Get(item);

				// Call the function to remove an item from position "pos"
				Pop_At(pos);
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// Removes every occurence of the Value "item" found in the current Vector
		void Pops(T &item)
		{
			int removed = 0;

			try
			{
				// Get each position that we are removing from this vector
				int *pos = Gets(item);

				// Remove each position from the array
				for (int i = 1; i <= pos[0]; ++i)
				{
					Pop_At(pos[i]);
					removed++;
					if (i < pos[0])
						pos[i + 1] -= removed;
				}

			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// Removes an element from the position "pos" from the Vector
		void Pop_At(int pos)
		{
			try
			{
				if (pos > -1 && (uint)pos < size)
				{
					// Loop from the position after this element,
					// to the last element in the Vector
					for (int i = pos; (uint)i < size-1; ++i)
					{
						// Switch the elements
						T temp = element[i];
						element[i] = element[i+1];
						element[i + 1] = temp;
					}
					// Call the Pop function to remove the last element in the Vector
					Pop_Back();
				}
				else
					throw std::out_of_range("Out Of Range Exception: Defined Vector Position does not fall within the Vector Elements Range.");
			}
			catch (const std::out_of_range& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// Returns the first element in the Vector
		T& Front()
		{
			try
			{
				if (size > 0)
					return element[0];
				else
					throw exception();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		// Returns the last element in the Vector
		T& Back()
		{
			try
			{
				if (size > 0)
					return element[size - 1];
				else
					throw exception();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		// Returns the first position in the Vector
		uint First()
		{
			try
			{
				if (size > 0)
					return 0;
				else
					throw exception();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		// Returns the last position in the Vector
		uint Last()
		{
			try
			{
				if (size > 0)
					return size - 1;
				else
					throw exception();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		// Returns the Iterator for the Beginning of the Vector object
		Iterator Begin()
		{
			return Iterator(element);
		}
		// Returns the Iterator for the End of the Vector Object
		Iterator End()
		{
			return Iterator(element + size);
		}

		

	}; // End Vector Class

	
} // End Namespace

