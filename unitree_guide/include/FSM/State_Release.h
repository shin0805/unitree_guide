/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef RELEASE_H
#define RELEASE_H

#include "FSM/FSMState.h"

class State_Release : public FSMState{
public:
    State_Release(CtrlComponents *ctrlComp);
    ~State_Release(){}
    void enter();
    void run();
    void exit();
    FSMStateName checkChange();

private:
    float _targetPos[12] = {-1.0, 0.67, -1.3, 1.0, 0.67, -1.3, 
                            -1.0, 0.67, -1.3, 1.0, 0.67, -1.3};
    float _startPos[12];
    float _duration = 1000;   //steps
    float _percent = 0;       //%
};

#endif  // RELEASE_H
