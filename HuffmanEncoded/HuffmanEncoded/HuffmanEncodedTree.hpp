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
    std::vector<int> weights;
    std::vector<HTNode*> leafs;
    std::vector<HTNode*> trees;
    
    HuffmanEncodedTree(std::string dictionary, std::vector<int>weights) {
        this->dictionary = dictionary;
        this->weights = weights;
        firstNode = NULL;
        createTree();
        createEncodedDictionary();
    }
    bool createTree() {
        if (weights.size() < dictionary.size()) {
            return false;
        }
        for (int i = 0; i<dictionary.size(); i++) {
            trees.push_back(new HTNode(weights[i], dictionary[i]));
//            leafs.push_back(&trees[i]);
        }
        while (trees.size() > 1) {
            auto minIndex = trees.begin();
            HTNode *node1;
            HTNode *node2;
            for (auto i = trees.begin(); i!=trees.end(); i++) {
                if (trees[minIndex-trees.begin()]->weight > trees[i-trees.begin()]->weight) {
                    minIndex = i;
                }
            }
            node1 = trees[minIndex-trees.begin()];
            if (node1->lChild == NULL) {
                leafs.push_back(node1);
            }
            trees.erase(minIndex);
            
            minIndex = trees.begin();
            for (auto i = trees.begin(); i!=trees.end(); i++) {
                if (trees[minIndex-trees.begin()]->weight > trees[i-trees.begin()]->weight) {
                    minIndex = i;
                }
            }
            node2 = trees[minIndex-trees.begin()];
            if (node2->lChild == NULL) {
                leafs.push_back(node2);
            }
            trees.erase(minIndex);
            trees.push_back(new HTNode(node1, node2));
        }
        firstNode = trees[0];
        return true;
    }
    
    bool createEncodedDictionary() {
        for (auto i = leafs.begin(); i!=leafs.end(); i++) {
            auto node = leafs[i-leafs.begin()];
            std::string tempString;
            std::string returnString;
            while (node != firstNode) {
                if (node->parent->lChild == node) {
                    tempString += "0";
                    node = node->parent;
                } else if (node->parent->rChild == node) {
                    tempString += "1";
                    node = node->parent;
                } else {
                    return false;
                }
            }
            for (int i = int(tempString.size()); i>0; i--) {
                returnString += tempString[i-1];
            }
            leafs[i - leafs.begin()]->encode = returnString;
        }
        return true;
    }
    
    std::string encode(std::string inString) {
        std::string returnString;
        for (int i = 0; i<inString.size(); i++) {
            for (int j = 0; j<leafs.size(); j++) {
                if (inString[i] == leafs[j]->code) {
                    returnString += leafs[j]->encode;
                    break;
                }
            }
        }
        return returnString;
    }
    
    std::string unEncode(std::string inString) {
        std::string returnString;
        while (inString.size() > 0) {
            for (int i = 0; i<leafs.size(); i++) {
                int j = 0;
                for (; j<leafs[i]->encode.size() && j < inString.size(); j++) {
                    if (leafs[i]->encode[j] != inString[j]) {
                        break;
                    }
                }
                if (j > inString.size()) {
                    return "";
                } else if (j == leafs[i]->encode.size()) {
                    returnString += leafs[i]->code;
                    inString.erase(0, leafs[i]->encode.size());
//                    for (int k = 0; k<leafs[i]->encode.size(); k++) {
//                        returnString.erase(returnString.begin());
//                    }
                    break;
                }
            }
        }
        return returnString;
    }
};

#endif /* HuffmanEncodedTree_h */
