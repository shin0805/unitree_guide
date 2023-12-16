/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef ROS_H
#define ROS_H

#include "FSM/FSMState.h"
#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"

class State_ROS : public FSMState{
public:
    State_ROS(CtrlComponents *ctrlComp);
    ~State_ROS(){}
    void enter();
    void sub_callback(const std_msgs::Float32MultiArray::ConstPtr& msg);
    void run();
    void exit();
    FSMStateName checkChange();

private:
    ros::NodeHandle _nh;
    ros::Subscriber _angle_sub = _nh.subscribe("/go1_mani/target_pos", 5, &State_ROS::sub_callback, this);
    float _targetPos[12] = {0.0, 0.67, -1.3, 0.0, 0.67, -1.3, 
                            0.0, 0.67, -1.3, 0.0, 0.67, -1.3};
    std_msgs::Float32MultiArray _targetMsg;
    float _startPos[12];
    float _duration = 1000;   //steps
    float _percent = 0;       //%
};

#endif  // ROS_H
