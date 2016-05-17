//
//  RandomTime.h
//  BankQueue
//
//  Created by Bill Hu on 16/5/11.
//  Copyright © 2016年 Bill Hu. All rights reserved.
//

#ifndef RandomTime_h
#define RandomTime_h

class RandomTime {
public:
    static int randomTime() {
        return random()%15;
    }
};

#endif /* RandomTime_h */
