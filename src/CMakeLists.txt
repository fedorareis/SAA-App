#Setup QT
find_package(Qt5Widgets)

# Collect sources into the variable SIMPLE_FUNCTION_SOURCES  
file (GLOB_RECURSE COMMON_FUNCTION_SOURCES
      "common/*.cpp" "common/*.cc")

file (GLOB_RECURSE CDTI_FUNCTION_SOURCES
      "cdti/*.cpp")

file (GLOB_RECURSE SAA_APPLICATION_FUNCTION_SOURCES
      "saa-application/*.cpp")

file (GLOB_RECURSE TEST_SERVER_FUNCTION_SOURCES
      "test-server/*.cpp")

# Properties->C/C++->General->Additional Include Directories
include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories("/usr/local/include")
link_directories("/usr/local/lib")
# Set Properties->General->Configuration Type to Dynamic Library(.dll)
# Creates saa-application.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer

add_library(common-sources ${COMMON_FUNCTION_SOURCES} common/FrameBody.cpp common/FrameBody.h)
target_link_libraries(common-sources mlpack armadillo protobuf)
add_library(cdti-sources ${CDTI_FUNCTION_SOURCES} cdti/Display.h)
target_link_libraries(cdti-sources Qt5::Widgets common-sources protobuf)
add_library(saa-application-sources ${SAA_APPLICATION_FUNCTION_SOURCES})
target_link_libraries(saa-application-sources common-sources)
add_library(test-server-sources ${TEST_SERVER_FUNCTION_SOURCES})
target_link_libraries(test-server-sources common-sources)


# Adds logic to INSTALL.vcproj to copy sa--application.dll to the destination directory
install (TARGETS common-sources
		 RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin
		 LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/bin
		 ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/bin)

install (TARGETS  cdti-sources
       RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin
       LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/bin
       ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/bin)

install (TARGETS saa-application-sources
       RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin
       LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/bin
       ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/bin)

install (TARGETS test-server-sources
       RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin
       LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/bin
       ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/bin)
