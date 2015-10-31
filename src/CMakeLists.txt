

# Collect sources into the variable SIMPLE_FUNCTION_SOURCES  
file (GLOB TOP_FUNCTION_SOURCES
      "*.cpp")

file (GLOB ADDER_FUNCTION_SOURCES
      "Adders/*.cpp")

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("" FILES ${TOP_FUNCTION_SOURCES})

source_group("adders" FILES ${ADDER_FUNCTION_SOURCES})

# Properties->C/C++->General->Additional Include Directories
include_directories (${PROJECT_SOURCE_DIR}/include)
include_directories (${PROJECT_SOURCE_DIR}/lib/catch)

# Set Properties->General->Configuration Type to Dynamic Library(.dll)
# Creates saa-application.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
add_library(saa-application ${TOP_FUNCTION_SOURCES} ${ADDER_FUNCTION_SOURCES})

# Creates a folder "libraries" and adds target project (saa-application.vcproj) under it
set_property(TARGET saa-application PROPERTY FOLDER "libraries")

# Adds logic to INSTALL.vcproj to copy sa--application.dll to the destination directory
install (TARGETS saa-application
		 RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin
		 LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/bin
		 ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/bin)