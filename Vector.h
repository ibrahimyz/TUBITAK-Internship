#ifndef INCLUDE_UTIL_VECTOR_H_
#define INCLUDE_UTIL_VECTOR_H_

#include <cstddef> 
#include "Iterator.h"

namespace util {


	// T: type of elements stored in the vector
	// Capacity: max number of elements the vector can hold

	template <typename T, std::size_t Capacity>
	class StaticVector {
	private:
		T data[Capacity]; // Fixed-size array to store elements
		std::size_t size; // Current number of elements in the vector

	public:
		using iterator = StaticVectorIterator<T, Capacity>;

		// Constructor (empty vector)
		StaticVector() : size(0), data{} {}

		// Function to add ana element at the end of the vector
		bool push_back(const T& value) {
			//Check if vector has reached its capacity
			if (size >= Capacity)
				return false;
			data[size++] = value; // Add element and increment size
			return true;
		}

		// Function to remove the last element from the vector
		bool pop_back() {
			//Check if vector is empty
			if (size == 0)
				return false;
			--size; // Decrement size to remove the last element
			return true;
		}

		// operator to access elements by index
		T& operator[] (std::size_t index) {
			return data[index]; // return element at specified index
		}

		// const version of operator
		const T& operator[] (std::size_t index) const {
			return data[index];
		}

		// Function to return the current number of elements in the vector
		std::size_t getSize() const {
			return size;
		}

		// Function to return max capacity of the vector
		std::size_t capacity() const {
			return Capacity;
		}

		// Function to check if the vector is empty
		bool empty() const {
			return size == 0;
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

#endif // !INCLUDE_UTIL_VECTOR_H_