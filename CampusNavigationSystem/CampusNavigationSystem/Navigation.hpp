//
//  Navigation.hpp
//  CampusNavigationSystem
//
//  Created by Bill Hu on 16/5/23.
//  Copyright © 2016年 Bill Hu. All rights reserved.
//

#ifndef Navigation_h
#include <vector>
#include <iostream>
#include <string>
#include "Node.hpp"
#define Navigation_h

class Navigation {
    
public:
    std::vector<Node*> nodes;
    void addNode(Node *node) {
        nodes.push_back(node);
    }
    
    void addPath(Node *node1, Node *node2, double weight) {
        node1->addPath(node2, weight);
        node2->addPath(node1, weight);
    }
    
    void findPath(Node *node1, Node *node2) {//, void check(std::vector<Node*>)
        double dis = _findPath(node1, node2);
        std::cout<<std::endl<<"short distance: "<<dis<<std::endl;
    }
    
    void traval(Node* gate) {
        auto tempNode = gate;
        std::vector<bool> isVisited;
        std::vector<Node*> path;
        for (int i = 0; i<nodes.size(); i++) {
            isVisited.push_back(false);
        }
        for (int j = 0; j<nodes.size(); j++) {
            for (int i = 0;i<tempNode->nodes.size();i++) {
                if (!isVisited[tempNode->nodes[i]->id]) {
                    path.push_back(tempNode->nodes[i]);
                    isVisited[tempNode->id] = true;
                    tempNode = tempNode->nodes[i];
                    continue;
                }
            }
        }
        if (tempNode != gate) {
            _findPath(tempNode, gate);
            path.pop_back();
            std::cout<<"<--";
        }
        for (; path.size()!=0; ) {
            std::cout<<path.back()->name<<"<--";
            path.pop_back();
        }
        std::cout<<gate->name<<std::endl;
    }
private:
    double _findPath(Node *node1, Node *node2) {
        Node* tempNode = node1;
        std::vector<double> shortDistance;
        std::vector<bool> isVisited;
        std::vector<Node*> willVisit1;
        std::vector<Node*> willVisit2;
        std::vector<Node*> preNodes;
        for (int i = 0; i<nodes.size(); i++) {
            shortDistance.push_back(0x7fffffff);
            preNodes.push_back(NULL);
            isVisited.push_back(0);
        }
        shortDistance[node1->id] = 0;
        isVisited[node1->id] = 1;
        preNodes[node1->id] = node1;
        for (int i = 0; i<tempNode->nodes.size(); i++) {
            int j = tempNode->nodes[i]->id;
            shortDistance[j] = tempNode->weights[i];
            preNodes[j] = tempNode;
            willVisit1.push_back(tempNode->nodes[i]);
            isVisited[tempNode->id] = 1;
        }
        for (; willVisit1.size()!=0 ;) {
            bool alsoBreak = false;
            while (isVisited[willVisit1.back()->id]) {
                willVisit1.pop_back();
                if (willVisit1.size() ==  0) {
                    willVisit1 = willVisit2;
                    if (willVisit1.size()==0) {
                        alsoBreak = true;
                    }
                    //                    std::cout << willVisit2.size();
                    willVisit2.clear();
                    //                    std::cout << willVisit1.size();
                    //                    std::cout << willVisit2.size()<<std::endl;
                    break;
                }
            }
            if (alsoBreak) {
                break;
            }
            tempNode = willVisit1.back();
            for (int i = 0; i<tempNode->nodes.size(); i++) {
                if (!isVisited[tempNode->nodes[i]->id]) {
                    willVisit2.push_back(tempNode->nodes[i]);
                }
                //                std::cout << tempNode->weights[i] <<" "<< shortDistance[tempNode->id] <<" "<< shortDistance[tempNode->nodes[i]->id]<<std::endl;
                if (tempNode->weights[i] + shortDistance[tempNode->id] < shortDistance[tempNode->nodes[i]->id]) {
                    shortDistance[tempNode->nodes[i]->id] = tempNode->weights[i] + shortDistance[tempNode->id];
                    preNodes[tempNode->nodes[i]->id] = tempNode;
                }
            }
            isVisited[tempNode->id] = true;
            willVisit1.pop_back();
            if (willVisit1.size() ==  0) {
                willVisit1 = willVisit2;
                //                std::cout << willVisit2.size();
                willVisit2.clear();
                //                std::cout << willVisit1.size();
                //                std::cout << willVisit2.size()<<std::endl;
            }
        }
        auto preNode = node2;
        for (; preNode->id!=node1->id; ) {
            std::cout<<nodes[preNode->id]->name<<"<--";
            preNode = preNodes[preNode->id];
        }
        std::cout<<node1->name;
        return shortDistance[node2->id];
    }
};

#endif /* Navigation_h */
