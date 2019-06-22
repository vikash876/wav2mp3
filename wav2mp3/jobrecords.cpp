//
//  jobrecords.cpp
//  wav2mp3
//
//  Created by Vikash jha on 14.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#include "jobrecords.hpp"

using namespace std;

JobRecords::JobRecords(list<string> nameList, string path) {
    jobNames = nameList;
    totalJobs = (int)jobNames.size();
    jobIterator = jobNames.begin();
    jobPath = path;
}

std::string JobRecords::getNextJob() {
    string name = *jobIterator;
    if(jobIterator != jobNames.end()) {
        jobIterator++;
        return jobPath+name;
    }
    else
        return "";
}
