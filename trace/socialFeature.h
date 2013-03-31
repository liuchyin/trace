//
//  socialFeature.h
//  trace
//
//  Created by Cong on 13-3-6.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once

//#include "node.h"
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class socialFeature{
public:
    socialFeature(int id){
        string pre = "../../data-trace/Exp6/forms/";
        string tail = ".dat";
        string path = pre + char(id / 10 + '0') + char(id % 10 + '0') + tail;
        ifstream infile;
        infile.open(path);
        if(!infile){
            cout<<"node "<<id<<" feature infile error"<<endl;
            return;
        }
        char feature[100];
        infile>>feature;
        infile>>feature;
        //nationality
        infile>>feature;
        //cout<<id<<endl;
        vector<int> nums = getNumbers(split(feature));
        for(int i = 0; i != nums.size(); i++)
            nationality.insert(nums[i]);
        infile>>feature;
        //languages
        infile>>feature;
        nums = getNumbers(split(feature));
        for(int i = 0; i != nums.size(); i++)
            language.insert(nums[i]);
        
        //affiliation
        infile>>feature;
        nums = getNumbers(split(feature));
        for(int i = 0; i != nums.size(); i++)
            affiliation.insert(nums[i]);
        
        //position
        infile>>feature;
        position = getNumber(split(feature));
        
        //city
        
        infile>>feature;
        city = getNumber(split(feature));
        
        infile>>feature;
        //country
        country = getNumber(split(feature));

        infile.close();
        //cout<<city<<endl;
        //print();
    }
public:
    
    int city;
    int country;
    int position;
    set<int> language;
    set<int> nationality;
    set<int> affiliation;

public:
    void print();
    
private:
    char* split(char* str);
    vector<int> getNumbers(char* str);
    int getNumber(char* str);
};