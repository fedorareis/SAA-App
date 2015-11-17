#CMakeLists for main application

# Collect sources into the variable SIMPLE_FUNCTION_SOURCES
file (GLOB_RECURSE CDTI_TEST_SOURCES
      "cdti/*.cpp")
file (GLOB_RECURSE COMMON_TEST_SOURCES
      "common/*.cpp")
file (GLOB_RECURSE SAA_APPLICATION_TEST_SOURCES
      "saa-application/*.cpp")
file (GLOB_RECURSE TEST_SERVER_TEST_SOURCES
      "test-server/*.cpp")

find_library(LIB_PROTO protobuf)


# Properties->C/C++->General->Additional Include Directories
include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/lib)


#Add all the tests
add_executable (saa_test main.cpp ${CDTI_TEST_SOURCES} ${COMMON_TEST_SOURCES} ${SAA_APPLICATION_TEST_SOURCES} ${TEST_SERVER_TEST_SOURCES})
#Link all of the sources
target_link_libraries (saa_test cdti-sources common-sources saa-application-sources test-server-sources ${LIB_PROTO})

set_property(TARGET saa_test PROPERTY FOLDER "executables")

# Adds logic to INSTALL.vcproj to copy saa_test.exe to destination directory
install (TARGETS saa_test
		 RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
