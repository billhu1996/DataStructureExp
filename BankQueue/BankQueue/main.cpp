//
//  main.cpp
//  BankQueue
//
//  Created by Bill Hu on 16/5/11.
//  Copyright © 2016年 Bill Hu. All rights reserved.
//

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "LobbyManager.h"
using namespace std;

int Window::count = 1;
int main(int argc, const char * argv[]) {
    int cashWindow, noneCashWindow,openingTime;
    cout << "请输入现金业务窗口数: ";
    cin >> cashWindow;
    cout << "请输入非现金业务窗口数: ";
    cin >> noneCashWindow;
    cout << "请输入营业总时间: ";
    cin >> openingTime;
    LobbyManager manager = LobbyManager(cashWindow, noneCashWindow);
    cout << "Start Time: " << time(NULL) << endl;
    manager.service(time(NULL) + openingTime);
    cout << "End Time: " << time(NULL) << endl;
    return 0;
}
