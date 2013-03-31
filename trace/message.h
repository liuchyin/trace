//
//  message.h
//  trace
//
//  Created by Cong on 13-3-6.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once

#include <vector>
using namespace std;

class Common{
public:
    int id;
    int source;
    int destination;
    long creatingTime;
	long deliveredTime;
	int copies;
    
	
    
public:
	Common(): deliveredTime(-1), copies(0){
	};
    Common(Common*);
	bool equals(Common* common);
};

class Message{
public:
    static long TTL;
	Common* common;
    
public:
	Message(Message* message);
	Message(Common* common);
	bool equals(Common* common);
	bool equals(Message* message);
    int getID(){
        return common->id;
    }
    virtual ~Message(){
    }
};





