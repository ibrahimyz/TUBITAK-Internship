#ifndef INCLUDE_UTIL_ERRORCODE_H_
#define INCLUDE_UTIL_ERRORCODE_H_


namespace util {

	enum ErrorCode {
		NO_ERROR = 0,
		NO_AVAILABLE_OBJECT = -1,
		OBJECT_NOT_ALLOCATED = -2,
		OBJECT_NOT_FOUND = -3
	};


}

#endif // !INCLUDE_UTIL_ERRORCODE_H_
