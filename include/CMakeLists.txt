file (GLOB TOP_FUNCTION_HEADERS
      "*.h")
source_group("" FILES ${TOP_FUNCTION_HEADERS})

file (GLOB ADDER_FUNCTION_HEADERS
      "adders/*.h")
source_group("adders" FILES ${ADDER_FUNCTION_HEADERS})




add_custom_target(include SOURCES ${ADDER_FUNCTION_HEADERS} ${TOP_FUNCTION_HEADERS})

# Creates a folder "include" and adds target 
# project (iinclude.vcproj) under it
set_property(TARGET include PROPERTY FOLDER "include")
