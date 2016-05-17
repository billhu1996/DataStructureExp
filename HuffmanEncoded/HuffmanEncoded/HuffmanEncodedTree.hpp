//
//  HuffmanEncodedTree.hpp
//  HuffmanEncoded
//
//  Created by Bill Hu on 16/5/17.
//  Copyright © 2016年 Bill Hu. All rights reserved.
//

#ifndef HuffmanEncodedTree_h
#include "HTNode.hpp"
#include <vector>
#include <string>
#define HuffmanEncodedTree_h

class HuffmanEncodedTree{
public:
    HTNode *firstNode;
    std::string dictionary;
    std::vector<int> weight;
    
    HuffmanEncodedTree(std::string dictionary, std::vector<int>weight) {
        this->dictionary = dictionary;
        this->weight = weight;
        firstNode = NULL;
    }
    bool createTree() {
        std::vector<HTNode> trees;
        if (weight.size() < dictionary.size()) {
            return false;
        }
        for (int i = 0; i<dictionary.size(); i++) {
            trees[i] = HTNode(weight[i]);
        }
        while (trees.size() > 1) {
            auto minIndex = trees.begin();
            HTNode *node1;
            HTNode *node2;
            for (auto i = trees.begin(); i!=trees.end(); i++) {
                if (trees[minIndex-trees.begin()].weight > trees[i-trees.begin()].weight) {
                    minIndex = i;
                }
            }
            node1 = &trees[minIndex-trees.begin()];
            trees.erase(minIndex);
            
            minIndex = trees.begin();
            for (auto i = trees.begin(); i!=trees.end(); i++) {
                if (trees[minIndex-trees.begin()].weight > trees[i-trees.begin()].weight) {
                    minIndex = i;
                }
            }
            node2 = &trees[minIndex-trees.begin()];
            trees.erase(minIndex);
            trees.push_back(HTNode(node1, node2));
        }
        return true;
    }
};

#endif /* HuffmanEncodedTree_h */
