//
//  SprayandFocus.cpp
//  trace
//
//  Created by Cong on 13-3-7.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#include "SprayandFocus.h"
#include "clock.h"



void SourceSprayFocus::connect(Node* _node2){
    SourceSprayFocus* node2 = (SourceSprayFocus*)_node2;
    
    
    messageContainter::const_iterator end = messages.end();
    for(messageContainter::iterator iter = messages.begin();
        iter != end;
        )
    {
        //cout<<iter->first<<endl;
        TicketMessage* message =  (TicketMessage*)iter->second;
        
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
        
        //spray phase
        //delivery message with half of tokens 
        if(message->share() && !node2->messages.count(message->getID())){
            message->tickets /= 2;
            TicketMessage* newM = new TicketMessage(message);
            node2->messages[newM->getID()] = newM;
            ++iter;
            continue;
        }
        
        //focus 
        if(!message->share() && !node2->messages.count(message->getID())
           && compare(node2->getID(), message->common->destination)){
            TicketMessage* newM = new TicketMessage(message);
            node2->messages[newM->getID()] = newM;
            delete iter->second;
            messages.erase(iter++);
            //++iter;
            continue;
        }
        ++iter;
    }   
    
}


Message* SourceSprayFocus::createMessage(Common* common){
    return new TicketMessage(common);
}