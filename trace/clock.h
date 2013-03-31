//
//  clock.h
//  trace
//
//  Created by Cong on 13-3-14.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//
#pragma once

#include <iostream>
#include "simulator.h"
class clock{
    friend class Simulator;
private:
    static long curTime;
    static void reset(){
        curTime = 0;
    }
public:
    static long getTime(){
        return curTime;
    }
};

