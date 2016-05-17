//
//  main.cpp
//  HuffmanEncoded
//
//  Created by Bill Hu on 16/5/17.
//  Copyright © 2016年 Bill Hu. All rights reserved.
//

#include <iostream>
#include "HuffmanEncodedTree.hpp"
#include "HTNode.hpp"
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    vector<HTNode> trees;
    trees.push_back(HTNode(0));
    auto a = trees[0];
    trees.erase(trees.begin());
    cout << a.weight;
    cout << &a;
    return 0;
}
