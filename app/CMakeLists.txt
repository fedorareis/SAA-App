#CMakeLists for main application

include_directories ("${PROJECT_SOURCE_DIR}/src")

#Script for building the CDTI sources
file (GLOB_RECURSE CDTI_APP_SOURCES
      "cdti/*.cpp")


add_executable (cdti ${CDTI_APP_SOURCES})
target_link_libraries (cdti common-sources cdti-sources)

file (GLOB_RECURSE SAA_APPLICATION_APP_SOURCES
      "saa-application/*.cpp")

add_executable (saa-application ${SAA_APPLICATION_APP_SOURCES})
target_link_libraries (saa-application  common-sources saa-application-sources)

file (GLOB_RECURSE TEST_SERVER_APP_SOURCES
      "test-server/*.cpp")

add_executable (test-server ${TEST_SERVER_APP_SOURCES})
target_link_libraries (test-server  common-sources test-server-sources)



# Adds logic to INSTALL.vcproj to copy cdti.exe to destination directory
install (TARGETS cdti
		 RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
# Adds logic to INSTALL.vcproj to copy saa-application.exe to destination directory
install (TARGETS saa-application
       RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
       # Adds logic to INSTALL.vcproj to copy test-server.exe to destination directory
install (TARGETS test-server
       RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)