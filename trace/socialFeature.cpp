//
//  socialFeature.cpp
//  trace
//
//  Created by Cong on 13-3-6.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#include "socialFeature.h"



char* socialFeature::split(char* str){
    while(*str != '=')
        str++;
    return str + 1;
}

int socialFeature::getNumber(char* str){
    if(*str == 0){
        cout<<"invalid feature1"<<endl;

        return -1;
    }
    char* p2 = str;
    while(*p2 != 0)
        p2++;
    int num = *(p2 - 1) - '0';
    if(p2 - str == 2)
        num += (*str - '0') * 10;
    return num;
}

vector<int> socialFeature::getNumbers(char* str){
    vector<int> numbers;
    if(*str == 0){
        cout<<"invalid feature2"<<endl;
        numbers.push_back(-1);
        return numbers;
    }
    char* p1 = str;
    char* p2 = str;

    while(*p2 != 0){
        if(*p2 == ','){
            int num = *(p2 - 1) - '0';
            if(p2 - p1 == 2)
                num += (*p1 - '0') * 10;
            numbers.push_back(num);
            p1 = p2 + 1;
        }
        p2++;
    }
    
    int num = *(p2 - 1) - '0';
    if(p2 - p1 == 2)
        num += (*p1 - '0') * 10;
    numbers.push_back(num);
    
    return numbers;
}

void socialFeature::print(){
    cout<<"city: "<<city<<endl;

    cout<<"country: "<<country<<endl;
    cout<<"position: "<<position<<endl;
    
    cout<<"nationality: ";
   set<int>::iterator end = nationality.end();
    for(set<int>::iterator iter = nationality.begin();
        iter != end;
        ++iter)
        cout<<*iter<<" ";
    cout<<endl;
    
    cout<<"language: ";
    end = language.end();
    for(set<int>::iterator iter = language.begin();
        iter != end;
        ++iter)
        cout<<*iter<<" ";
    cout<<endl;
    
    cout<<"affiliation: ";
     end = affiliation.end();
    for(set<int>::iterator iter = affiliation.begin();
        iter != end;
        ++iter)
        cout<<*iter<<" ";
    cout<<endl;
 
}