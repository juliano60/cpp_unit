cmake_minimum_required( VERSION 3.5 FATAL_ERROR )
project( hello-world LANGUAGES CXX)

## set compiler standard
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

## add google mock/test dependencies
find_package( GMock REQUIRED )

## add boost dependency
find_package( Boost REQUIRED )

## add executable
add_executable( exo1 main.cpp SoundexTest.cpp )

target_link_libraries( exo1 
            ${GMOCK_LIBRARIES}
 )
