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
#include <fstream>
#include <vector>

#endif /* filesystem_hpp */



class LinuxFileSys : public FileSys {
private:
    Logger *log;
public:
    /* Constructor */
    LinuxFileSys(Logger& log) {this->log = &log;}
    /* Get list of file with matching extensions */
    void getFileListExtn(std::list<std::string>& fileList, std::string directory, std::string extn);
    /* Read the file content into buffer */
    void readFileCharacters(std::vector<char>& buffer, std::string filePath);
    /* Write the buffer content into file */
    void writeFileCharacters(char *buffer, std::string filePath, int size);
    /* Append the buffer content into file */
    void appendFileCharacters(char *buffer, std::string filePath, int size);
    /* Change filePath's old extension (ex: .wav) to a new extension (ex: .mp3) */
    void changeExtensionTo(std::string& filePath, std::string extn);
};
