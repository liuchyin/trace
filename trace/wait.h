//
//  wait.h
//  trace
//
//  Created by Cong on 13-3-19.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once

#include "node.h"
#include "clock.h"
class Wait : public Node{
public:
    Wait(int id) : Node(id){}
    void connect(Node* node2){
        messageContainter::const_iterator end = messages.end();
        for(messageContainter::iterator iter = messages.begin();
            iter != end;)
        {
            Message* message = iter->second;
            
            //discard outdated message
            if(clock::getTime() - message->common->creatingTime >= Message::TTL
               || message->common->deliveredTime != -1){
                delete iter->second;
                messages.erase(iter++);
                continue;
            }
            //encounter destination
            if(message->common->destination == node2->getID()){
                message->common->deliveredTime = clock::getTime();
                message->common->copies++;
                delete iter->second;
                messages.erase(iter++);
                //cout<<"delivered!"<<endl;
                continue;
            }
            
            ++iter;
        }
    }

};


