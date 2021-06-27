#include <iostream>

#pragma once

struct DictNode{

    std::string character;
    std::string code;
    DictNode* next;

};

class HuffDict {

public:
    int size = 0;
    DictNode* start;
    DictNode* end;
    HuffDict() = default;
    void Insert(DictNode* node);
    void Show();


};


