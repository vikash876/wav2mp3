//
//  encoder.cpp
//  wav2mp3
//
//  Created by Vikash jha on 13.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#include "encoder.hpp"
#include <unistd.h>
#include <stdio.h>
#include "filesystem.hpp"


using namespace std;


/* functon to encode 8 bit mono pcm to mp3 */
int Mp3Encod::encode_8bit_mono(WavDecode *wd, lame_t lame, int numSamples, unsigned char* mMp3Buffer, int mp3BufSize) {
    uint32_t datasz = wd->getDataSize();
    int encoded=-1;
    std::vector<uint8_t> copiedDataLVec;
    try {
        copiedDataLVec.resize(datasz * sizeof(short int));
    } catch(...) {
        log->LogErr("ERROR allocating copiedDataLVec");
        lame_close(lame);
        lame = NULL;
    }
    uint8_t* mCopiedDataL = &copiedDataLVec[0];
    
    // Copy data in 16-bit buffer mCopiedDataL, converting to signed
    short int* sip = (short int *) mCopiedDataL;
    const char* datap = wd->getRawData();
    
    for( uint32_t i=0; i<datasz; i++ )
        sip[i] = ((short)(datap[i] - 0x80)) << 8;
    encoded = lame_encode_buffer(lame, (short int *) mCopiedDataL,
                                 NULL, numSamples, mMp3Buffer, (int)mp3BufSize);
    return encoded;
}

/* functon to encode 16 bit mono pcm to mp3 */
int Mp3Encod::encode_16bit_mono(WavDecode *wd, lame_t lame, int numSamples, unsigned char* mMp3Buffer, int mp3BufSize) {
    return lame_encode_buffer(lame,
                                 (short int *) wd->getRawData(),
                                 NULL, numSamples, mMp3Buffer, (int)mp3BufSize);
}

/* functon to encode 24 bit mono pcm to mp3 */
int Mp3Encod::encode_24bit_mono(WavDecode *wd, lame_t lame, int numSamples, unsigned char* mMp3Buffer, int mp3BufSize) {
    //TODO
    return 0;
}

/* functon to encode 32 bit mono pcm to mp3 */
int Mp3Encod::encode_32bit_mono(WavDecode *wd, lame_t lame, int numSamples, unsigned char* mMp3Buffer, int mp3BufSize) {
    //TODO
    return 0;
}

void Mp3Encod::encode(string filePath) {
    
    /* Initialize the wav decoder */
    WavDecode *wd;
    try {
        wd = new WavDecode(fs, filePath);
    } catch (const char* msg) {
        cout << msg << filePath << endl;
        return;
    }
    
    /* filePath has .wav change it to .mp3 */
    fs->changeExtensionTo(filePath, encExtn);
    /* Init lame */
    lame_t lame = lame_init();
    lame_set_num_channels(lame, wd->getNumChannels());
    lame_set_in_samplerate(lame, wd->getSampleRate());
    lame_set_VBR(lame, vbr_default);
    lame_set_quality(lame, 5);
    
    /* set mono/stereo */
    if(wd->getNumChannels() == 1 )
        lame_set_mode(lame, MONO);
    else
        lame_set_mode(lame, STEREO);
    
    lame_set_bWriteVbrTag(lame, 0);
    lame_init_params(lame);
    
    int numSamples = wd->getDataSize() / wd->getFrameSize();
     // Calculate MP3 buffer size, according to LAME lib
    size_t mp3BufSize = numSamples*5/4 + 7200;
    std::vector<unsigned char> mp3Buffer;
    mp3Buffer.resize(mp3BufSize);
    unsigned char* mMp3Buffer = &mp3Buffer[0];
    
    // Encode PCM data in mp3
    uint16_t bps = wd->getBPS();
    int encoded=-1;
    if( wd->getNumChannels() == 1 )  // mono
    {
        if( (8 == bps) && (1 == wd->getFrameSize()) ){
            encoded = encode_8bit_mono(wd, lame, numSamples, mMp3Buffer, (int)mp3BufSize);
        } else if( (16 == bps) || ((8 == bps) && (2 == wd->getFrameSize())) )
        {
            encoded = encode_16bit_mono(wd, lame, numSamples, mMp3Buffer, (int)mp3BufSize);
            
        } else if( (24 == bps) && (3 == wd->getFrameSize()) )
        {
              encoded = encode_24bit_mono(wd, lame, numSamples, mMp3Buffer, (int)mp3BufSize);
        } else if( (32 == bps) || ((24 == bps) && (4 == wd->getFrameSize())) )
        {
            encoded = encode_32bit_mono(wd, lame, numSamples, mMp3Buffer, (int)mp3BufSize);
        }
    } else { // stereo
        // TODO
    }
        
    
    if( encoded <= 0 )
    {
        log->LogErr("ERROR in lame_encode_buffer");
    }
    else
    {
        fs->writeFileCharacters((char *)mMp3Buffer, filePath, encoded);
        int flushed = lame_encode_flush(lame, mMp3Buffer, (int)mp3BufSize);
        fs->appendFileCharacters((char *)mMp3Buffer, filePath, flushed);
        lame_close(lame);
    }
    delete wd;
}
