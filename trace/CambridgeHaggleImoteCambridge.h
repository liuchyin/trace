//
//  CambridgeHaggleImoteCambridge.h
//  trace
//
//  Created by Cong on 13-3-6.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once

#include <fstream>
#include <iostream>
#include <list>
#include "Reader.h"
#include "constants.h"

using namespace std;

class CambridgeHaggleImoteCambridge : public Reader{
public:
    CambridgeHaggleImoteCambridge(){
        ifstream infile;
        infile.open("../../data-trace/Exp2/contacts.Exp2.dat");
        if(!infile){
            cout<<"CambridgeHaggleImoteCambridge infile error!"<<endl;
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
            
            nodes1.insert(node1);
            nodes2.insert(node2);
            
        }
        contacts.resize(cons.size());
        copy(cons.begin(), cons.end(), contacts.begin());
        
        CmpContact cmp;
        sort(contacts.begin(), contacts.end(), cmp);
        ofstream outfile;
         outfile.open("../../report/contact.txt");
         if(!outfile){
         cout<<"out contact error!"<<endl;
         return;
         }
         for(int i = 0; i != contacts.size(); i++)
         outfile<<contacts[i]->node1<<" "<<contacts[i]->node2<<endl;
         outfile.close();
         
    }
    
    string getName(){
        return "CambridgeHaggleImoteCambridge";
    }
};