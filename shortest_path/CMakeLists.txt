cmake_minimum_required(VERSION 3.5)
project(shortest_path)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(graph_interfaces REQUIRED)

add_executable(server src/serviceA_server.cpp)
ament_target_dependencies(server
  rclcpp graph_interfaces)

add_executable(client src/serviceA_client.cpp)
ament_target_dependencies(client
  rclcpp graph_interfaces)

install(TARGETS
  server
  client
  DESTINATION lib/${PROJECT_NAME})

ament_package()
