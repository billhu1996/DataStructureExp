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

vector<int> weight = {5,4,3,2,1};
string dic = "abcde";
string testCode[2] = {"aabbcaa","eedeec"};

int main(int argc, const char * argv[]) {
    HuffmanEncodedTree tree = HuffmanEncodedTree(dic, weight);
    for (int i = 0; i<2; i++) {
        string encoded = tree.encode(testCode[i]);
        string uncoded = tree.unEncode(encoded);
        cout << encoded << endl << uncoded << endl;
        cout << "----------------" << endl;
    }
    for (int i = 0; i<tree.leafs.size(); i++) {
        cout << tree.leafs[i]->code << ": " << tree.leafs[i]->encode << endl;
    }
    cout << "----------------" << endl;
    cout << tree;
    return 0;
}
