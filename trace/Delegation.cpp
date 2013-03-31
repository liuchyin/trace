//
//  Sosim.cpp
//  trace
//
//  Created by Cong on 13-3-11.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#include "Delegation.h"
#include "clock.h"


void Delegation::connect(Node* node2){
    messageContainter::const_iterator end = messages.end();
    for(messageContainter::iterator iter = messages.begin();
        iter != end;)
    {
        thresMessage* message = (thresMessage*)iter->second;
        
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
        
        
        
        if(!node2->messages.count(message->getID())){
            double newThres = predictor(node2->getID(), message->common->destination);
            double curThres = predictor(this->getID(), message->common->destination);
            if(newThres > curThres){
                //message->threshold = newThres;
                thresMessage* newM = new thresMessage(message);
                node2->messages[newM->getID()] = newM;
                delete iter->second;
                messages.erase(iter++);
            }else
                ++iter;
            continue;
        }
        
        ++iter;
    }
}

Message* Delegation::createMessage(Common* common){
    thresMessage* newM = new thresMessage(common);
    newM->threshold = predictor(this->getID(), common->destination);
    return newM;
}






