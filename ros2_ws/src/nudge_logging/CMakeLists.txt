cmake_minimum_required(VERSION 3.16)
project(nudge_logging VERSION 0.1.0 LANGUAGES CXX)

find_package(ament_cmake REQUIRED)

add_library(${PROJECT_NAME} src/run_directory.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS ${PROJECT_NAME} EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY schema/ DESTINATION share/${PROJECT_NAME}/schema)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_run_directory test/test_run_directory.cpp)
  if(TARGET test_run_directory)
    target_link_libraries(test_run_directory ${PROJECT_NAME})
  endif()
endif()

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_package()
