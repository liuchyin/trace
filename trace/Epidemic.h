//
//  Epidemic.h
//  trace
//
//  Created by Cong on 13-3-10.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//


#include <iostream>
#include "node.h"

class Epidemic : public Node{
public:
    Epidemic(int id) : Node(id){}
    void connect(Node* node2);
    ~Epidemic(){};
};
