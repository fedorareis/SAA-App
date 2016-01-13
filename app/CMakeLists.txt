#CMakeLists for main application

include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories("/usr/local/include")
link_directories("/usr/local/lib")

if( NOT DEFINED protobuf_BINARY_DIR )
	message( FATAL_ERROR "Protobuf has not been built! Ensure that it exists in lib/google/protobuf")
endif()

#Script for building the CDTI sources
file (GLOB_RECURSE CDTI_APP_SOURCES
      "cdti/*.cpp")

add_executable (cdti-main WIN32 ${CDTI_APP_SOURCES})
target_link_libraries (cdti-main common-sources cdti-sources protobuf)

#SAA application

add_executable (cdti ${CDTI_APP_SOURCES})
target_link_libraries (cdti common-sources cdti-sources protobuf)

file (GLOB_RECURSE SAA_APPLICATION_APP_SOURCES
      "saa-application/*.cpp")

add_executable (saa-application ${SAA_APPLICATION_APP_SOURCES})
target_link_libraries (saa-application  common-sources saa-application-sources protobuf)

file (GLOB_RECURSE TEST_SERVER_APP_SOURCES
      "test-server/*.cpp")

add_executable (test-server ${TEST_SERVER_APP_SOURCES})
target_link_libraries (test-server  common-sources test-server-sources protobuf )



# Adds logic to INSTALL.vcproj to copy cdti.exe to destination directory
install (TARGETS cdti-main
		 RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
# Adds logic to INSTALL.vcproj to copy saa-application.exe to destination directory
install (TARGETS saa-application
       RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
       # Adds logic to INSTALL.vcproj to copy test-server.exe to destination directory
install (TARGETS test-server
       RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)