//
//  Node.hpp
//  CampusNavigationSystem
//
//  Created by Bill Hu on 16/5/23.
//  Copyright © 2016年 Bill Hu. All rights reserved.
//

#ifndef Node_h
#include <vector>
#include <iostream>
#include <string>
#define Node_h

class Node {
public:
    static int count;
    int id;
    std::string name;
    std::string descripe;
    std::vector<double> weights;
    std::vector<Node*> nodes;
    
    Node(std::string name, std::string descripe) {
        this->id = count;
        count++;
        this->name = name;
        this->descripe = descripe;
    }
    
    void addPath(Node *node, double weight) {
        nodes.push_back(node);
        weights.push_back(weight);
    }
};

#endif /* Node_h */
