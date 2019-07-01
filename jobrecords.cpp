//
//  jobrecords.cpp
//  wav2mp3
//
//  Created by Vikash jha on 14.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#include "jobrecords.hpp"

using namespace std;

JobRecords::JobRecords(list<string>& nameList, string path) {
    jobList = &nameList;
    jobIterator = jobList->begin();
    jobPath = path;
}

int JobRecords::getTotalJobs(){
    return (int)jobList->size();
}

std::string JobRecords::getNextJob() {
    string name = *jobIterator;
    if(jobIterator != jobList->end()) {
        jobIterator++;
        return jobPath+name;
    }
    else
        return "";
}
