#CMakeLists for main application

# Collect sources into the variable SIMPLE_FUNCTION_SOURCES  
file (GLOB TOP_TEST_SOURCES
      "*.cpp")

file (GLOB ADDER_TEST_SOURCES
      "Adders/*.cpp")

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("" FILES ${TOP_TEST_SOURCES})
source_group("adders" FILES ${ADDER_TEST_SOURCES})

# Properties->C/C++->General->Additional Include Directories
include_directories (${PROJECT_SOURCE_DIR}/include)
include_directories (${PROJECT_SOURCE_DIR}/lib/catch)

include_directories (${PROJECT_SOURCE_DIR}/lib)
include_directories ("${PROJECT_SOURCE_DIR}/include")

add_executable (saa_test ${TOP_TEST_SOURCES} ${ADDER_TEST_SOURCES})

target_link_libraries (saa_test  saa-application)


# Creates a folder "executables" and adds target 
# project (saa_test.vcproj) under it
set_property(TARGET saa_test PROPERTY FOLDER "executables")

# Adds logic to INSTALL.vcproj to copy saa_test.exe to destination directory
install (TARGETS saa_test
		 RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
		 