//
//  newPredictor.h
//  trace
//
//  Created by Cong on 13-3-27.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//
#pragma once

#include <iostream>
#include "IndiGroup.h"

template<class Similarity, class History>
class simplePredictor : public getPredictor<Similarity, History>{
protected:
    double calPre(int node, int dest, int* L){
        double rvd = this->his(node, dest);
        double svd = this->sim(node, dest);
        return rvd + svd;
    }
};

template<class Simlilarity, class History>
class enhancedPredictor : public getPredictor<Simlilarity, History>{
protected:
    double calPre(int node, int dest, int* L){
        double rvd = this->his(node, dest);
        
        double sumUp = this->sim(node, dest);
        int size = 1;
        
        for(int i = 0; i != 10; ++i){
            if(this->his(L[i], node) <= 0)
                break;
            double szd;
            if(L[i] == dest)
                szd = 1;
            else
                szd =  this->sim(L[i], dest);
            //Szd
            //Szd * Rvz
            sumUp += szd * this->his(L[i], node);
            size++;
        }
        
        return rvd + sumUp / size;
    }
};




template<class Similarity, class History>
class SimpleSpray : public SourceSprayFocus{
public:
    SimpleSpray(int id) : SourceSprayFocus(id){
        
    }
private:
    simplePredictor<Similarity, History> pre;
protected:
    bool compare(int node2, int dest){
        
        double pre1;
        double pre2;
        pre1 = pre.getPre(this->getID(), dest);
        pre2 = pre.getPre(node2, dest);
        
        if(pre2 > pre1)
            return true;
        else return false;
    }
    
};


template<class Similarity, class History>
class SimpleDel : public Delegation{
public:
    SimpleDel(int id) : Delegation(id){
    }
private:
    simplePredictor<Similarity, History> pre;
protected:
    double predictor(int node, int dest){
        
        double pre = this->pre.getPre(node, dest);
        
        return pre;
    }
    
};

template<class Similarity, class History>
class EnhancedSpray : public SourceSprayFocus{
public:
    EnhancedSpray(int id) : SourceSprayFocus(id){
        
    }
private:
    enhancedPredictor<Similarity, History> pre;
protected:
    bool compare(int node2, int dest){
        
        double pre1;
        double pre2;
        pre1 = pre.getPre(this->getID(), dest);
        pre2 = pre.getPre(node2, dest);
        
        if(pre2 > pre1)
            return true;
        else return false;
    }
    
};


template<class Similarity, class History>
class EnhancedDel : public Delegation{
public:
    EnhancedDel(int id) : Delegation(id){
    }
private:
    enhancedPredictor<Similarity, History> pre;
protected:
    double predictor(int node, int dest){
        
        double pre = this->pre.getPre(node, dest);
        
        return pre;
    }
    
};

