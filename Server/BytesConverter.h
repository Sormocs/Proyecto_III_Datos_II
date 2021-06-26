//
// Created by luis on 23/6/21.
//

#ifndef SERVER_BYTESCONVERTER_H
#define SERVER_BYTESCONVERTER_H

#include <iostream>
#include <vector>
#include <bitset>

using namespace  std;

class BytesConverter {


public:

    std::string parity = "";
    std::string text1;
    std::string text2;
    std::string text;

    std::vector<char> GetChars(std::string text);
    std::vector<bitset<8>> GetBytes(std::vector<char> v);
    std::string BytestoString(std::vector<bitset<8>> b);
    void GetParity(std::string bytes);

    std::vector<bitset<8>> GetBytesChar(std::string text);
    std::vector<char> BytesToChar(std::vector<bitset<8>> b);
    std::string GenerateString(std::vector<char> c);

    void ResetText();

    std::string GetDisk(std::string text1, std::string text2);


};


#endif //SERVER_BYTESCONVERTER_H
