//
//  threads.hpp
//  wav2mp3
//
//  Created by Vikash jha on 13.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//


#ifndef threads_hpp
#define threads_hpp

#include <iostream>
#include "interfaces.hpp"
#include <pthread.h>
#include "logger.hpp"


class PThreadLib: public ThreadLib {
private:
    pthread_t       *my_thread;
    int             poolSize;
    std::string     tdata;
    pthread_mutex_t lock;
    Logger *log;
public:
    void *workFunc;
    void run(Records& r);
    std::string getTdata() {return tdata;}
    PThreadLib(Logger& log, EncodLib *e, int poolSize);
    ~PThreadLib();
    static void* workert(void *);
};

#endif /* threads_hpp */
