#ifndef INCLUDE_HEADERS_VECTOR_H_
#define INCLUDE_HEADERS_VECTOR_H_

#include <cstddef> 
#include "Iterator.h"

namespace util {


	// T: Type of elements stored in the vector
	// Capacity: Maximum number of elements the vector can hold
	template <typename T, std::size_t Capacity>
	class StaticVector {

	private:
		T data[Capacity]; // Fixed-size array for storing elements
		std::size_t size; // Number of elements currently stored

	public:
		// Iterator type alias for StaticVector
		using iterator = StaticVectorIterator<T, Capacity>;

		// Constructor (empty vector)
		StaticVector() : size(0), data{} {}

		//Appends an element to the end of the vector
		bool push_back(const T& value) {
			//Check if vector has reached its capacity
			if (size >= Capacity)
				return false;
			data[size++] = value; // Add element and increment size
			return true;
		}

		// Removes the last element from the vector
		bool pop_back() {
			//Check if vector is empty
			if (size == 0)
				return false;
			--size; // Decrease size to remove the last element
			return true;
		}

		// Operator to access elements by index
		T& operator[] (std::size_t index) {
			return data[index]; // return element at specified index
		}

		// Const version of operator (read-only)
		const T& operator[] (std::size_t index) const {
			return data[index];
		}

		// Returns the number of elements in the vector
		std::size_t getSize() const {
			return size;
		}

		// Returns the capacity of the vector
		std::size_t capacity() const {
			return Capacity;
		}

		// Returns true if the vector is empty
		bool empty() const {
			return size == 0;
		}
		// Clear the vector
		void clear() {
			size = 0;
		}

		// Begin iterator
		iterator begin() {
			return iterator(data, 0);
		}
		// End iterator
		iterator end() {
			return iterator(data + size, size);
		}
	};
} // end namespace util

#endif // !INCLUDE_HEADERS_VECTOR_H_
