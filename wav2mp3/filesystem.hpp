//
//  filesystem.hpp
//  wav2mp3
//
//  Created by Vikash jha on 13.06.19.
//  Copyright © 2019 Vikash jha. All rights reserved.
//

#ifndef filesystem_hpp
#define filesystem_hpp

#include <iostream>
#include "interfaces.hpp"

#endif /* filesystem_hpp */



class LinuxFileSys : public FileSys {
private:
    std::list<std::string> fileName;
public:
    std::list<std::string> getFileList(std::string directory);
};
