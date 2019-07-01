//
//  logger.hpp
//  wav2mp3
//
//  Created by Vikash jha on 01.07.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#ifndef logger_hpp
#define logger_hpp

#include <stdio.h>
#include "interfaces.hpp"
#include <iostream>

class ConsoleLogger : public Logger {
public:
    /* Display informational logs */
    void LogInfo(std::string s);
    /* Display error logs */
    void LogErr(std::string s);
};

#endif /* logger_hpp */
