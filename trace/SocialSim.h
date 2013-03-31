//
//  SocialSim.h
//  trace
//
//  Created by Cong on 13-3-19.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once

#include <iostream>
#include "Delegation.h"
#include "SprayandFocus.h"

template<class Similarity>
class SosimDel : public Delegation {
public:
    SosimDel(int id) : Delegation(id){}
private:
    Similarity sim;
protected:
    double predictor(int node, int dest){
        return sim(node, dest);
    }
};

template <class Similarity>
class SosimSpray : public SourceSprayFocus{
public:
    SosimSpray(int id) : SourceSprayFocus(id){}
private:
    Similarity sim;
protected:
    bool compare(int node2, int dest){
        double sim1 = sim(this->getID(), dest);
        double sim2 = sim(node2, dest);
        if (sim2 > sim1)
            return true;
        else return false;
    }
};
