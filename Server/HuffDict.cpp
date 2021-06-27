//
// Created by sormocs on 6/24/21.
//

#include "HuffDict.h"

void HuffDict::Insert(DictNode *node) {

    if (start == nullptr){

        start = node;
        end = node;
        node->next = nullptr;

    } else {

        end->next = node;
        node->next = nullptr;
        end = node;

    }
    size += 1;

}

void HuffDict::Show() {

    DictNode* temp = start;
    std::cout << "[ ";
    while(temp != nullptr){
        std::cout << "("+temp->character << " , " << temp->code << ")";
        temp = temp->next;
    }
    std::cout << "]" << std::endl;

}
