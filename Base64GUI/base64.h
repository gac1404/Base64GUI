#ifndef BASE64_H
#define BASE64_H

#include "string"
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <array>

class Base64
{
public:
    Base64();

     bool encode(std::string filepath);
     void decode(std::string filepath , std::string outputformat);


private:
    const std::string _base64Chars{
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/"};


};

#endif // BASE64_H
