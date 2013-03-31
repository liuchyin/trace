//
//  Epidemic.cpp
//  trace
//
//  Created by Cong on 13-3-10.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#include "Epidemic.h"
#include "clock.h"
void Epidemic::connect(Node* node2){
    
    messageContainter::const_iterator end = messages.end();
    for(messageContainter::iterator iter = messages.begin();
        iter != end;
        )
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
        
        if( !node2->messages.count(message->getID())){
            Message* newM = new Message(message);
            node2->messages[newM->getID()] = newM;
            ++iter;
            continue;
        }
        ++iter;
    }
    
    
}