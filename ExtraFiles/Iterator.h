#ifndef INCLUDE_UTIL_ITERATOR_H_
#define INCLUDE_UTIL_ITERATOR_H_

#include <cstddef>

namespace util {


// Iterator class for Static Vector

template <typename T, std::size_t Capacity>

class StaticVectorIterator {
private:
	T* ptr;			// Pointer to current element
	std::size_t index;	// Index of current element

public:
	// Constructor
	StaticVectorIterator(T* ptr, std::size_t index): ptr(ptr), index(index) {}

	// Dereference operator: return reference to element
	T& operator*() const {
		return *ptr;
	}

	// Member access operator: return pointer to element
	T* operator->() const {
		return ptr;
	}

	// Pre-increment operator
	StaticVectorIterator& operator++() {
		++ptr;
		++index;
		return *this;
	}

	// Post-increment operator: 
	StaticVectorIterator operator++(int) {
		StaticVectorIterator temp = *this; // a copy of the current iterator
		++(*this); // pre-increment operator to move to the next element
		return temp; // return the copy
	}

	// Equality operator for iterators
	bool operator==(const StaticVectorIterator& other) const {
		return ptr == other.ptr; // ptr == other.ptr
	}

	// Inequality operator for iterators
	bool operator!=(const StaticVectorIterator& other) const {
		return !(*this == other);
	}
};

} // namespace util

#endif // !INCLUDE_UTIL_ITERATOR_H_
