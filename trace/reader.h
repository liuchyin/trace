//
//  reader.h
//  trace
//
//  Created by Cong on 13-3-6.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//
#pragma once

#include <set>
#include <vector>
#include "contact.h"
#include <string>
using namespace std;

//const long longmax = 2147483647L;

class Reader{
protected:
    vector<Contact*> contacts;
    set<int> nodes1;
    set<int> nodes2;
    long minTime;
    long maxTime;
public:
    vector<Contact*>& getContacts(){
        return contacts;
    }
    set<int>& getNodes1(){
        return nodes1;
    }
    set<int>& getNodes2(){
        return nodes2;
    }
    long getMinTime(){
        return minTime;
    }
    long getMaxTime(){
        return maxTime;
    }
    virtual string getName(){
        return "reader";
    }
    virtual ~Reader(){
        
    }
};

