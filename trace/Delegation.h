//
//  Sosim.h
//  trace
//
//  Created by Cong on 13-3-11.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//
#pragma once

#include <iostream>
#include <map>
#include <cmath>
//#include "reader.h"
//#include "socialFeature.h"
#include "node.h"

class Delegation : public Node{
public:


    class thresMessage : public Message{
    public:
        thresMessage(Common* common) : Message(common){}
        thresMessage(thresMessage* t) : Message(t->common), threshold(t->threshold){}
        double threshold;
    };
    
    Delegation(int id) : Node(id){}
    
    void connect(Node* node2);
    Message* createMessage(Common* common);
    virtual ~Delegation(){}
    
protected:
    virtual double predictor(int node, int dest) = 0;

};


/*class Tanimoto1 : public Sosim{
public:
    Tanimoto1(int id) : Sosim(id){
    }
protected:
    double similarity(vector<double>& v){
        double xy = 0;
        double xx = 0;
        double yy = 0;
        for(int i = 0; i != 6; i++){
            xy += v[i];
            xx += 1;
            yy += v[i] * v[i];
        }
        return xy / (xx + yy - xy);
    }
};

class Euclidean1 : public Sosim{
public:
    Euclidean1(int id) : Sosim(id){
    }
protected:
    double similarity(vector<double>& v){
        //cout<<111<<endl;
        //if(v.empty())
          //  cout<<this->getID()<<endl;
        double sum = 0;
        for(int i = 0; i != 6; ++i){
            sum += (1 - v[i]) * (1 - v[i]);
        }
        return 1 - sqrt(sum / 6);
    }
};*/




