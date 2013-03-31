//
//  node.h
//  trace
//
//  Created by Cong on 13-3-6.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once

#include <map>
#include "message.h"
#include "reader.h"
#include "socialFeature.h"
//#include "clock.h"
#include <string>
using namespace std;

typedef map<int, Message*> messageContainter;



class Node{
protected:
    int id;
    
public:
    messageContainter messages;
    Node(int id) : id(id){}
    int getID(){
        return id;
    }
    
    virtual string getName(){
        return "Node";
    }
    
    
    virtual void connect(Node* node2) = 0;
    virtual Message* createMessage(Common* common);
    virtual ~Node();
    
public:
    class Statistic{
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
                void print();
                Statistic(Reader& reader, int L);
                map<pair<int, int> , int*> Lv;
                map<pair<int, int>, double> predictor;
                map<int, map<int, int>> meetings;
                int getSlot(long start);
                map<pair<int, int>, int*, compare> contactTimes;
                map<pair<int, int>, vector<double>> vectors;
                ~Statistic();
                };
                static Statistic* statistic;
};

