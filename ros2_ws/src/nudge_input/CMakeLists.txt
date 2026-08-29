cmake_minimum_required(VERSION 3.16)
project(nudge_input VERSION 0.1.0 LANGUAGES CXX)

find_package(ament_cmake REQUIRED)
find_package(yaml_cpp_vendor REQUIRED)
find_package(yaml-cpp REQUIRED)

add_library(${PROJECT_NAME}
  src/controller_config.cpp
  src/deadzone_filter.cpp
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
if(TARGET yaml-cpp::yaml-cpp)
  target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp)
else()
  target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp)
endif()

install(TARGETS ${PROJECT_NAME} EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)
install(DIRECTORY include/ DESTINATION include)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_deadzone_filter test/test_deadzone_filter.cpp)
  if(TARGET test_deadzone_filter)
    target_link_libraries(test_deadzone_filter ${PROJECT_NAME})
  endif()
  ament_add_gtest(test_controller_config test/test_controller_config.cpp)
  if(TARGET test_controller_config)
    target_link_libraries(test_controller_config ${PROJECT_NAME})
    target_compile_definitions(test_controller_config PRIVATE
      NUDGE_CONTROLLER_CONFIG="${CMAKE_CURRENT_SOURCE_DIR}/../../../config/controller.yaml")
  endif()
endif()

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(yaml_cpp_vendor)
ament_package()
