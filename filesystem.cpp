//
//  filesystem.cpp
//  wav2mp3
//
//  Created by Vikash jha on 13.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#include "filesystem.hpp"
#include <dirent.h>

using namespace std;


inline bool caseInsCharCompareN(char a, char b) {
    return(toupper(a) == toupper(b));
}

bool caseInsCompare(const string& s1, const string& s2) {
    return((s1.size() == s2.size()) &&
           equal(s1.begin(), s1.end(), s2.begin(), caseInsCharCompareN));
}

void LinuxFileSys::getFileListExtn(list<string>& fileList, string dir, string extn) {
    
    DIR *dpdf;
    struct dirent *epdf;
    
    dpdf = opendir(dir.c_str());
    if (dpdf != NULL){
        while ((epdf = readdir(dpdf))!=0){
            string s = epdf->d_name;
            string file_extn = s.substr(s.rfind(".")+1);
            
            if(caseInsCompare(file_extn, extn))
                fileList.push_back(s);
        }
    }
    closedir(dpdf);
}



void LinuxFileSys::readFileCharacters(vector<char>& buffer, string filePath) {
    std::ifstream file;
    file.open(filePath.c_str(), std::ios::in | std::ios::binary);
    if(!file)
        log->LogErr("could not open the file " + filePath);
    file.seekg(0, std::ios::end);
    int size = (int)file.tellg();  // TODO try-catch?
    try {
        buffer.resize(size);
    } catch(...) {
        log->LogErr("buffer allocation failed");
    }
    char *fStream = &buffer[0];
    file.seekg(0, std::ios::beg);
    file.read(fStream, size);
    file.close();
}

void LinuxFileSys::writeFileCharacters(char *buffer, string filePath, int size) {
    std::ofstream       mMp3File;
    // Create/open output mp3 file
    mMp3File.open(filePath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
    if( ! mMp3File.is_open() )
    {
        log->LogErr("ERROR opening mp3 file " + filePath + " for writing");
    }
    else
    {
        // Write mp3 buffer in the file
        mMp3File.write(&buffer[0], size);
        mMp3File.close();
        mMp3File.clear();
    }
}

void LinuxFileSys::appendFileCharacters(char *buffer, string filePath, int size) {
    std::ofstream       mMp3File;
    // Create/open output mp3 file
    mMp3File.open(filePath.c_str(), std::ios::out | std::ios::app | std::ios::binary);
    if( ! mMp3File.is_open() )
    {
        log->LogErr("ERROR opening mp3 file " + filePath + " for writing");
    }
    else
    {
        // Write mp3 buffer in the file
        mMp3File.write(&buffer[0], size);
        mMp3File.close();
        mMp3File.clear();
    }
}

void LinuxFileSys::changeExtensionTo(string& filePath, string extn) {
    string old_extn;
    size_t pos = filePath.rfind('.');
    if (pos != std::string::npos) {
        // return the substring
        old_extn = filePath.substr(pos+1);
    }
    string::size_type i = filePath.find(old_extn);
    filePath.erase(i, old_extn.size());
    filePath += extn;
}









