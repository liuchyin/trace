//
//  simulator.cpp
//  trace
//
//  Created by Cong on 13-3-6.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#include "simulator.h"
#include <map>
#include "constants.h"
#include <iostream>
using namespace std;

int Simulator::getProtocols(){
    if (protocols != 0) {
        return protocols;
    }
    vector<Node*> temp = createNodes(0);
    int size = (int)temp.size();
    for(int i = 0; i != size; i++)
        delete temp[i];
    return size;
}

void Simulator::start(Reader& reader,int messageNumber){

    vector<Contact*>& contacts = reader.getContacts();

    long maxTime = reader.getMaxTime();
    
    protocols = getProtocols();
    
    commons = new vector<Common*>[protocols];
    commons[0] = createMessages(reader, messageNumber);
    //cout<<protocols<<endl;
  
    // copy commons
    for(int i = 1; i != protocols; i++){
        for(int j = 0; j != commons[0].size(); j++){
            commons[i].push_back(new Common(commons[0][j]));
        }
    }
    //  int a;
   // cin>>a;

    for(countProtocol = 0; countProtocol != protocols; ++ countProtocol){
        clock::reset();
        unsigned int countContact = 0;
        unsigned int countMessage = 0;
        int event;
        //int count = 0;
        while((event = nextTime(countContact, countMessage, commons[countProtocol], contacts))){
            if(event == MESSAGE){
                //cout<<"Message"<<endl;
                clock::curTime = commons[countProtocol][countMessage]->creatingTime;
                if(clock::curTime > maxTime)
                    break;
                createMessage(commons[countProtocol][countMessage]);

                countMessage++;
            }else{
                //cout<<"Contact"<<endl;
                clock::curTime = contacts[countContact]->start;
                if(clock::curTime > maxTime)
                    break;
                handleConnect(contacts[countContact]);
                countContact++;
            }
           // cout<<count<<endl;
           // count++;
            //cout<<clock::getTime()<<endl;
        }
        clearNodes();
    }
    processData();
    for(int i = 0; i != protocols; ++i){
        for(int j = 0; j != messageNumber; ++j){
            delete commons[i][j];
        }
    }
    //delete commons;
}


vector<Common*> Simulator::createMessages(Reader& reader, int messageNumber){
    long startTime = reader.getMinTime();
    long endTime = reader.getMaxTime();
    
    //startTime += (endTime - startTime) / 10;
    
    set<int>& _nodes1 = reader.getNodes1();
    set<int>& _nodes2 = reader.getNodes2();
    vector<int> nodes1(_nodes1.size());
    vector<int> nodes2(_nodes2.size());
    copy(_nodes1.begin(), _nodes1.end(), nodes1.begin());
    copy(_nodes2.begin(), _nodes2.end(), nodes2.begin());
    
    long interval = (endTime - startTime) / messageNumber; /// 2;
    
    int count1 = 0;
    int count2 = 0;
    vector<Common*> messages;
    messages.reserve(messageNumber);
    
    int* index = new int[nodes2.size()];
    random(index, (int)nodes2.size());
    
    for (int i = 0; i != messageNumber; ++ i) {
        Common* common = new Common();
        common->id = i;
        common->source = nodes1[count1];
        ++ count1;
        if (count1 == nodes1.size()) {
            count1 = 0;
        }
        while (true) {
            common->destination = nodes2[index[count2]];
            ++ count2;
            if (count2 == nodes2.size()) {
                count2 = 0;
                random(index, (int)nodes2.size());
            }
            if (common->source != common->destination) break;
        }
        //cout<<i<<" "<<common->source<<" "<<common->destination<<endl;
        common->creatingTime = startTime;
        startTime += interval;
        messages.push_back(common);
    }
    delete index;
    return messages;
}

