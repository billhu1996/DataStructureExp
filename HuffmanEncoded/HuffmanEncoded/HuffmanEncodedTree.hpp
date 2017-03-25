//
//  HuffmanEncodedTree.hpp
//  HuffmanEncoded
//
//  Created by Bill Hu on 16/5/17.
//  Copyright © 2016年 Bill Hu. All rights reserved.
//

#ifndef HuffmanEncodedTree_h
#include "HTNode.hpp"
#include <math.h>
#include <iomanip>
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
        createTree();//建立霍夫曼树
        createEncodedDictionary();//建立编码字典
        fullNodeCountPosition();
    }
    bool createTree() {
        if (weights.size() < dictionary.size()) {
            return false;
        }
        for (int i = 0; i<dictionary.size(); i++) {
            HTNode *node = new HTNode(weights[i], dictionary[i]);
            trees.push_back(node);
            leafs.push_back(node);
        }
        while (trees.size() > 1) {
            auto minIndex = 0;
            HTNode *node1;
            HTNode *node2;
            for (auto i = 0; i!=trees.end()-trees.begin(); i++) {
                if (trees[minIndex]->weight > trees[i]->weight) {
                    minIndex = i;
                }
            }
            node1 = trees[minIndex];
            trees.erase(trees.begin() + minIndex);
            
            minIndex = 0;
            for (int i = 0; i!=trees.end() - trees.begin(); i++) {
                if (trees[minIndex]->weight > trees[i]->weight) {
                    minIndex = i;
                }
            }
            node2 = trees[minIndex];
            trees.erase(trees.begin() + minIndex);
            trees.push_back(new HTNode(node1, node2));
        }
        firstNode = trees[0];
        return true;
    }
    
    bool createEncodedDictionary() {
        for (auto i = 0; i<leafs.size(); i++) {
            auto node = leafs[i];
            std::string tempString;
            std::string returnString;
            while (node != firstNode) {
                if (node->parent->lChild == node) {
                    tempString += "0";
                    node = node->parent;
                } else {
                    tempString += "1";
                    node = node->parent;
                }
            }
            for (int i = int(tempString.size()); i>0; i--) {
                returnString += tempString[i-1];
            }
            leafs[i]->encode = returnString;
        }
        return true;
    }
    
    std::string encode(std::string inString) {//编码
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
    
    std::string unEncode(std::string inString) {//译码
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
                    break;
                }
            }
        }
        return returnString;
    }
    
    friend std::ostream &operator<<(std::ostream &cout, HuffmanEncodedTree &tree) {
        auto depth = tree.getDepth();
        std::vector<HTNode*> node;
        node.push_back(tree.firstNode);
        for (int j = 0; j<depth; j++) {
            for (int k = 0; k<node.size(); k++) {
                if (k != 0) {
                    node[k]->lengthWithPreNode = node[k]->positionX - node[k - 1]->positionX - 1;
                } else {
                    node[k]->lengthWithPreNode = node[k]->positionX;
                }
                for (int i = 0; i<node[k]->lengthWithPreNode; i++) {
                    cout << "   ";
                }
                if (node[k] != NULL) {
                    if (node[k]->weight == 0) {
                        cout << "  ";
                    } else {
                        cout << std::setw(2) << node[k]->weight;
                    }
                    cout << std::setw(1) << node[k]->code;
                } else {
                    cout << "   ";
                }
            }
            cout << std::endl;
            std::vector<HTNode*> temp;
            for (int k = 0; k<node.size(); k++) {
                temp.push_back(node[k]->lChild);
                temp.push_back(node[k]->rChild);
            }
            node = temp;
        }
        return cout;
    }
    
    unsigned long getDepth() {
        return _getDepth(firstNode);
    }
    
    void fullNodeCountPosition() {
        unsigned long depth = getDepth();
        std::vector<HTNode*> node;
        node.push_back(firstNode);
        for (int i = 0; i < depth - 1; i++) {
            std::vector<HTNode*> temp;
            for (int k = 0; k < node.size(); k++) {
                if (node[k]->lChild == NULL) {
                    node[k]->lChild = new HTNode(node[k]);
                    node[k]->rChild = new HTNode(node[k]);
                }
                temp.push_back(node[k]->lChild);
                temp.push_back(node[k]->rChild);
            }
            node = temp;
        }
        std::vector<HTNode*> temp;
        for (int j = int(depth - 1); j >= 0; j--) {
            for (int i = 0; i < node.size(); i++) {
                if (j == depth - 1) {
                    node[i]->positionX = 2 * i;
                } else {
                    node[i]->positionX = (node[i]->lChild->positionX + node[i]->rChild->positionX) / 2;
                }
                if (i % 2 == 1) {
                    temp.push_back(node[i]->parent);
                }
            }
            node = temp;
            temp.clear();
        }
    }
    
    void preOrderRecursiveTraverse(void visit(HTNode &), HTNode *node) {
        if (node == NULL) {
            return;
        }
        visit(*node);
        preOrderRecursiveTraverse(visit, node->lChild);
        preOrderRecursiveTraverse(visit, node->rChild);
    }
private:
    
    unsigned long _getDepth(HTNode *node) {
        if (node == NULL) {
            return 0;
        }
        unsigned long leftDepth = _getDepth(node->lChild);
        unsigned long rightDepth = _getDepth(node->rChild);
        return ((leftDepth > rightDepth) ? leftDepth : rightDepth) + 1;
    }
};

#endif /* HuffmanEncodedTree_h */
