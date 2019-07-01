//
//  wavdecode.hpp
//  wav2mp3
//
//  Created by Vikash jha on 23.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#ifndef wavdecode_hpp
#define wavdecode_hpp

#include "interfaces.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>

typedef struct wav_header {
    /* Riff section */
    char riffID[4];
    int riffSize;
    char riffFormat[4];
    
    /* fmt section */
    char fmtID[4];
    int fmtSize;
    short audioFmt;
    short numChannels;
    int sampleRate;
    int byteRate;
    short blockAlign;
    short bitsPerSample;
    
    /* data section */
    char dataID[4];
    int dataSize;
}__attribute__((__packed__))  wav_header;

class WavDecode : public Decode {
    
    wav_header wv_hdr;
    std::vector<char> data;
public:
    WavDecode(FileSys *fs, std::string filePath);
    int getSampleRate();
    short getNumChannels();
    int getByteRate();
    char* getRawData();
    int getDataSize();
    short getFrameSize();
    short getBPS();
};


#endif /* wavdecode_hpp */
