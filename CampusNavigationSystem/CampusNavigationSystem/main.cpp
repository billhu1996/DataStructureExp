//
//  main.cpp
//  CampusNavigationSystem
//
//  Created by Bill Hu on 16/5/23.
//  Copyright © 2016年 Bill Hu. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Node.hpp"
#include "Navigation.hpp"
using namespace std;

int Node::count = 0;
vector<string> nodes;
vector<int> curNode;
vector<double> path;
vector<int> withNodes;
Navigation *nav = new Navigation();

void findPath() {
    int n1,n2;
    cout << "请输入要查询的始 末节点\n";
    cin >> n1 >> n2;
    nav->findPath(nav->nodes[n1], nav->nodes[n2]);
}

void addTestData() {
    for (int i = 0; i<nodes.size(); i++) {
        nav->addNode(new Node(nodes[i], nodes[i]));
    }
    for (int i = 0; i<path.size(); i++) {
        nav->addPath(nav->nodes[curNode[i]], nav->nodes[withNodes[i]], path[i]);
    }
}

void addPath(int cur,double pa, int with) {
    curNode.push_back(cur);
    path.push_back(pa);
    withNodes.push_back(with);
}

int main(int argc, const char * argv[]) {
    for (int i = 0; i<10; i++) {
        char a[2];
        a[0] = 'a' + i;
        a[1] = '\0';
        nodes.push_back(&a[0]);
    }
    addPath(0,2,1);
    addPath(0,1,2);
    addPath(0,2,3);
    addPath(1,2,4);
    addPath(1,2,5);
    addPath(1,1,2);
    addPath(2,2,5);
    addPath(2,1,3);
    addPath(3,3,5);
    addPath(3,3,6);
    addPath(3,5,8);
    addPath(4,1,7);
    addPath(4,1,5);
    addPath(5,1,7);
    addPath(6,2,7);
    addPath(7,1,9);
    addPath(7,1,8);
    addPath(8,1,9);
    
    while (1) {
        int n;
        cout << "请选择\n1.加载测试数据\n2.手动输入数据(v0 距离 v1)\n3.找路\n4.周游(大门)\n0.退出\n";
        cin >> n;
        switch (n) {
            case 0:
                return 0;
            case 1:
                addTestData();
                break;
            case 2:
                int a,b;
                double c;
                cin >> a >> c >> b;
                addPath(a,c,b);
                break;
            case 3:
                findPath();
                break;
            case 4:
                cin >>a;
                nav->traval(nav->nodes[a]);
            default:
                break;
        }
    }
    return 0;
}

