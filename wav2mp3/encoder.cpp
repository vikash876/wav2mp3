//
//  encoder.cpp
//  wav2mp3
//
//  Created by Vikash jha on 13.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#include "encoder.hpp"
#include <unistd.h>
#include <lame.h>
#include <stdio.h>


using namespace std;

void Mp3Encod::encode(string filePath) {
    
    int read, write;
    
    FILE *pcm = fopen(filePath.c_str(), "rb");
    size_t pos = filePath.rfind('.');
    string extn;
    if (pos != std::string::npos) {
        // return the substring
         extn = filePath.substr(pos+1);
    }
    string::size_type i = filePath.find(extn);
    filePath.erase(i, extn.size());
    filePath += "mp3";
    FILE *mp3 = fopen(filePath.c_str(), "wb");
    cout << "to " << filePath <<endl;
    
    const int PCM_SIZE = 8192;
    const int MP3_SIZE = 8192;
    
    short int pcm_buffer[PCM_SIZE*2];
    unsigned char mp3_buffer[MP3_SIZE];
    
    lame_t lame = lame_init();
    lame_set_in_samplerate(lame, 44100);
    lame_set_VBR(lame, vbr_default);
    lame_init_params(lame);
    
    do {
        read = fread(pcm_buffer, 2*sizeof(short int), PCM_SIZE, pcm);
        if (read == 0)
            write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
        else
            write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
        fwrite(mp3_buffer, write, 1, mp3);
    } while (read != 0);
    
    lame_close(lame);
    fclose(mp3);
    fclose(pcm);
}
