//
//  wavdecode.cpp
//  wav2mp3
//
//  Created by Vikash jha on 23.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#include "wavdecode.hpp"

using namespace std;

WavDecode::WavDecode(FileSys *fs, string filePath) {
    fs->readFileCharacters(data, filePath);
    if(data.size()<sizeof(wav_header)) {
        throw "file format error: ";
    }
}

int WavDecode::getSampleRate() {
    wav_header *wav = (wav_header *)&data[0];
    return wav->sampleRate;
}

short WavDecode::getNumChannels() {
    wav_header *wav = (wav_header *)&data[0];
    return wav->numChannels;
}

int WavDecode::getByteRate() {
    wav_header *wav = (wav_header *)&data[0];
    return wav->byteRate;
}

int WavDecode::getDataSize() {
    wav_header *wav = (wav_header *)&data[0];
    return wav->dataSize;
}

short WavDecode::getBPS() {
    wav_header *wav = (wav_header *)&data[0];
    return wav->bitsPerSample;
}

short WavDecode::getFrameSize() {
    wav_header *wav = (wav_header *)&data[0];
    return wav->blockAlign;
}


char* WavDecode::getRawData() {
    return &data[0]+sizeof(wav_header);
}
