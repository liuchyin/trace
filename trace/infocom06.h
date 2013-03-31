//
//  infocom06.h
//  trace
//
//  Created by Cong on 13-3-7.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once


#include "reader.h"
#include "constants.h"
#include <fstream>
#include <list>
#include <iostream>
using namespace std;

class socialFeatureInfocom06 : public Reader{
public:
    socialFeatureInfocom06(){
        //process nodes
        ifstream nodeFile("../../data-trace/Exp6/nodes.txt");
        if(!nodeFile){
            cout<<"nodeFile error!"<<endl;
            return;
        }
        istream_iterator<int> dataBegin(nodeFile);
        istream_iterator<int> dataEnd;
        list<int> data(dataBegin, dataEnd);

        list<int>::const_iterator end1 = data.end();
        for(list<int>::iterator iter = data.begin();
            iter != end1;
            ++iter){
            nodes1.insert(*iter);
            nodes2.insert(*iter);
        }
        //cout<<nodes1.size()<<endl;
        nodeFile.close();
        
        //process contacts
        ifstream infile;
        infile.open("../../data-trace/Exp6/contacts.Exp6.dat");
        if(!infile){
            cout<<"infile error!"<<endl;
            return;
        }
        list<Contact*> cons;
        minTime = LONG_MAX;
        maxTime = 0;
        int node1, node2, start, end, temp1, temp2;
        
        while(true){
            infile>>node1;
            if(node1 == -1)
                break;
            infile>>node2>>start>>end>>temp1>>temp2;
            if(!nodes1.count(node1) || !nodes1.count(node2))
                continue;
            Contact* contact = new Contact();
            contact->node1 = node1;
            contact->node2 = node2;
            contact->start = start * SECOND;
            contact->duration = (end - start + 1) * SECOND;
            if(minTime > contact->start)
                minTime = contact->start;
            if(maxTime < contact->start + contact->duration)
                maxTime = contact->start + contact->duration;
            
            cons.push_back(contact);
            /*Contact* contact1 = new Contact();
            contact1->node1 = node2;
            contact1->node2 = node1;
            contact1->start = contact->start;
            contact1->duration = contact->duration;
            cons.push_back(contact1);*/
        }
        //cout<<cons.size()<<endl;
        
        contacts.resize(cons.size());
        copy(cons.begin(), cons.end(), contacts.begin());
        
        CmpContact cmp;
        sort(contacts.begin(), contacts.end(), cmp);
        //cout<<nodes1.size()<<endl;
        cout<<contacts.size()<<endl;
        //cout<<(maxTime - minTime) / SECOND<<endl;
        /*ofstream outfile;
        outfile.open("../../report/contact.txt");
        if(!outfile){
            cout<<"out contact error!"<<endl;
            return;
        }
        for(int i = 0; i != contacts.size(); i++)
            outfile<<contacts[i]->node1<<" "<<contacts[i]->node2<<endl;
        outfile.close();*/

    }

    string getName(){
        return "infocom06";
    }
};