#CMakeLists for main application
include_directories("/usr/local/include")
link_directories("/usr/local/lib")

# Collect sources into the variable SIMPLE_FUNCTION_SOURCES
file (GLOB_RECURSE CDTI_TEST_SOURCES
      "cdti/*.cpp")
file (GLOB_RECURSE COMMON_TEST_SOURCES
      "common/*.cpp")
file (GLOB_RECURSE SAA_APPLICATION_TEST_SOURCES
      "saa-application/*.cpp")
file (GLOB_RECURSE TEST_SERVER_TEST_SOURCES
      "test-server/*.cpp")

file (GLOB_RECURSE MOCKS_SOURCES
		"mocks/*.cpp")

if( NOT DEFINED protobuf_BINARY_DIR )
	message( "Protobuf has not been built! Ensure that it exists in lib/google/protobuf")
endif()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

# Properties->C/C++->General->Additional Include Directories
include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/lib)
include_directories (${PROJECT_SOURCE_DIR}/test)



#Add all the tests
add_executable (test_all  ${MOCKS_SOURCES} ${CDTI_TEST_SOURCES} ${COMMON_TEST_SOURCES} ${SAA_APPLICATION_TEST_SOURCES} ${TEST_SERVER_TEST_SOURCES})
add_executable(test_testserver ${MOCKS_SOURCES} ${TEST_SERVER_TEST_SOURCES})
#Link all of the sources
target_link_libraries (test_all cdti-sources common-sources
                       saa-application-sources test-server-sources
                       protobuf mlpack armadillo gtest gmock gtest_main)
target_link_libraries(test_testserver common-sources test-server-sources gtest gmock gtest_main)

set_property(TARGET test_all PROPERTY FOLDER "executables")

# Adds logic to INSTALL.vcproj to copy saa_test.exe to destination directory
install (TARGETS test_all
		 RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
