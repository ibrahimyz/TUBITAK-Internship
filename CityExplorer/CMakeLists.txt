# CMakeList.txt : CMake project for CityExplorer, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CityExplorer "src/CityExplorer.cpp" "include/algorithm/CityExplorer.h" "include/headers/ObjectPool.h" "include/headers/Vector.h" "include/headers/Iterator.h" "include/headers/ErrorCode.h" "include/algorithm/Algorithms.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CityExplorer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
