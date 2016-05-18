//
//  HTNode.hpp
//  HuffmanEncoded
//
//  Created by Bill Hu on 16/5/17.
//  Copyright © 2016年 Bill Hu. All rights reserved.
//

#ifndef HTNode_h
#define HTNode_h

class HTNode {
public:
    int weight;
    HTNode *parent;
    HTNode *lChild;
    HTNode *rChild;
    char code = NULL;
    std::string encode;
    
    HTNode() {}
    HTNode(int weight, char code) {
        parent = NULL;
        lChild = NULL;
        rChild = NULL;
        this->weight = weight;
        this->code = code;
    }
    HTNode(HTNode *lChild, HTNode *rChild) {
        this->parent = NULL;
        this->lChild = lChild;
        this->rChild = rChild;
        lChild->parent = this;
        rChild->parent = this;
        this->weight = lChild->weight + rChild->weight;
    }
};

#endif /* HTNode_h */
