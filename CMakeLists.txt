cmake_minimum_required(VERSION 3.12)
project(cpp-sdl)
set(CMAKE_CXX_STANDARD 20)


# Set source files
set(SOURCES main.cpp)

# Set platform-specific settings
if(WIN32)
	# Set SDL2 variables
	set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SDL2/x86_64-w64-mingw32/include)
	set(SDL2_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/SDL2/x86_64-w64-mingw32/lib)
	set(SDL2_SOURCE_DIR ${CMAKE_SOURCE_DIR}/SDL2/x86_64-w64-mingw32/bin)

	# Add SDL2 include directory
	include_directories(${SDL2_INCLUDE_DIR})

	# Add source files
	add_executable(${PROJECT_NAME} ${SOURCES})

	# Link against SDL2
	target_link_libraries(${PROJECT_NAME}
		-lmingw32 ${SDL2_LIBRARY_DIR}/libSDL2main.a 
		${SDL2_LIBRARY_DIR}/libSDL2.dll.a -mwindows)

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${SDL2_SOURCE_DIR}/SDL2.dll
			$<TARGET_FILE_DIR:${PROJECT_NAME}>)
elseif(UNIX)
	# Find SDL2
	find_package(SDL2 REQUIRED)
	include_directories(${SDL2_INCLUDE_DIRS})

	# Add source files
	add_executable(${PROJECT_NAME} ${SOURCES})

	# Link against SDL2
	target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif()
