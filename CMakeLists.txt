cmake_minimum_required(VERSION 3.13)

if (POLICY CMP0068)
    cmake_policy(SET CMP0068 NEW)
endif ()
# Define file(GENERATE) behavior for relative paths.
if (POLICY CMP0070)
    cmake_policy(SET CMP0070 NEW)
endif ()
# target_sources: use absolute path for INTERFACE_SOURCES.
if (POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif ()
# projectname is the same as the main-executable
project(CPlusPlusProjectTemplate)

add_definitions('-g')
add_definitions('-Wall')
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif ()
message (STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
set(CPlusPlusProjectTemplate_VERSION_MAJOR 0)
set(CPlusPlusProjectTemplate_VERSION_MINOR 0)
set(CPlusPlusProjectTemplate_VERSION_BUG 0)
if (NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH /depends/thirdparty)
    LINK_DIRECTORIES(/depends/thirdparty/lib /depends/thirdparty/lib64)
endif()

include_directories(${CMAKE_PREFIX_PATH}/include)
function(get_commitid CODE_DIR COMMIT_ID)
    find_package(Git REQUIRED)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%h
        OUTPUT_VARIABLE COMMIT_ID_TMP
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        WORKING_DIRECTORY
        ${CODE_DIR}
    )
    set("${COMMIT_ID}" ${COMMIT_ID_TMP} PARENT_SCOPE)
endfunction()
get_commitid(${PROJECT_SOURCE_DIR} CPlusPlusProjectTemplate_COMMIT_ID)
configure_file (
  "${PROJECT_SOURCE_DIR}/src/version.h.in"
  "${PROJECT_SOURCE_DIR}/src/version.h"
)
add_subdirectory(src)
