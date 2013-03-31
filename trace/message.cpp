//
//  message.cpp
//  trace
//
//  Created by Cong on 13-3-6.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#include "message.h"

long Message::TTL;

bool Common::equals(Common* common){
	return id == common->id;
}

Common::Common(Common* common) : id(common->id), source(common->source), destination(common->destination), creatingTime(common->creatingTime), deliveredTime(common->deliveredTime), copies(0){
}

Message::Message(Message* message){
	this->common = message->common;
    this->common->copies++;
}

Message::Message(Common* common){
	this->common = common;
    this->common->copies++;
}


bool Message::equals(Message* message){
	return common->id == message->common->id;
}

bool Message::equals(Common* common){
	return this->common->id == common->id;
}
