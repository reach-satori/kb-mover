cmake_minimum_required(VERSION 2.8.3)
project(kb_mover)


find_package(catkin REQUIRED COMPONENTS keyboard_reader tf roscpp)

catkin_package(
    CATKIN_DEPENDS keyboard_reader roscpp tf
    )

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(kb_mover src/camera_mover.cpp)
target_link_libraries(kb_mover ${catkin_LIBRARIES})


