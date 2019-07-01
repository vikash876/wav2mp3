//
//  encoder.hpp
//  wav2mp3
//
//  Created by Vikash jha on 13.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#ifndef encoder_hpp
#define encoder_hpp

#include <iostream>
#include "interfaces.hpp"
#include <lame.h>
#include "wavdecode.hpp"

class Mp3Encod : public EncodLib {
private:
    FileSys *fs;
    Logger *log;
    std::string encExtn;
    
    int encode_8bit_mono(WavDecode *wd, lame_t lame, int numSamples, unsigned char* mMp3Buffer, int mp3BufSize);
    int encode_16bit_mono(WavDecode *wd, lame_t lame, int numSamples, unsigned char* mMp3Buffer, int mp3BufSize);
    int encode_24bit_mono(WavDecode *wd, lame_t lame, int numSamples, unsigned char* mMp3Buffer, int mp3BufSize);
    int encode_32bit_mono(WavDecode *wd, lame_t lame, int numSamples, unsigned char* mMp3Buffer, int mp3BufSize);
    
public:
    void encode(std::string filePath);
    int getStdBRate(int brate);
    Mp3Encod(Logger& log, FileSys *fs, std::string extn) {this->log = &log; this->fs = fs; encExtn = extn;}
};

#endif /* encoder_hpp */
