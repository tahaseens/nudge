cmake_minimum_required(VERSION 3.16)
project(nudge_bringup VERSION 0.1.0)
find_package(ament_cmake REQUIRED)
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../config/"
  DESTINATION share/${PROJECT_NAME}/config)
ament_package()
