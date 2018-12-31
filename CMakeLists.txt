cmake_minimum_required (VERSION 2.6)

project(MetaData)

find_package(Boost COMPONENTS system REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++17")

include_directories(

	${Boost_INCLUDE_DIRS}

)

add_executable(
    	MetaData 

    	Entry.cpp

    	FileInformationGeneral.cpp

    	FileSize.cpp
)

target_link_libraries(
	MetaData 
	
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
)

