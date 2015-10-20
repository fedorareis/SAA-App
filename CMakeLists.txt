cmake_minimum_required (VERSION 3.0)

#Environment Setup,  add C++11, debugging symbols, all warnings
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall ")
option(test "Build all tests." ON) # Makes boolean 'test' available.


project (CatchTestDemo)
#Enable a testing library with CMAKE
enable_testing()
#Include any libraries
include_directories ("${PROJECT_SOURCE_DIR}/lib")

#Include any include files
include_directories ("${PROJECT_SOURCE_DIR}/include")

#Gather any source files
file(GLOB_RECURSE CatchTestDemo_SOURCES "src/*.cpp" "src/*.cc")


#Build the main project as a library, and only link main at the end
list(REMOVE_ITEM CatchTestDemo_SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)
add_library(CatchTestDemo_Lib ${CatchTestDemo_SOURCES})

#add main
add_executable(CatchTestDemo ${PROJECT_SOURCE_DIR}/src/main.cpp)

#and link the 'library'
target_link_libraries(CatchTestDemo CatchTestDemo_Lib)


#If tests are set to build (Run ccmake to configure!)
if (test)

  #add additional Cmake capabilities (Running specific tests from 'make test')
  enable_testing()

  ##############
  # Unit Tests
  ##############
  #Gather all unit tests.
  file(GLOB_RECURSE TEST_SRC_FILES "test/*.cpp")

  #Add tests to the executable
  add_executable(runUnitTests ${TEST_SRC_FILES})

  # Standard linking to gtest executables (If you want to use GoogleTests's prebuilt main file).
  
  # Extra linking for the project.
  target_link_libraries(runUnitTests CatchTestDemo_Lib)


endif()
