cmake_minimum_required(VERSION 3.1)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(X16PPd)

find_package(LibXml2 REQUIRED)

file(GLOB X16PPd_SRC "*.cpp" ".h")


#if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
#	add_executable(tilemaped ${Tilemaped_SRC} "tilemaped.rc")
#else()
#if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	add_executable(x16ppd ${X16PPd_SRC})
#endif()

target_include_directories(x16ppd SYSTEM PUBLIC ${LIBXML2_INCLUDE_DIRS})

#if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
#	set(CMAKE_CXX_COMPILER "g++")
#	set(CMAKE_CXX_FLAGS "-std=c++17 -O2")
#	#-mwindows
#	target_link_directories(tilemaped PUBLIC C:/msys64/mingw64/lib)
#	add_definitions(-Dmain=SDL_main)
#endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(CMAKE_CXX_COMPILER "g++")
	set(CMAKE_CXX_FLAGS "-std=c++17 -ggdb -O2 -Wall -Wno-sign-compare -Wno-unused-variable")
	target_link_libraries(x16ppd ${LIBXML2_LIBRARIES})
endif()

#if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
#	#mingw32 SDL2main SDL2 SDL2_image SDL2_ttf
#	target_link_libraries(tilemaped mingw32 ${SDL2_LIBRARIES} SDL2_image SDL2_ttf ${LIBXML2_LIBRARIES})
#endif()
