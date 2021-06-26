#include "BytesConverter.h"

/**
 * @brief Gets char of one string
 * @param text string
 * @return vector<char>
 */

vector<char> BytesConverter::GetChars(std::string text) {

    vector<char> v(text.begin(), text.end());
    return v;

}

/**
 * @brief Get bytes of vector char
 * @param v vector<char>
 * @return vector<bitset<8>>
 */

vector<bitset<8>> BytesConverter::GetBytes(std::vector<char> v) {

    vector<bitset<8>> b;

    for (int i = 0; i < v.size(); ++i) {

        std::bitset<8> bitset(v.at(i));
        b.push_back(bitset);

    }

    return b;

}

/**
 * @brief convert bytes to string bytes
 * @param b vector<bitset<8>>
 * @return string
 */

string BytesConverter::BytestoString(std::vector<bitset<8>> b) {

    string temp = "";

    for (int i = 0; i < b.size(); ++i) {

        temp += b.at(i).to_string();

    }

    this->text = temp;

    return temp;

}

/**
 * @brief Generate parity with 2 text with xor parity
 * @param bytes string
 */

void BytesConverter::GetParity(std::string bytes) {

    this->text1 = bytes.substr(0,bytes.length()/2);
    this->text2 = bytes.substr(bytes.length()/2,bytes.length());

    for (int i = 0; i < text2.size(); ++i) {
        if(text1.at(i) ^ text2.at(i)){
            parity+='1';
        } else{
            parity+='0';
        }
    }

}

/**
 * @brief get bytes to string
 * @param text string
 * @return vector<bitset<8>>
 */

vector<bitset<8>> BytesConverter::GetBytesChar(std::string text) {

    vector<bitset<8>> b;

    int size = text.length()/8;

    for (int i = 0; i < size; i++) {

        bitset<8> byte(text.substr(0,8));
        b.push_back(byte);

        if (text.length() != 8){
            text = text.substr(8,text.length());
        }

    }
    return b;
}

/**
 * @brief Get char from  bytes
 * @param b vector<bitset<8>>
 * @return vector<char>
 */

vector<char> BytesConverter::BytesToChar(std::vector<bitset<8>> b) {

    vector<char> c;

    for (int i = 0; i < b.size(); ++i) {

        unsigned long k = b.at(i).to_ulong();
        char caracter = static_cast<char>( k );

        c.push_back(caracter);

    }

    return c;

}

/**
 * @brief Generate string from chars
 * @param c vector<char>
 * @return string
 */

string BytesConverter::GenerateString(std::vector<char> c) {

    string temp;

    for (int i = 0; i < c.size(); i++) {

        temp.push_back(c.at(i));

    }

    return temp;

}

/**
 * @brief reset texts
 */

void BytesConverter::ResetText() {
    this->text = "";
    this->text1 = "";
    this->text2 = "";
    this->parity = "";

}

/**
 * @brief Get data disk when the disk is disable
 * @param text1 string text
 * @param text2 string parity
 * @return string
 */

std::string BytesConverter::GetDisk(std::string text1, std::string text2) {

    std::string temp = "";

    for (int i = 0; i < text2.length(); ++i) {

        if(text1.at(i) ^ text2.at(i)){
            temp+='1';
        } else{
            temp+='0';
        }

    }

    return temp;

}
