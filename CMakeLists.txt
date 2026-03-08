cmake_minimum_required(VERSION 3.20.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(dlinked_list_serial C CXX)

set(SRC 
"src/main.cpp" 
"src/dlist.cpp" 
"src/dparser.cpp"  
)

add_executable(dlinked_list_serial ${SRC})