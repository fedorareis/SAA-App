#CMakeLists for main application

include_directories ("${PROJECT_SOURCE_DIR}/include")

add_executable (app main.cpp)

target_link_libraries (app  saa-application)


# Creates a folder "executables" and adds target 
# project (app.vcproj) under it
set_property(TARGET app PROPERTY FOLDER "executables")

# Adds logic to INSTALL.vcproj to copy app.exe to destination directory
install (TARGETS app
		 RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
		 