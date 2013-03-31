//
//  SprayandFocus.h
//  trace
//
//  Created by Cong on 13-3-7.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once

#include "node.h"
#include <iostream>
#include "reader.h"
//#include "socialFeature.h"


class SourceSprayFocus : public Node{

private:
    
    class TicketMessage : public Message{
    public:
        int tickets;
        TicketMessage(TicketMessage* t) : Message(t->common), tickets(t->tickets){}
        TicketMessage(Common* common) : Message(common), tickets(4){}
        inline bool share(){
            return tickets != 1;
        }
    };
    
protected:
    //return true if node2 is better
    virtual bool compare(int node2, int dest){
        return false;
    }
public:
    SourceSprayFocus(int id) : Node(id){}
    void connect(Node* node2);
    Message* createMessage(Common* common);
    virtual ~SourceSprayFocus(){};
    
    
public:
    
    
}; 


