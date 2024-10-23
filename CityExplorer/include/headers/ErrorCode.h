#ifndef INCLUDE_HEADERS_ERRORCODE_H_
#define INCLUDE_HEADERS_ERRORCODE_H_

namespace util {

	// Enum class for error codes used in the application

	enum ErrorCode {
		NO_ERROR = 0,
		NO_AVAILABLE_OBJECT = -1,
		OBJECT_NOT_ALLOCATED = -2,
		OBJECT_NOT_FOUND = -3
	};
}

#endif // !INCLUDE_HEADERS_ERRORCODE_H_