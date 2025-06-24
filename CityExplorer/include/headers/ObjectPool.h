#ifndef INCLUDE_HEADERS_OBJECTPOOL_H_
#define INCLUDE_HEADERS_OBJECTPOOL_H_

#include <stdint.h>
#include "ErrorCode.h"

namespace util {

	// Class template for managing a pool of objects of type T
	template <typename T, size_t Size>
	class ObjectPool {
	public:

		// Constructor initializes the object pool
		ObjectPool() : lastAllocatedIndex{ static_cast<size_t>(-1) }, isAllocated{ false } {

		}

		~ObjectPool() {}

		// Allocate an object from the pool
		int Allocate(T*& pObj) {
			size_t currentIndex = (lastAllocatedIndex + 1) % Size;
			for (uint32_t i = 0; i < Size; ++i) {

				// Skip if the current index is already allocated (circularly)
				if (isAllocated[currentIndex]) {
					currentIndex = (currentIndex + 1) % Size;
					continue;
				}
				else {
					// Mark the object as allocated and return its address
					isAllocated[currentIndex] = true;
					pObj = &objects[currentIndex];
					lastAllocatedIndex = currentIndex; // Update the last allocated index
					return ErrorCode::NO_ERROR; // No error
				}
			}
			return ErrorCode::NO_AVAILABLE_OBJECT; // No available object in the pool
		}

		// Deallocate an object back to the pool
		int Deallocate(const T* pObj) {
			for (uint32_t i = 0; i < Size; ++i)

				// Verify that the object to be deallocated belongs to the pool
				if (&objects[i] == pObj) {
					if (!isAllocated[i])
						return ErrorCode::OBJECT_NOT_ALLOCATED; // Object not allocated
				}
				else {
					isAllocated[i] = false; // Mark object as deallocated
					return ErrorCode::NO_ERROR; // No error
				}
			
			return ErrorCode::OBJECT_NOT_FOUND; // Object not found
		}	

	private:
		T objects[Size]; // Fixed-size array for object pool
		bool isAllocated[Size]; // Allocation flags for objects in the pool
		size_t lastAllocatedIndex; // Index of the last allocated object
	};

} // namespace util

#endif // !INCLUDE_HEADERS_OBJECTPOOL_H_

