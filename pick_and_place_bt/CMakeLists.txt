cmake_minimum_required(VERSION 3.5)

project(pick_and_place_bt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/usr/local/share/behaviortree_cpp/cmake")
find_package(behaviortree_cpp REQUIRED)
add_executable(${PROJECT_NAME} "pick_place.cpp")
target_link_libraries(${PROJECT_NAME} behaviortree_cpp_v3)
