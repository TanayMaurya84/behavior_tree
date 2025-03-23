#include <iostream>
#include <chrono>
#include <thread>
#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/bt_factory.h"
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std::chrono_literals;




class BallFound : public BT::ConditionNode {
public:
    BallFound(const std::string& name, const BT::NodeConfig& config) : 
        BT::ConditionNode(name, config),attempt(0) {}
    

    static BT::PortsList providedPorts(){
        return { BT::InputPort<int>("attempt") };
    }

    BT::NodeStatus tick() override{
        

        if (attempt == 5) {
            std::cout << "Ball has been found!" << std::endl;
            return BT::NodeStatus::SUCCESS;
        } else {
            if (attempt % 2 == 0) {
                std::cout << "Ball not found yet" << std::endl;
            }
            return BT::NodeStatus::FAILURE;
        }
    }
    
private:
    int attempt; 
   
    
};


class FindBall : public BT::StatefulActionNode
{
public:
    FindBall(const std::string& name,const BT::NodeConfig& config)  
                    : BT::StatefulActionNode(name,config),attempt(0) {}

                    
    
    
    static BT::PortsList providedPorts() {
        return { BT::OutputPort<int>("attempt") };
    }
    BT::NodeStatus onStart() override {  
        std::cout << "Searching for ball..." << std::endl;
        
         
        setOutput("attempt", attempt);
        
        return BT::NodeStatus::RUNNING;
    }

    BT::NodeStatus onRunning() override {  
        
        attempt++;
        setOutput("attempt", attempt);  
        if (attempt == 5) {
            std::cout<<"Ball Found!"<<std::endl<<std::endl;
            return BT::NodeStatus::SUCCESS;
            
        }
        std::this_thread::sleep_for(2s);
        return BT::NodeStatus::RUNNING;
    }
    void onHalted() override {
        std::cout << "FindBall action halted!" << std::endl;
    }


private:
    int attempt;

};

class BallApproached : public BT::ConditionNode {
public:
    BallApproached(const std::string& name, const BT::NodeConfig& config) : 
        BT::ConditionNode(name, config) {}
    

    static BT::PortsList providedPorts(){
        return { BT::InputPort<int>("distance_from_ball") };
    }

    BT::NodeStatus tick() override{
        
        int distance_from_ball=std::rand() % 10 + 4;
        
        if (distance_from_ball <= 5) {
            std::cout << "Ball has been approached!" << std::endl<<std::endl;
            return BT::NodeStatus::SUCCESS;
        } else {
            return BT::NodeStatus::FAILURE;
        }
    }
    

    

    
};
class ApproachBall : public BT::StatefulActionNode
{
public:
    ApproachBall(const std::string& name,const BT::NodeConfig& config)  
                    : BT::StatefulActionNode(name,config),distance_from_ball(std::rand() % 10 + 6) {}

                    
    
    
    static BT::PortsList providedPorts() {
        return { BT::OutputPort<int>("distance_from_ball") };
    }
    BT::NodeStatus onStart() override {  
        std::cout << "Reaching for ball..." << std::endl;
        
        setOutput("distance_from_ball", distance_from_ball);
        
        return BT::NodeStatus::RUNNING;
    }

    BT::NodeStatus onRunning() override {  
        
        distance_from_ball--;
        setOutput("distance_from_ball", distance_from_ball);  
        
        if (distance_from_ball <= 5) {
            std::cout<<"Ball has been Approached !"<<std::endl<<std::endl;
            return BT::NodeStatus::SUCCESS;
            
        }
        std::this_thread::sleep_for(2s);
        return BT::NodeStatus::RUNNING;
    }
    void onHalted() override {
        std::cout << "ApproachBall action halted!" << std::endl;
    }

private:
    int distance_from_ball;

};

class BallGrasped : public BT::ConditionNode {
public:
    BallGrasped(const std::string& name, const BT::NodeConfig& config) : 
        BT::ConditionNode(name, config) {}
    

    static BT::PortsList providedPorts(){
        return { BT::InputPort<int>("trying") };
    }

    BT::NodeStatus tick() override{
        
        int trying=std::rand() % 10;
        
        if (trying == 10) {
            std::cout << "Ball has been grasped!" << std::endl;
            return BT::NodeStatus::SUCCESS;
        } else {
            
            std::cout<<"Ball not grasped yet!"<<std::endl;
            std::this_thread::sleep_for(2s);
            return BT::NodeStatus::FAILURE;
        }
    }
    

    

    
};
class GraspBall : public BT::StatefulActionNode
{
public:
    GraspBall(const std::string& name,const BT::NodeConfig& config)  
                    : BT::StatefulActionNode(name,config),trying(std::rand() % 10) {}

                    
    
    
    static BT::PortsList providedPorts() {
        return { BT::OutputPort<int>("trying") };
    }
    BT::NodeStatus onStart() override {  
        std::cout << "Grasping for ball..." << std::endl;
          
        
        setOutput("try", trying);
        
        return BT::NodeStatus::RUNNING;
    }

