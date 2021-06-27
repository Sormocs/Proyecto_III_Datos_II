//
// Created by sormocs on 6/25/21.
//

#include "StrChar.h"

void StrChar::Insert(Character *node) {

    if (start == nullptr){

        start = node;
        end = node;
        node->next = nullptr;
        node->freq = 1;

    } else {

        end->next = node;
        node->next = nullptr;
        end = node;
        node->freq = 1;

    }
    size += 1;

}

void StrChar::Show() {

    Character* temp = start;
    std::cout << "[ ";
    while(temp != nullptr){
        std::cout << "("+std::string(1,temp->character) << " , " << temp->freq << ")";
        temp = temp->next;
    }
    std::cout << "]" << std::endl;

}