Node* Simulator::getNode(int id){
    if(nodes.count(id)){
        return nodes.find(id)->second;
    }else{
        vector<Node*> temp = createNodes(id);
        nodes[id] = temp[countProtocol];
        for(int i = 0; i != protocols; ++i){
            if(i != countProtocol)
                delete temp[i];
        }
        return nodes[id];
    }
}

int Simulator::nextTime(int countContact, int countMessage, vector<Common*>& coms, vector<Contact*>& cons){
    if(countMessage < coms.size() && countContact < cons.size()){
        if(coms[countMessage]->creatingTime < cons[countContact]->start){
            return MESSAGE;
        }else
            return CONTACT;
    }else{
        if(countContact < cons.size())
            return CONTACT;
        if(countMessage < coms.size())
            return MESSAGE;
        return FINISH;
    }
}

void Simulator::createMessage(Common* common){
    Node* node = getNode(common->source);
    Message* message = node->createMessage(common);
    
    node->messages.insert(messageContainter::value_type(message->getID(), message));
    //[message->getID()] = message;
}

void Simulator::handleConnect(Contact* contact){
    Node* node1 = getNode(contact->node1);
    Node* node2 = getNode(contact->node2);
    //cout<<"handle"<<endl;
    node1->connect(node2);
    node2->connect(node1);
}

void Simulator::random(int* index, int size){
    for (int j = 0; j < size; ++ j) {
        index[j] = j;
    }
    for (int j = size - 1; j > 0; -- j) {
        int in = rand()%j + 1;
        swap(index[j], index[in]);
    }
}

void Simulator::clearNodes(){
    map<int, Node*>::iterator end = nodes.end();
    for(map<int, Node*>::iterator iter = nodes.begin();
        iter != end;
        ++iter)
        delete iter->second;
    nodes.clear();
}

void Simulator::processData(){
    delivery = new double[countProtocol];
    delay = new double[countProtocol];
    forwarding = new double[countProtocol];
    
    int protocol = (int)createNodes(0).size();
    int messageNumber = (int)commons[0].size();
    
    for(int i = 0; i != protocol; ++i){
        //int delivered = 0;
        delivery[i] = 0;
        delay[i] = 0;
        forwarding[i] = 0;
        for(int j = 0; j != messageNumber; ++j){
            Common* com = commons[i][j];
            if(com->deliveredTime >= 0){
                //cout<<j<<" "<<(com->deliveredTime - com->creatingTime) / MINUTE<<" "<<com->copies - 1<<endl;
                delivery[i]++;
                delay[i] += (com->deliveredTime - com->creatingTime) / MINUTE;
                forwarding[i] += com->copies - 1;
            }
        }
        delay[i] /= delivery[i];
        forwarding[i] /= delivery[i];
        delivery[i] /= messageNumber;
        
    }
}

void Simulator::processData1(){
    delivery = new double[countProtocol];
    delay = new double[countProtocol];
    forwarding = new double[countProtocol];
    
    int protocol = (int)createNodes(0).size();
    int messageNumber = (int)commons[0].size();
    
    for(int i = 0; i != protocol; ++i){
        delivery[i] = 0;
        delay[i] = 0;
        forwarding[i] = 0;
    }
    
    int countDelay = 0;
    for(int j = 0; j != messageNumber; ++j){
        int delivered = 0;
        for(int i = 0; i != protocol; ++i){
            Common* com = commons[i][j];
            if(com->deliveredTime >= 0){
                delivery[i]++;
                delivered++;
            }
            forwarding[i]+=com->copies - 1;
        }
        if(delivered == protocol){
            countDelay++;
            for(int i = 0; i != protocol; ++i)
                delay[i] += (commons[i][j]->deliveredTime - commons[i][j]->creatingTime) / MINUTE;
        }
    }
    for(int i = 0; i != protocol; ++i){
        delay[i] /= countDelay;
        forwarding[i] /= messageNumber;
        delivery[i] /= messageNumber;
    }
}

Simulator::~Simulator(){
    
    
}

