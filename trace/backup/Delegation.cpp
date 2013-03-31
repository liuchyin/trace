//
//  Sosim.cpp
//  trace
//
//  Created by Cong on 13-3-11.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#include "Delegation.h"
#include "clock.h"
/*Sosim::Statistics* Sosim::statistics;
Sosim::Statistics::Statistics(Reader& reader){


    readFeature(reader);
    readContact(reader);
    calculateVectors();
}


void Sosim::Statistics::readFeature(Reader& reader){
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

void Sosim::Statistics::readContact(Reader& reader){
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
    }
}




void Sosim::Statistics::calculateVectors(){
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

vector<double> Sosim::Statistics::vec(int _node, int _dest){
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
        if(encounter.position == dest.country)
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
    for(int i = 0; i != 6; i++)
        array[i] = count[i] / array[i];
    
    return array;
}

*/

void Delegation::connect(Node* node2){
    messageContainter::const_iterator end = messages.end();
    for(messageContainter::iterator iter = messages.begin();
        iter != end;)
    {
        thresMessage* message = (thresMessage*)iter->second;
        
        //discard outdated message
        if(clock::getTime() - message->common->creatingTime >= Message::TTL
           || message->common->deliveredTime != -1){
            delete iter->second;
            messages.erase(iter++);
            continue;
        }
        //encounter destination
        if(message->common->destination == node2->getID()){
            message->common->deliveredTime = clock::getTime();
            message->common->copies++;
            delete iter->second;
            messages.erase(iter++);
            //cout<<"delivered!"<<endl;
            continue;
        }
        
        
        
        if(!node2->messages.count(message->getID())){
            double newThres = predictor(node2->getID(), message->common->destination);
            if(newThres > message->threshold){
                message->threshold = newThres;
                thresMessage* newM = new thresMessage(message);
                node2->messages[newM->getID()] = newM;
            }
            ++iter;
            continue;
        }
        
        ++iter;
    }
}

Message* Delegation::createMessage(Common* common){
    thresMessage* newM = new thresMessage(common);
    newM->threshold = predictor(this->getID(), common->destination);
    return newM;
}






