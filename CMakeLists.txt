cmake_minimum_required(VERSION 3.8)
project(hue_server VERSION 1.0.0 
    DESCRIPTION "HUE lighting system controller"
    LANGUAGES CXX)
add_compile_options(-Wall -Wextra -W -Wshadow -Wformat -fexceptions)
# set(CMAKE_CXX_FLAGS "-Wall -Wextra -fpermissive -Wno-unused-variable -Wno-unused-parameter -Wno-uninitialized -Wno-comment")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
link_directories(/usr/local/lib)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS}) 

find_package(CURL)
include_directories(${CURL_INCLUDE_DIRS})

find_package(Notcurses REQUIRED)
include_directories(${Notcurses_INCLUDE_DIRS})
# find_package(Notcurses++ REQUIRED)
# set_package_properties(Notcurses PROPERTIES TYPE REQUIRED)
# include_directories(${Notcurses_LIBRARARY_DIRS})
# include_directories(${NotcursesCore_INCLUDE_DIRS})
# include_directories(${Notcurses++_INCLUDE_DIRS})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CURL_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${Notcurses_LIBRARIES})
# target_link_libraries(${CMAKE_PROJECT_NAME} ${Notcurses++_LIBRARIES})
# target_link_libraries(${CMAKE_PROJECT_NAME} ${NotcursesCore_LIBRARIES})

