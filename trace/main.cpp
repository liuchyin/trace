//
//  main.cpp
//  trace
//
//  Created by Cong on 13-3-6.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#include <iostream>
#include "report.h"
#include "SprayandFocus.h"
//#include "Social.h"
//#include "Sosim.h"
#include "Epidemic.h"
#include "IndiGroup.h"
#include "extend.h"
#include "SocialSim.h"
#include "wait.h"
#include "newPredictor.h"

#include "infocom06.h"
#include "CambridgeHaggleImoteCambridge.h"
using namespace std;

class Sim : public Simulator{
private:
    vector<Node*>& createNodes(int id){
        vector<Node*>* nodes = new vector<Node*>;
        //nodes->push_back(new Wait(id));
        //nodes->push_back(new Epidemic(id));
        nodes->push_back(new IndiGroupDel<Euclidean, Average<10>>(id));
        //nodes->push_back(new IndiGroupDel<Euclidean, Average<10>>(id));
        //nodes->push_back(new SimpleSpray<Euclidean, Average<10>>(id));
        //nodes->push_back(new SimpleDel<Euclidean, Average<10>>(id));
        //nodes->push_back(new EnhancedSpray<Euclidean, Average<10>>(id));
        //nodes->push_back(new EnhancedDel<Euclidean, Average<10>>(id));
        

        //nodes->push_back(new extendDel<Average<10>>(id));
        //nodes->push_back(new SosimDel<Euclidean>(id));
        //nodes->push_back(new extendDel<Average<10>>(id));
        //nodes->push_back(new extendSpray<Average<10>>(id));
        //nodes->push_back(new SosimDel<Euclidean>(id));
        //nodes->push_back(new SosimSpray<Euclidean>(id));

        //nodes->push_back(new SourceSprayFocus(id));
        return *nodes;
    }
public:
    ~Sim(){}
};



int main(int argc, const char * argv[])
{
    Sim sim;
    srand(4);
    //CambridgeHaggleImoteCambridge reader;
    socialFeatureInfocom06 reader;
    //Node::statistic = new Node::Statistic(reader, 100);
    //    
    //Report report(5000, 1);
    //report.runSimulator(reader, sim);
   // Node::statistic->print();

    return 0;
}

