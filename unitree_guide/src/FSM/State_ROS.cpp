/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#include <iostream>
#include "FSM/State_ROS.h"

State_ROS::State_ROS(CtrlComponents *ctrlComp)
                :FSMState(ctrlComp, FSMStateName::ROS, "ros"){
}

void State_ROS::sub_callback(const std_msgs::Float32MultiArray::ConstPtr& msg) { 
  std::cout << "[Go1 got message] move to {";
  _targetMsg = *msg; 
  for (int i = 0; i < 12; i++) {
    _targetPos[i] = _targetMsg.data.at(i);
    std::cout << _targetPos[i] << (i == 11 ? "}" : ", ");
  }
  std::cout << std::endl;
  State_ROS::enter();
  _percent = 0;
}

void State_ROS::enter(){
    for(int i=0; i<4; i++){
        if(_ctrlComp->ctrlPlatform == CtrlPlatform::GAZEBO){
            _lowCmd->setSimStanceGain(i);
        }
        else if(_ctrlComp->ctrlPlatform == CtrlPlatform::REALROBOT){
            _lowCmd->setRealStanceGain(i);
        }
        _lowCmd->setZeroDq(i);
        _lowCmd->setZeroTau(i);
    }
    for(int i=0; i<12; i++){
        _lowCmd->motorCmd[i].q = _lowState->motorState[i].q;
        _startPos[i] = _lowState->motorState[i].q;
    }
    _ctrlComp->setAllStance();
}

void State_ROS::run(){
    _percent += (float)1/_duration;
    _percent = _percent > 1 ? 1 : _percent;
    for(int j=0; j<12; j++){
        _lowCmd->motorCmd[j].q = (1 - _percent)*_startPos[j] + _percent*_targetPos[j]; 
    }
}

void State_ROS::exit(){
    _percent = 0;
    _angle_sub.shutdown();
}

FSMStateName State_ROS::checkChange(){
    if(_lowState->userCmd == UserCommand::L2_B){
        return FSMStateName::PASSIVE;
    }
    else if(_lowState->userCmd == UserCommand::L2_X){
        return FSMStateName::FREESTAND;
    }
    else if(_lowState->userCmd == UserCommand::L2_A){
        return FSMStateName::FIXEDSTAND;
    }
    else if(_lowState->userCmd == UserCommand::HOLD){
        return FSMStateName::HOLD;
    }
    else if(_lowState->userCmd == UserCommand::RELEASE){
        return FSMStateName::RELEASE;
    }
    else{
        return FSMStateName::ROS;
    }
}
