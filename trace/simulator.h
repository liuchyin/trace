//
//  simulator.h
//  trace
//
//  Created by Cong on 13-3-6.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once

#include <vector>
#include <map>
#include "message.h"

#include "Reader.h"
#include "clock.h"

#include "node.h"
using namespace std;

enum nextEvent{CONTACT = 1, MESSAGE = 2, FINISH = 0};


class Simulator{
private:
    
    double* delivery;
    double* delay;
    double* forwarding;
    map<int, Node*> nodes;
    int countProtocol;
    int protocols;
	vector<Common*>* commons;
    //vector<Contact*>* contacts;
protected:
    virtual vector<Node*>& createNodes(int id) = 0;//以后改成工厂模式
public:
    Simulator() : protocols(0){}
    void start(Reader& reader, int messageNumber);
    int getProtocols();
    double* getDelivery(){
        return delivery;
    }
    double* getDelay(){
        return delay;
    }
    double* getForwarding(){
        return forwarding;
    }
    virtual ~Simulator();
private:
    void processData();
    void processData1();
    int nextTime(int countContact, int countMessage, vector<Common*>& coms, vector<Contact*>& cons);
    vector<Common*> createMessages(Reader& reader, int messageNumber);
    Node* getNode(int id);
    void createMessage(Common* common);
    void handleConnect(Contact* contact);
    void random(int* index, int size);
    void clearNodes();

};