    BT::NodeStatus onRunning() override {  
        
        trying++;
        setOutput("try", trying);  
        
        if (trying == 10) {
            std::cout<<"Ball has been now grasped!"<<std::endl<<std::endl;
            return BT::NodeStatus::SUCCESS;
            
        }
        std::this_thread::sleep_for(2s);
        return BT::NodeStatus::RUNNING;
    }
    void onHalted() override {
        std::cout << "ApproachBall action halted!" << std::endl;
    }

private:
    int trying;

};
class BinClose : public BT::ConditionNode {
public:
    BinClose(const std::string& name, const BT::NodeConfig& config) : 
        BT::ConditionNode(name, config) {}
    

    

    BT::NodeStatus tick() override{
        
        int open=std::rand() % 2;
        
        if (open == 1) {
            std::cout << "Bin is opened!" << std::endl<<std::endl;
            return BT::NodeStatus::SUCCESS;
        } else {
            
            std::cout<<"Bin is closed!"<<std::endl<<std::endl;
            std::this_thread::sleep_for(2s);
            return BT::NodeStatus::FAILURE;
        }
    }
    

    

    
};
class OpenBin : public BT::StatefulActionNode
{
public:
    OpenBin(const std::string& name,const BT::NodeConfig& config)  
                    : BT::StatefulActionNode(name,config),open(0) {}

                    
    
    
   
    BT::NodeStatus onStart() override {  
        std::cout << "Opening the bin..." << std::endl;
        
        
       
        
        return BT::NodeStatus::RUNNING;
    }

    BT::NodeStatus onRunning() override {  
        
        open=true;
        std::this_thread::sleep_for(4s);
        
        std::cout<<"Bin is now opened!"<<std::endl<<std::endl;
        return BT::NodeStatus::SUCCESS;
            
       
    }
    void onHalted() override {
        std::cout << "ApproachBall action halted!" << std::endl;
    }

private:
    int open;

};

class BallPlaced : public BT::ConditionNode {
public:
    BallPlaced(const std::string& name, const BT::NodeConfig& config) : 
        BT::ConditionNode(name, config) {}
    

    

    BT::NodeStatus tick() override{
        
        int x=std::rand() % 5;
        int y=std::rand() % 5;
        
        if (x==0 && y==0) {
            std::cout << "Ball is placed in bin!" << std::endl;
            return BT::NodeStatus::SUCCESS;
        } else {
            
            std::cout<<"Bin center not found!"<<std::endl;
            std::this_thread::sleep_for(2s);
            return BT::NodeStatus::FAILURE;
        }
    }
    

    

    
};
class PlaceBall : public BT::StatefulActionNode
{
public:
    PlaceBall(const std::string& name,const BT::NodeConfig& config)  
                    : BT::StatefulActionNode(name,config) {}

                    
    
    
   
    BT::NodeStatus onStart() override {  
        std::cout << "Placing the ball..." << std::endl;
        
        
       
        
        return BT::NodeStatus::RUNNING;
    }

    BT::NodeStatus onRunning() override {  
        
        int x=std::rand() % 5;
        int y=std::rand() % 5;
        while(x!=0 || y!=0){
            
            if(x>0) x--;
            if(y>0) y--;
            std::this_thread::sleep_for(0.2s);
        }
        
        std::cout<<"Ball has been placed in bin !"<<std::endl;
        return BT::NodeStatus::SUCCESS;
            
       
    }
    void onHalted() override {
        std::cout << "ApproachBall action halted!" << std::endl;
    }



};



int main(){
    std::srand(std::time(0));
    BT::BehaviorTreeFactory factory;
    
    factory.registerNodeType<BallFound>("Ball_Found", {BT::InputPort<int>("attempt")});
    factory.registerNodeType<FindBall>("Find_Ball", {BT::OutputPort<int>("attempt")});

    factory.registerNodeType<BallApproached>("Ball_Approached", {BT::InputPort<int>("distance_from_ball")});
    factory.registerNodeType<ApproachBall>("Approach_Ball", {BT::OutputPort<int>("distance_from_ball")});

    factory.registerNodeType<BallGrasped>("Ball_Grasped", {BT::InputPort<int>("trying")});
    factory.registerNodeType<GraspBall>("Grasp_Ball", {BT::OutputPort<int>("trying")});

    factory.registerNodeType<BinClose>("Bin_Opened", {BT::InputPort<bool>("open")});
    factory.registerNodeType<OpenBin>("Open_Bin", {BT::OutputPort<int>("open")});

    factory.registerNodeType<BallPlaced>("Ball_Placed", {BT::InputPort<int>("x"),BT::InputPort<int>("y")});
    factory.registerNodeType<PlaceBall>("Place_Ball",{BT::OutputPort<int>("x"),BT::OutputPort<int>("y")});
   
    
    auto tree = factory.createTreeFromFile("./../pick_place_tree.xml");
    tree.subtrees.front()->blackboard->set("attempt", 0);
    tree.tickWhileRunning();
    return 0;
}

