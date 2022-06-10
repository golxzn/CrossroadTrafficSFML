cmake_minimum_required(VERSION 3.15)

project(CrossroadTraffic LANGUAGES CXX VERSION 0.1.0)

set(target ${CMAKE_PROJECT_NAME})
set(root ${CMAKE_SOURCE_DIR})

set(install_dir ${root}/bin)
set(CMAKE_INSTALL_PREFIX ${install_dir})

#============================== Sources ==============================#

file(GLOB_RECURSE sources ${root}/source/*.cpp)
file(GLOB_RECURSE headers ${root}/source/*.h)

list(REMOVE_DUPLICATES sources)
list(REMOVE_DUPLICATES headers)

set(directories)
foreach(header ${headers})
	get_filename_component(directory ${header} PATH)
	list(APPEND directories ${directory})
endforeach()

list(REMOVE_DUPLICATES directories)

#============================ Dependencies ===========================#

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND CMAKE_MODULE_PATH ${root}/cmake/FindScripts)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(${root}/libs)

#============================= Executable ============================#
add_executable(${target} ${sources} ${headers})
target_include_directories(${target}
	PUBLIC
		${directories}
)
target_link_libraries(${target}
	PUBLIC
		sfml-system
		sfml-graphics
		sfml-window
		sfml-audio
)
set_target_properties(${target}
	PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
		RUNTIME_OUTPUT_DIRECTORY ${root}/assets
)
