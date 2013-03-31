//
//  IndiGroup.h
//  trace
//
//  Created by Cong on 13-3-15.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once

#include <iostream>
#include "SprayandFocus.h"
#include "extend.h"
#include "Delegation.h"


bool c(pair<int, double>& p1, pair<int, double>& p2);

template<class Similarity, class History>
class getPredictor{
protected:
    Similarity sim;
    History his;
    
    int* Lnodes(int node, int dest){
        map<int, int>& meetTimes = Node::statistic->meetings.find(node)->second;
        int t = Node::statistic->getSlot(clock::getTime());
        pair<int, int> p(node, t);
        if(!Node::statistic->Lv.count(p)){
            Node::statistic->Lv[p] = new int[10];
            
            vector<pair<int, double>> n;
            
            for(map<int, int>::iterator iter  = meetTimes.begin();
                iter != meetTimes.end();
                ++iter)
            {
                n.push_back(pair<int, double>(iter->first, his(node, iter->first)));//his(node, iter->first)));//his(node, iter->first)));
            }
            
            sort(n.begin(), n.end(), c);
            //cout<<node<<endl;
            for (int i = 0; i != 10; ++i) {
                Node::statistic->Lv[p][i] = n[i].first;
                //cout<<n[i].first<<" "<<n[i].second<<endl;
            }
            
        }
        return Node::statistic->Lv[p];
    }
    virtual double calPre(int node, int dest, int* L){

        double rvd = his(node, dest);
        //cout<<rvd<<endl;
        double svd = sim(node, dest); 
        double sumUp = svd;
        double sumDown = svd;
        int size = 1;
        for(int i = 0; i != 10; ++i){
            if (his(L[i], node) <= 0){
                continue;
            }
            double szd;
            if(L[i] == dest)
                szd = 1;
            else
                szd = sim(L[i], dest);
            //Szd
            sumDown += szd;
            //Szd * Rvz
            sumUp += szd * his(L[i], node);
            ++size;
            
        }
        //if(sumUp == svd)
            //return rvd;
        //if(rvd == 0)
            //return 0;
        cout<<rvd<<" "<<rvd + sumUp / sumDown<<" "<<rvd + svd<<" "<< rvd + sumUp / size<<endl;
        return rvd + sumUp / sumDown;
        
        
    }
public:
    double getPre(int node, int dest){
        double pre = 0;
        
        int* L = Lnodes(node, dest);
        pre = calPre(node, dest, L);
        
        return pre;
    }
};


template<class Similarity, class History>
class IndiGroupSpray : public SourceSprayFocus{
public:
    IndiGroupSpray(int id) : SourceSprayFocus(id){
        
    }
private:
    getPredictor<Similarity, History> pre;
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
class IndiGroupDel : public Delegation{
public:
    IndiGroupDel(int id) : Delegation(id){
    }
private:
    getPredictor<Similarity, History> pre;
protected:
    double predictor(int node, int dest){

        double pre = this->pre.getPre(node, dest);
        
        return pre;
    }
    
};
