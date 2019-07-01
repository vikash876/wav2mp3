//
//  logger.cpp
//  wav2mp3
//
//  Created by Vikash jha on 01.07.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#include "logger.hpp"

using namespace std;

void ConsoleLogger::LogInfo(std::string s) {
    cout << s << endl;
}


void ConsoleLogger::LogErr(std::string s) {
    cerr << s << endl;
}
