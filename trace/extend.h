//
//  extend.h
//  trace
//
//  Created by Cong on 13-3-13.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once

#include <iostream>
#include <cmath>
#include "SprayandFocus.h"
#include "Delegation.h"
#include "clock.h"

struct Fault{
    double inline operator()(int node1, int node2){
        return 0;
    }
};

template<class T = Fault>
class extendSpray : public SourceSprayFocus{
public:
    extendSpray(int id) : SourceSprayFocus(id){}
    
private:
    T value;
protected:
    bool compare(int node2, int dest){
        double value1 = value(this->getID(), dest);
        double value2 = value(node2, dest);
        if (value2 > value1)
            return true;
        else return false;
    }

};



template<class T = Fault>
class extendDel : public Delegation{
public:
    extendDel(int id) : Delegation(id){}
private:
    T value;
protected:
    double predictor(int node, int dest){
        return value(node, dest);
    }
};


template<int T>
class Average{
public:
    double operator()(int node1, int node2){
        //cout<<node1<<" "<<node2<<endl;
        pair<int, int> p(node1, node2);
        int* times;
        if(SourceSprayFocus::statistic->contactTimes.count(p))
            times = SourceSprayFocus::statistic->contactTimes.find(p)->second;
        else return 0;
        
        int slot = SourceSprayFocus::statistic->getSlot(clock::getTime());
        int start = 0;
        if(slot < T)
            return 0;
        else start = slot - T;
        double sum = 0.0;
        for(int i = start; i != slot; ++i){
            sum += times[i];
        }
        return sum / T;
    }
    double operator()(int node1, int node2, int slot){
        //cout<<node1<<" "<<node2<<endl;
        pair<int, int> p(node1, node2);
        int* times;
        if(SourceSprayFocus::statistic->contactTimes.count(p))
            times = SourceSprayFocus::statistic->contactTimes.find(p)->second;
        else return 0;
        
        int start = 0;
        if(slot < T)
            return 0;
        else start = slot - T;
        double sum = 0.0;
        for(int i = start; i != slot; ++i){
            sum += times[i];
        }
        return sum / T;
    }
};



template<int T>
class WeightFrequency{
private:
    int sum;
public:
    WeightFrequency(){
        sum = 0;
        for(int i = 1; i <= T; ++i)
            sum += i;
    }
    double operator()(int node1, int node2){
        pair<int, int> p(node1, node2);
        int* times;
        if(SourceSprayFocus::statistic->contactTimes.count(p))
            times = SourceSprayFocus::statistic->contactTimes.find(p)->second;
        else return 0;
        
        int slot = SourceSprayFocus::statistic->getSlot(clock::getTime());
        int start = 0;
        if(slot < T)
            return 0;
        else start = slot - T;
        double weight = 0;
        for(int i = start; i != slot; ++i){
            weight += times[i] * (i - start + 1);
        }
        return weight / sum;
    }
};



template<int T>
class  LinearRegression{
private:
    int sum;
    int squareSum;
public:
    LinearRegression(){
        sum = 0;
        squareSum = 0;
        for(int i = 1; i <= T; ++i){
            sum += i;
            squareSum += i * i;
        }
    }
    double operator()(int node1, int node2){
        pair<int, int> p(node1, node2);
        int* times;
        if(SourceSprayFocus::statistic->contactTimes.count(p))
            times = SourceSprayFocus::statistic->contactTimes.find(p)->second;
        else return 0;
        
        int slot = SourceSprayFocus::statistic->getSlot(clock::getTime());
        int start = 0;
        if(slot < T)
            return 0;
        else start = slot - T;
        double a1 = (T + 1) * T - sum;
        double a2 = -(T + 1) * sum + squareSum;
        double b1 = 0;
        double b2 = 0;
        for(int i = start; i != slot; ++i){
            b1 += (i - start + 1) * times[i];
            b2 += times[i];
        }
        double up = a1 * b1 + a2 * b2;
        double down = T * squareSum - sum * sum;
        /*double result = up / down;
        if(result > 0){
            cout<<node1<<" "<<node2<<" "<<slot<<endl;
            for(int i = start; i!= slot; ++i){
                cout<<times[i]<<" ";
            }
            cout<<endl;
            cout<<a1<<" "<<a2<<" "<<b1<<" "<<b2<<endl;
        }*/
        return up / down;
    }
};




class Tanimoto{
public:

    double operator()(int node1, int node2){
        
        vector<double>& v = SourceSprayFocus::statistic->vectors.find(pair<int, int>(node1, node2))->second;
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

class Euclidean{
public:

    double operator()(int node1, int node2){
        vector<double>& v = SourceSprayFocus::statistic->vectors.find(pair<int, int>(node1, node2))->second;
        double sum = 0;
        for(int i = 0; i != 6; ++i){
            sum += (1 - v[i]) * (1 - v[i]);
        }
        return 1 - sqrt(sum / 6);
    }
};