//
//  main.cpp
//  wav2mp3
//
//  Created by Vikash jha on 13.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#include <iostream>
#include "encoder.hpp"
#include "threads.hpp"
#include "filesystem.hpp"
#include "jobrecords.hpp"

#define SONG_DIR "/Users/vikashjha/Music/songs/"

using namespace std;

int main(int argc, const char * argv[]) {
    
    LinuxFileSys fs;
    list<string> myList = fs.getFileList(SONG_DIR);
    
    JobRecords r = JobRecords(myList, SONG_DIR);
    
    EncodLib *e = new Mp3Encod();
    
    PThreadLib *t = new PThreadLib(e, r.getTotalJobs());
    t->run(r);
    
    delete t;
    cout << "main exiting now...." << endl;
    return 0;
}
