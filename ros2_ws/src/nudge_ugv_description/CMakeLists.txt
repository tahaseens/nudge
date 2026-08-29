cmake_minimum_required(VERSION 3.16)
project(nudge_ugv_description VERSION 0.1.0)

find_package(ament_cmake REQUIRED)
install(DIRECTORY urdf launch DESTINATION share/${PROJECT_NAME})
ament_package()
