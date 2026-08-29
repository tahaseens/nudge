cmake_minimum_required(VERSION 3.16)
project(nudge_interfaces VERSION 0.1.0)

find_package(ament_cmake REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)

set(msg_files
  "msg/AssistanceState.msg"
  "msg/ConfidenceState.msg"
  "msg/CorrectionEvent.msg"
  "msg/CorrectionInterpretation.msg"
  "msg/OperatorState.msg"
  "msg/RobotGoalState.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES builtin_interfaces geometry_msgs nav_msgs std_msgs
)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  find_package(rclcpp REQUIRED)
  ament_add_gtest(test_interface_serialization test/test_interface_serialization.cpp)
  if(TARGET test_interface_serialization)
    target_compile_features(test_interface_serialization PRIVATE cxx_std_17)
    ament_target_dependencies(test_interface_serialization rclcpp)
    rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
    target_link_libraries(test_interface_serialization "${cpp_typesupport_target}")
  endif()
endif()

ament_export_dependencies(rosidl_default_runtime)
ament_package()
