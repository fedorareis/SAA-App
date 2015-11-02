cmake_minimum_required (VERSION 2.8)

#Environment Setup,  add C++11, debugging symbols, all warnings
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall ")
option(test "Build all tests." ON) # Makes boolean 'test' available.


# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Command to output information to the console
# Useful for displaying errors, warnings, and debugging
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

project (SAA_Application)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)
add_subdirectory(include)
enable_testing()
add_test(SAA-Test ${PROJECT_BINARY_DIR}/bin/saa_test.exe)
