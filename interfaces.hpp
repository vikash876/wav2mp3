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
#include <vector>
#include <string>

class Logger {
public:
    /* Display informational logs */
    virtual void LogInfo(std::string s) = 0;
    /* Display error logs */
    virtual void LogErr(std::string s) = 0;
};

class Decode {
private:
    std::vector<char> data;
};

class FileSys {
public:
    /* Get list of file with matching extensions */
    virtual void getFileListExtn(std::list<std::string>& fileList, std::string directory, std::string extn)=0;
    /* Read the file content into buffer */
    virtual void readFileCharacters(std::vector<char>& buffer, std::string filePath)=0;
    /* Write the buffer content into file */
    virtual void writeFileCharacters(char *buffer, std::string filePath, int size)=0;
    /* Append the buffer content into file */
    virtual void appendFileCharacters(char *buffer, std::string filePath, int size)=0;
    /* Change filePath's old extension (ex: .wav) to a new extension (ex: .mp3) */
    virtual void changeExtensionTo(std::string& filePath, std::string extn)=0;
    
};

class EncodLib {
public:
    /* Start the encoding process for a file store at path location */
    virtual void encode(std::string path)=0;
};

class Records {
private:
    /* Names of all the jobs */
    std::list<std::string> *jobList;
    /* Total number of jobs in jobList */
    int jobListSize;
public:
    virtual int getTotalJobs()=0;
    virtual std::string getNextJob()=0;
};


class ThreadLib {
public:
    virtual void run(Records& r) = 0;
};

#endif /* interfaces_hpp */
