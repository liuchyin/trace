//
//  node.cpp
//  trace
//
//  Created by Cong on 13-3-6.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#include "node.h"
#include "extend.h"
Node::Statistic* Node::statistic;

Node::Statistic::Statistic(Reader& reader, int L) : L(L){
    
    startTime = reader.getMinTime();
    endTime = reader.getMaxTime();
    interval =  (endTime - startTime) / L;
    
    readFeature(reader);
    readContact(reader);
    calculateVectors();
}

void Node::Statistic::readFeature(Reader& reader){
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

void Node::Statistic::readContact(Reader& reader){
    typedef map<int, int> IntToInt;
    typedef map<int, IntToInt> Meetings;
    vector<Contact*>& contacts = reader.getContacts();
    for(int i = 0; i != contacts.size(); ++i){
        Contact* contact = contacts[i];
        int node1 = contact->node1;
        int node2 = contact->node2;
        if(!meetings.count(node1)){
            meetings.insert(Meetings::value_type(node1, map<int, int>()));
        }
        if(!meetings.count(node2)){
            meetings.insert(Meetings::value_type(node2, map<int, int>()));
        }
        
        IntToInt& map1 = meetings[node1];
        IntToInt& map2 = meetings[node2];
        map1[node2]++;
        map2[node1]++;
        
        totalMeetings[node1]++;
        
        totalMeetings[node2]++;
        
        typedef pair<int, int> intPair;
        intPair p(node1, node2);
        if(!contactTimes.count(p)){
            int* times = new int[L];
            for(int j = 0; j != L; ++j)
                times[j] = 0;
            contactTimes.insert(map<pair<int, int>, int*, compare>::value_type(p, times));
        }
        int* times = contactTimes.find(p)->second;
        times[getSlot(contact->start)]++;
    }
}




void Node::Statistic::calculateVectors(){
    vector<int> node;
    map<int, socialFeature>::const_iterator end = nodes.end();
    
    for(map<int, socialFeature>::iterator iter = nodes.begin();
        iter != end;
        ++iter)
        node.push_back(iter->first);
    
    for(int i = 0; i != node.size(); i++){
        for(int j = i + 1; j != node.size(); j++){
            vectors[pair<int, int>(node[i], node[j])] = vec(node[i], node[j]);
            vectors[pair<int, int>(node[j], node[i])] = vec(node[j], node[i]);
        }
    }
    
}

vector<double> Node::Statistic::vec(int _node, int _dest){
    vector<double> array;
    for(int i = 0; i != 6; i++){
        array.push_back(totalMeetings[_node]);
    }
    //socialFeature& node = nodes[_node];
    socialFeature& dest = nodes.find(_dest)->second;// _dest];
    
    int count[6] = {0};
    map<int, int>& nodeMeetings = meetings[_node];
    //map<int, int>& nodeMeetings = meetings.find(_node)->second;// [_node];
    
    
    map<int, int>::iterator end = nodeMeetings.end();
    
    for(map<int, int>::iterator iter = nodeMeetings.begin();
        iter != end;
        ++iter)
    {

        socialFeature& encounter = nodes.find(iter->first)->second; //[iter->first];
        
        
        if(encounter.city == dest.city)
            count[0] += iter->second;
        if(encounter.country == dest.country)
            count[1] += iter->second;
        if(encounter.position == dest.position)
            count[2] += iter->second;
        set<int>::iterator end = encounter.language.end();
        for(set<int>::iterator iter1 = encounter.language.begin();
            iter1 != end;
            ++iter1)
        {
            //cout<<*iter<<endl;
            //cout<<_node<<endl;
            if(dest.language.count(*iter1)){
                count[3] += iter->second;
                break;
            }
        }
        
        end = encounter.nationality.end();
        for(set<int>::iterator iter1 = encounter.nationality.begin();
            iter1 != end;
            ++iter1)
        {
            if(dest.nationality.count(*iter1)){
                count[4] += iter->second;
                break;
            }
        }
        
        end = encounter.affiliation.end();
        for(set<int>::iterator iter1 = encounter.affiliation.begin();
            iter1 != end;
            ++iter1)
        {
            if(dest.affiliation.count(*iter1)){
                count[5] += iter->second;
                break;
            }
        }
    }
    for(int i = 0; i != 6; i++){
        //cout<<count[i]<<" ";
        array[i] = count[i] / array[i];
    }
    //cout<<endl;
    return array;
}


int Node::Statistic::getSlot(long start){
    return int((start - startTime) / interval);
}


Node::Statistic::~Statistic(){
    typedef map<pair<int, int>, int*, compare> m;
    m::const_iterator end = contactTimes.end();
    for(m::iterator iter = contactTimes.begin(); iter != end; ++iter)
        delete iter->second;
}



void Node::Statistic::print(){
    ofstream outfile;
    /*outfile.open("../../report/contactTimes.txt");
    if(!outfile)
        cout<<"statistic report error!"<<endl;
    for(map<pair<int, int>, int*, compare>::iterator iter = contactTimes.begin();
        iter != contactTimes.end();
        ++iter){
        outfile<<iter->first.first<<" "<<iter->first.second<<endl;
        for(int i = 0; i != 100; ++i)
            outfile<<iter->second[i]<<" ";
        outfile<<endl;
    }
    outfile.close();
    outfile.open("../../report/meetings.txt");
    if(!outfile)
        cout<<"statistic report error!"<<endl;
    for(map<int, map<int, int>>::iterator iter = meetings.begin();
        iter != meetings.end();
        ++iter){
        outfile<<iter->first<<endl;
        for(map<int, int>::iterator it = iter->second.begin();
            it != iter->second.end();
            ++it){
            outfile<<it->first<<" "<<it->second<<endl;
        }
    }
    outfile.close();*/
    /*outfile.open("../../report/vectors.txt");
    if(!outfile)
        cout<<"statistic report error!"<<endl;
    for(map<pair<int, int>, vector<double>>::iterator iter = vectors.begin();
        iter != vectors.end();
        ++iter){
        outfile<<iter->first.first<<" "<<iter->first.second<<endl;
        for(int i = 0; i != 6; ++i)
            outfile<<iter->second[i]<<" ";
        outfile<<endl;
    }
    outfile.close();*/
    
    outfile.open("../../report/L.txt");
    if(!outfile)
        cout<<"statistic report error!"<<endl;
    for(map<pair<int, int>, int*>::iterator iter = Lv.begin();
        iter != Lv.end();
        ++iter)
    {
        Average<10> his;
        //Euclidean euc;
        //Tanimoto tan;
        outfile<<iter->first.first<<" "<<iter->first.second<<endl;
        for(int i = 0; i != 10; ++i)
            outfile<<iter->second[i]<<" ";
        outfile<<endl;
        for(int i = 0; i != 10; ++i)
            outfile<<his(iter->first.first, iter->second[i], iter->first.second)<<" ";
        outfile<<endl;
        //for(int i = 0; i != 10; ++i)
            //outfile<<his(iter->first.first, iter->second[i])<<" ";
        //outfile<<endl;
    }
    outfile.close();
    
    /*outfile.open("../../report/preTanimoto.txt");
    if(!outfile)
        cout<<"statistic report error!"<<endl;
    for(map<pair<int, int>, double>::iterator iter = predictor.begin();
        iter != predictor.end();
        ++iter)
    {
        outfile<<iter->first.first<<" "<<iter->first.second<<" "<<iter->second<<endl;
    }*/
    
}


Node::~Node(){
    messageContainter::const_iterator end = messages.end();
    for(messageContainter::iterator iter = messages.begin();
        iter != end;
        ++iter)
        delete iter->second;
}

Message* Node::createMessage(Common* common){
    return new Message(common);
}