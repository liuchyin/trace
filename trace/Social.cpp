//
//  Social.cpp
//  trace
//
//  Created by Cong on 13-3-10.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#include "Social.h"

Social::Statistics* Social::statistics;

bool Social::compare(int node2, int dest){
    
    int similarFeature1 = getValue(this->getID(), dest);

    int similarFeature2 = getValue(node2, dest);

    
    if(similarFeature1 < similarFeature2)
        return true;
    else return false;
}

int Social::getValue(int _node1, int _node2){
    int value = 0;
    socialFeature* node1 = &statistics->nodes.find(_node1)->second;
    socialFeature* node2 = &statistics->nodes.find(_node2)->second;


    if(node1->city == node2->city)
        value++;
    if(node1->country == node2->country)
        value++;
    if(node1->position == node2->position)
        value++;
    
    if(simility(node1->language, node2->language))
        value++;
    
    if(simility(node1->nationality, node2->nationality))
        value++;
    
    if(simility(node1->affiliation, node2->affiliation))
        value++;
     
    return value;
}

bool Social::simility(set<int>& set1, set<int>& set2){
    typedef set<int>::iterator iterator;
    iterator end = set1.end();
    for(iterator iter = set1.begin();
        iter != end;
        ++iter)
    {
        if(set2.count(*iter)){
            return true;
        }
    }
    return false;
}


Social::Statistics::Statistics(Reader& reader){
    set<int>& node1 = reader.getNodes1();
    set<int>& node2 = reader.getNodes2();
    typedef set<int>::iterator iterator;
    iterator end = node1.end();
    for(iterator iter = node1.begin();
        iter != end;
        iter++)
    {
        if(!nodes.count(*iter)){
            //nodes[*iter] = new socialFeature(*iter);
            nodes.insert(map<int, socialFeature>::value_type(*iter, socialFeature(*iter)));
        }
    }
    
    end = node2.end();
    for(iterator iter = node2.begin();
        iter != end;
        iter++)
    {
        if(!nodes.count(*iter)){
            //nodes[*iter] = new socialFeature(*iter);
            nodes.insert(map<int, socialFeature>::value_type(*iter, socialFeature(*iter)));
        }
    }
    
}


