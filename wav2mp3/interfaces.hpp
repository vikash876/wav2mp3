//
//  interfaces.hpp
//  wav2mp3
//
//  Created by Vikash jha on 13.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#ifndef interfaces_hpp
#define interfaces_hpp

#include <stdio.h>
#include <list>

class EncodLib {
public:
    virtual void encode(std::string path)=0;
};

class FileSys {
public:
    virtual std::list<std::string> getFileList(std::string directory)=0;
};

class Records {
private:
    std::list<std::string> jobNames;
    int totalJobs;
public:
    virtual int getTotalJobs()=0;
    virtual std::string getNextJob()=0;
};


class ThreadLib {
public:
    virtual void run(Records& r) = 0;
};

#endif /* interfaces_hpp */
