//
//  LobbyManager.h
//  BankQueue
//
//  Created by Bill Hu on 16/5/11.
//  Copyright © 2016年 Bill Hu. All rights reserved.
//

#ifndef LobbyManager_h
#define LobbyManager_h
#include "Window.h"
#include <iostream>
#include <vector>
#endif /* LobbyManager_h */

const int CashService = 0;
const int NoneCashService = 1;
class LobbyManager {
private:
    std::vector<Window> cashWindows;
    std::vector<Window> noneCashWindows;
    Queue *cashQueue = new Queue();
    Queue *noneCashQueue = new Queue();
    int customerCount = 0;
    time_t nextArrivalTime = 0;
    time_t totalHandleTime = 0;
    void newCustomer() {
        if (nextArrivalTime > time(NULL)) {
            return;
        }
        if (time(NULL) > closeTime) {
            std::cout << "第" << customerCount+1 <<"位顾客" <<"很抱歉, 银行已经关门." << std::endl;
            return;
        }
        if (random()%1 == CashService) {
            cashQueue->add();
            customerCount++;
            int front = cashQueue->count > cashWindows.size() + noneCashWindows.size() ? cashQueue->count : cashQueue->count-1;
            std::cout << "欢迎第" << customerCount << "位顾客" << "前面还有" << front << "位顾客" << std::endl;
            nextArrivalTime = time(NULL) + 1;
        } else {
            noneCashQueue->add();
            customerCount++;
            int front = noneCashQueue->count >= cashWindows.size() + noneCashWindows.size() ? noneCashQueue->count : noneCashQueue->count-1;
            std::cout << "欢迎第" << customerCount <<"位顾客" << "前面还有" << front << "位顾客" << std::endl;
            nextArrivalTime = time(NULL) + 2;
        }
    }
    void serviceCustomer() {
        for (int i = 0; i<cashWindows.size(); i++) {
            if (cashWindows[i].available < time(NULL) && cashQueue->count > 0) {
                serviceCashCustomer(&cashWindows[i]);
                break;
            }
        }
        for (int i = 0; i<noneCashWindows.size(); i++) {
            if (cashWindows[i].available < time(NULL) && noneCashQueue->count > 0) {
                serviceNoneCashCustomer(&noneCashWindows[i]);
                break;
            }
        }
    }
    void serviceCashCustomer(Window *window) {
        time_t t = RandomTime::randomTime();
        totalHandleTime += t;
        window->service(t + time(NULL));
        cashQueue->remove();
    }
    void serviceNoneCashCustomer(Window *window) {
        time_t t = RandomTime::randomTime();
        totalHandleTime += t;
        window->service(t + time(NULL));
        noneCashQueue->remove();
    }
public:
    LobbyManager(int cashWindow, int noneCashWindow) {
        for (int i = 0; i<cashWindow; i++) {
            this->cashWindows.push_back(Window());
        }
        for (int i = 0; i<noneCashWindow; i++) {
            this->cashWindows.push_back(Window());
        }
    }
    time_t closeTime = NULL;
    void service(time_t closeTime) {
        this->closeTime = closeTime;
        while (closeTime >= time(NULL)) {
            serviceCustomer();
            newCustomer();
        }
        while(cashQueue->count > 0 || cashQueue->count > 0) {
            serviceCustomer();
        }
        std::cout << "所有顾客办理总时间:" << totalHandleTime << "分钟" <<std::endl;
        std::cout << "办理人数:" << customerCount <<std::endl;
        std::cout << "平均办理时间:" << totalHandleTime / customerCount << "分钟" <<std::endl;
    }
};
