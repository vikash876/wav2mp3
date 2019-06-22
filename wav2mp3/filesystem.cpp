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

std::list<std::string> LinuxFileSys::getFileList(string dir) {
    
    DIR *dpdf;
    struct dirent *epdf;
    
    dpdf = opendir(dir.c_str());
    if (dpdf != NULL){
        while ((epdf = readdir(dpdf))!=0){
            string s = epdf->d_name;
            string extn = s.substr(s.rfind(".")+1);
            
            if(extn == "wav" || extn == "WAV")
                fileName.push_back(s);
        }
    }
    closedir(dpdf);
    return fileName;
}







