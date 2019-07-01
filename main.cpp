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
#include "logger.hpp"
#include <vector>

#define song_dir "/Users/vikashjha/Music/songs/"  /* Directory for WAV files */
#define old_type "wav" /* extension before conversion (upper or lower case) */
#define new_type "mp3" /* extention after conversion */

using namespace std;

int main(int argc, const char * argv[]) {
    
    /* Initialize the log system */
     ConsoleLogger log;
    /* initialize the filesystem */
    FileSys *fs = new LinuxFileSys(log);

    /* get the list of all file with matching extension (old_type) */
    list<string> wavList;
    fs->getFileListExtn(wavList, song_dir, old_type);
    
    if(wavList.size()==0)
        log.LogErr(old_type " files not found!");
    else
        log.LogInfo(old_type " files found!!");
    
    /* Initialite the Jobrecords for record management */
    JobRecords jr = JobRecords(wavList, song_dir);

    /* Initialize the encoder */
    EncodLib *elib = new Mp3Encod(log, fs, new_type);
    
    /* Initialize the thread library */
    PThreadLib *th = new PThreadLib(log, elib, jr.getTotalJobs());
    log.LogInfo("Lets convert.... ");
    /* start the conversion with threads */
    th->run(jr);
    log.LogInfo("All " old_type " files convered successfully to " new_type);
    /* Deinit the thread library */
    delete th;
    delete (Mp3Encod *)elib;
    return 0;
}
