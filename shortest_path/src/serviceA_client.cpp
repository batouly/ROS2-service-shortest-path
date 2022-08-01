#include "rclcpp/rclcpp.hpp"

#include "graph_interfaces/srv/service_a.hpp"      // CHANGE

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 3) { // CHANGE
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add two sstrings");      // CHANGE
      return 1;
  }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("service_a_client"); // CHANGE
  rclcpp::Client<graph_interfaces::srv::ServiceA>::SharedPtr client = node->create_client<graph_interfaces::srv::ServiceA>("ServiceA");                  // CHANGE

  auto request = std::make_shared<graph_interfaces::srv::ServiceA::Request>();               // CHANGE
  //request->graph = atoll(argv[1]);
  //std::cout<<argv[1]<<"\n";
  request->graph = argv[1];
  request->p = argv[2];

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::executor::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "shortest paths: %s", result.get()->answer.c_str());
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "length of path: %d", result.get()->num1);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service ");    // CHANGE
  }

  rclcpp::shutdown();
  return 0;
}