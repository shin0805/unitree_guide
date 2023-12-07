/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef HOLD_H
#define HOLD_H

#include "FSM/FSMState.h"

class State_Hold : public FSMState{
public:
    State_Hold(CtrlComponents *ctrlComp);
    ~State_Hold(){}
    void enter();
    void run();
    void exit();
    FSMStateName checkChange();

private:
    float _targetPos[12] = {0.5, 0.67, -1.3, -0.5, 0.67, -1.3, 
                            0.5, 0.67, -1.3, -0.5, 0.67, -1.3};
    float _startPos[12];
    float _duration = 1000;   //steps
    float _percent = 0;       //%
};

#endif  // HOLD_H
