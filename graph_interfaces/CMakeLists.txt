cmake_minimum_required(VERSION 3.5)
project(graph_interfaces)


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/ServiceA.srv"
)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)



ament_package()
