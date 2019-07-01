//
//  threads.cpp
//  wav2mp3
//
//  Created by Vikash jha on 13.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//



#include "threads.hpp"

using namespace std;

PThreadLib::PThreadLib(Logger& log, EncodLib *e, int poolSize) {
    this->log = &log;
    workFunc = e;
    this->poolSize = poolSize;
    my_thread = new pthread_t[poolSize];
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        this->log->LogErr("\n mutex init failed\n");
    }
}

PThreadLib::~PThreadLib() {
    delete my_thread;
}


void* PThreadLib::workert(void *arg) {
    
    PThreadLib *ref = (PThreadLib *)arg;
    EncodLib *encoder = (EncodLib *)ref->workFunc;
    string encodePath = ref->getTdata();
    //release the lock
    pthread_mutex_unlock((&ref->lock));
    encoder->encode(encodePath);
    
    return NULL;
}


void PThreadLib::run(Records& r) {
    for(int i=0; i<poolSize; i++) {
        //take a lock
        pthread_mutex_lock(&lock);
        tdata = r.getNextJob();
        int ret = pthread_create(&my_thread[i], NULL, PThreadLib::workert, this);
        if(ret != 0) {
            log->LogErr("Unable to create a thread");
            exit(EXIT_FAILURE);
        }
    }
    
    for(int i=0; i<poolSize; i++) {
        pthread_join(my_thread[i], NULL);
    }
}
