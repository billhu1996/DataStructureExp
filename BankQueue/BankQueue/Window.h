//
//  Window.h
//  BankQueue
//
//  Created by Bill Hu on 16/5/11.
//  Copyright © 2016年 Bill Hu. All rights reserved.
//

#ifndef Window_h
#define Window_h
#include <iostream>
#include <unistd.h>
#include "BankQueue.h"
#endif /* Window_h */

class Window {
public:
    static int count;
    Window() {
        windowNumber = count;
        count++;
    }
//    std::weak_ptr<LobbyManager> *delegate = NULL;
    time_t available = 0;
    int windowNumber;
    void service(time_t time) {
        std::cout << "窗口" << windowNumber << "正在办理业务"<<std::endl;
        available = time;
    }
};
