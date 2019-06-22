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

class Mp3Encod : public EncodLib {
public:
    void encode(std::string filePath);
};

#endif /* encoder_hpp */
