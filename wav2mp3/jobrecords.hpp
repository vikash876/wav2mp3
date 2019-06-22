//
//  jobrecords.hpp
//  wav2mp3
//
//  Created by Vikash jha on 14.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#ifndef jobrecords_hpp
#define jobrecords_hpp

#include <iostream>
#include "interfaces.hpp"

#endif /* jobrecords_hpp */

class JobRecords : public Records {
private:
    std::list<std::string> jobNames;
    int totalJobs;
    std::string jobPath;
    std::list<std::string>::iterator jobIterator;
public:
    std::string getNextJob();
    int getTotalJobs() {
        return totalJobs;
    }
    JobRecords(std::list<std::string> nameList, std::string jobPath);
};
