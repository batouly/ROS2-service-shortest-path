#include "rclcpp/rclcpp.hpp"
#include "graph_interfaces/srv/service_a.hpp"     
//#include "Algo.cpp"   // CHANGE
#include "graph.h"

#include <memory>

void test(const std::shared_ptr<graph_interfaces::srv::ServiceA::Request> request,     // CHANGE
                std::shared_ptr<graph_interfaces::srv::ServiceA::Response> response)  // CHANGE
{
  
  pair<string, int> a = request_paths(request->graph,request->p);
  response->answer = a.first;
  response->num1 = a.second;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\ngraph: %s", request->graph.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\nsrc to dest: %s", request->p.c_str());                                          // CHANGE
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back shortest paths: [%s]", response->answer.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back length of path: [%d]", response->num1);
  
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("service_a_server");  // CHANGE

  rclcpp::Service<graph_interfaces::srv::ServiceA>::SharedPtr service =                 // CHANGE
    node->create_service<graph_interfaces::srv::ServiceA>("ServiceA",  &test);     // CHANGE

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to run service shortest paths");      // CHANGE

  rclcpp::spin(node);
  rclcpp::shutdown();
}