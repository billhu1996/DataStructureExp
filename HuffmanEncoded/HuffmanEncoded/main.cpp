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
vector<string> testCode = {"aabbcaa","eedeec"};

int main(int argc, const char * argv[]) {
    cout << "是否要输入数据?Y/N:";
    string edit;
    cin >> edit;
    if (edit == "Y") {
        weight.clear();
        testCode.clear();
        cout << "数据量n:";
        int n;
        int temp;
        cin >> n;
        cout << "请输入weight数组:";
        for (int i = 0; i<n; i++) {
            cin >> temp;
            weight.push_back(temp);
        }
        cout << "请输入字典:";
        cin >> dic;
        cout << "请输入测试数据:";
        for (int i = 0; i<n; i++) {
            cin >> edit;
            testCode.push_back(edit);
        }
    }
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
