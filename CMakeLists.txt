cmake_minimum_required(VERSION 3.5.1)
project(cpp-shape-triangulator)
set(CMAKE_SUPPRESS_REGENERATION true)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "Source/*.h" "Source/*.cpp" "Source/*.hpp")


macro(GroupSources curdir)
    file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)
	message(STATUS In: ${PROJECT_SOURCE_DIR}/${curdir})
    message(STATUS Children: ${children}/*)
    foreach(child ${children})
			message(STATUS Child: ${child}/*)
			if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})

				GroupSources(${curdir}/${child})


			else()

				string(REPLACE "/" "\\" groupname ${curdir})


				string(REPLACE "Source" "Root" groupname ${groupname})

				source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})

			endif()

	endforeach()
endmacro()

GroupSources(Source)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

if(CMAKE_SIZEOF_VOID_P STREQUAL "4")
    set(arc_subdir "x86")
elseif(CMAKE_SIZEOF_VOID_P STREQUAL "8")
    set(arc_subdir "x64")
endif()

