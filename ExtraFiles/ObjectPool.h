#ifndef INCLUDE_UTIL_OBJECTPOOL_H_
#define INCLUDE_UTIL_OBJECTPOOL_H_

#include <stdint.h>
#include "ErrorCode.h"

namespace util {

	template <typename T, size_t Size>
	class ObjectPool {
	public:
		ObjectPool() : lastAllocatedIndex{ static_cast<size_t>(-1)}, isAllocated{false} {

		}

		~ObjectPool() {}

		int Allocate(T*& pObj) {
			size_t currentIndex = (lastAllocatedIndex + 1) % Size;
			for (uint32_t i = 0; i < Size; ++i) {
				if (isAllocated[currentIndex]) {
					currentIndex = (currentIndex + 1) % Size;
					continue;
				}
				else {
					isAllocated[currentIndex] = true;
					pObj = &objects[currentIndex];
					lastAllocatedIndex = currentIndex;
					return ErrorCode::NO_ERROR; // No error
				}
			}
			return ErrorCode::NO_AVAILABLE_OBJECT; // No available object
		}

		int Deallocate(const T* pObj) {
			for (uint32_t i = 0; i < Size; ++i) {
				if (&objects[i] == pObj) {
					if (!isAllocated[i])
						return ErrorCode::OBJECT_NOT_ALLOCATED; // Object not allocated
				}
				else {
					isAllocated[i] = false;
					return ErrorCode::NO_ERROR; // No error
				}
			}
			return ErrorCode::OBJECT_NOT_FOUND; // Object not found
		}

	private:
		T objects[Size];
		bool isAllocated[Size];
		size_t lastAllocatedIndex;
};

} // namespace util

#endif // !INCLUDE_UTIL_OBJECTPOOL_H_

