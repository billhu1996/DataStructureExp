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
    
    HTNode(int weight) {
        parent = NULL;
        lChild = NULL;
        rChild = NULL;
        this->weight = weight;
    }
    HTNode(HTNode *lChild, HTNode *rChild) {
        parent = NULL;
        this->lChild = lChild;
        this->rChild = rChild;
        weight = lChild->weight = rChild->weight;
    }
};

#endif /* HTNode_h */
