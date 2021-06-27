#include <iostream>

#pragma once

struct Character{

    char character;
    int freq;
    Character* next;

};

class StrChar {

public:
    int size = 0;
    Character* start;
    Character* end;
    StrChar() = default;
    void Insert(Character* node);
    void Show();

};


