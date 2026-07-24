cmake_minimum_required(VERSION 3.15)

project(sample_clib LANGUAGES C VERSION 1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/sample_clib.c)

# Shared library
add_library(sample_clib_shared SHARED ${SOURCES})
target_include_directories(sample_clib_shared PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(sample_clib_shared PRIVATE LIBTYPE=2)
set_target_properties(sample_clib_shared PROPERTIES OUTPUT_NAME sample_clib)
install(TARGETS sample_clib_shared
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

# Static library
add_library(sample_clib_static STATIC ${SOURCES})
target_include_directories(sample_clib_static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(sample_clib_static PRIVATE LIBTYPE=1)
set_target_properties(sample_clib_static PROPERTIES OUTPUT_NAME sample_clib)
install(TARGETS sample_clib_static
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

# Install header
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/sample_clib.h
        DESTINATION include)
