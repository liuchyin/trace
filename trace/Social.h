//
//  Social.h
//  trace
//
//  Created by Cong on 13-3-10.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#pragma once

#include "socialFeature.h"
#include "SprayandFocus.h"
#include "reader.h"

class Social : public SourceSprayFocus{
public:
    class Statistics{
    public:
        map<int, socialFeature> nodes;
        Statistics(Reader& reader);
    };
    
    
    static Statistics* statistics;
    
    Social(int id): SourceSprayFocus(id){}
    ~Social(){}
    
protected:
    bool compare(int node2, int dest);


private:
    int getValue(int node1, int node2);
    bool simility(set<int>& set1, set<int>& set2);
};


/*    
*/