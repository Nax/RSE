find_package(OpenAL REQUIRED)

file(GLOB_RECURSE SOURCES "*.c" "*.h")
add_library(rse SHARED ${SOURCES})
target_include_directories(rse PRIVATE "${CMAKE_SOURCE_DIR}/src" "${OPENAL_INCLUDE_DIR}" PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(rse "${OPENAL_LIBRARY}")
target_compile_definitions(rse PRIVATE RSE_DLL=1)
set_target_properties(rse PROPERTIES OUTPUT_NAME "RSE")
install(TARGETS rse)
