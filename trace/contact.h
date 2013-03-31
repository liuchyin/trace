//
//  contact.h
//  trace
//
//  Created by Cong on 13-3-6.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once

class Contact{
public:
    long start;
    long duration;
    int node1;
    int node2;
};


class CmpContact{
public:
    inline bool operator()(Contact* c1, Contact* c2){
        return c1->start < c2->start;
    }
};


