cmake_minimum_required(VERSION 3.10)
project(cpp-sdl)
set(CMAKE_CXX_STANDARD 11)

# Set SDL2 variables
set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SDL2/x86_64-w64-mingw32/include)
set(SDL2_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/SDL2/x86_64-w64-mingw32/lib)
set(SDL2_SOURCE_DIR ${CMAKE_SOURCE_DIR}/SDL2/x86_64-w64-mingw32/bin)

# Set source files
set(SOURCES main.cpp)

# Include SDL2
include_directories(${SDL2_INCLUDE_DIR})

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link against SDL2
target_link_libraries(${PROJECT_NAME} 
    -lmingw32 ${SDL2_LIBRARY_DIR}/libSDL2main.a 
    ${SDL2_LIBRARY_DIR}/libSDL2.dll.a -mwindows)

# Copy SDL2.dll to output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${SDL2_SOURCE_DIR}/SDL2.dll
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)