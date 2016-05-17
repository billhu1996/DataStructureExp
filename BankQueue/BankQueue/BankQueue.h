//
//  Queue.h
//  BankQueue
//
//  Created by Bill Hu on 16/5/11.
//  Copyright © 2016年 Bill Hu. All rights reserved.
//

#ifndef Queue_h
#define Queue_h
#include <time.h>
#include "RandomTime.h"
#endif /* Queue_h */

typedef struct QueueN {
    time_t ArrivalTime;
    int Duration;
    struct QueueN *next;
} QueueN, *Queueptr;

class Queue {
public:
    Queueptr first = NULL;
    Queueptr last = NULL;
    int count = 0;
    
public:
    bool add() {
        QueueN *node = new QueueN;
        node->ArrivalTime = time(NULL);
        node->Duration = RandomTime::randomTime();
        node->next = NULL;
        if (count == 0) {
            first = node;
            last = node;
        } else {
            last->next = node;
            last = node;
        }
        count++;
        return true;
    };
    bool remove() {
        if (count <= 0) {
            return false;
        } else {
            count--;
            Queueptr cur = first;
            first = first->next;
            delete(cur);
            return true;
        }
    }
};
