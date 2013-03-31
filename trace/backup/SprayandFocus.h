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
    
    /*class Statistic{
    private:
        struct compare{
            inline bool operator()(const pair<int, int>& p1, const pair<int, int>& p2)const{
                int left1 = p1.first > p1.second ? p1.first : p1.second;
                int left2 = p1.first < p1.second ? p1.first : p1.second;
                
                int right1 = p2.first > p2.second ? p2.first : p2.second;
                int right2 = p2.first < p2.second ? p2.first : p2.second;
                if(left1 < right1)
                    return true;
                else if(left1 == right1 && left2 < right2)
                    return true;
                else return false;
            }
        };
        long startTime;
        long endTime;
        long interval;
        int L;
        map<int, socialFeature> nodes;
        map<int, int> totalMeetings;
        void readFeature(Reader& reader);
        void readContact(Reader& reader);
        void calculateVectors();
        vector<double> vec(int node, int dest);
        //void insert(int* times, long start);
    public:
        
        Statistic(Reader& reader, int L);
        map<int, int*> Lv;
        map<pair<int, int>, double> predictor;
        map<int, map<int, int>> meetings;
        int getSlot(long start);
        map<pair<int, int>, int*, compare> contactTimes;
        map<pair<int, int>, vector<double>> vectors;
        ~Statistic();
    };
    static Statistic* statistic;*/

}; 


