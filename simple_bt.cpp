#include <iostream>
#include <chrono>
#include "behaviortree_cpp_v3/action_node.h"
#include "behaviortree_cpp_v3/bt_factory.h"

using namespace std::chrono_literals;

//node class
//inherits from class in BehaviorTree library

//class for approaching object
class ApproachObject : public BT::SyncActionNode  //sync means it is a blocking call
{
public:
    explicit ApproachObject(const std::string &name) : BT::SyncActionNode(name, {})
    {
    }

    BT::NodeStatus tick() override
    {
        std::cout << "ApproachObject: " << std::endl;
        std::this_thread::sleep_for(5s);
        return BT::NodeStatus::SUCCESS;
    }
};
// custom function for a leaf node
BT::NodeStatus CheckBattery() //checks battery status
{
    std::cout << "Battery is OK" << std::endl;
    return BT::NodeStatus::SUCCESS;
}

//custom class for opening and closing the gripper
class GripperInterface
{
public:
    GripperInterface() : is_open(true)
    {

    }
    BT::NodeStatus open_gripper()
    {
        is_open=true;
        std::cout << "Opening Gripper" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
    BT::NodeStatus close_gripper()
    {
        is_open=false;
        std::cout <<"Gripper close" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
private:
    bool is_open;


};



int main()
{
    //in BehaviorTreeFactory we store all our methods as leaf nodes
    BT::BehaviorTreeFactory factory; 
    factory.registerNodeType<ApproachObject>("ApproachObject");

    factory.registerSimpleAction("CheckBattery", std::bind(CheckBattery));

    GripperInterface gripper;

    factory.registerSimpleAction(
        "OpenGripper", 
        std::bind(&GripperInterface::open_gripper, &gripper));

    factory.registerSimpleAction(
        "CloseGripper", 
        std::bind(&GripperInterface::close_gripper, &gripper));
    
    //creating tree
    auto tree = factory.createTreeFromFile("./../bt_tree.xml");
    
    tree.tickRoot();

    return 0;

}