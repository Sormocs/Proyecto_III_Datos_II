//
// Created by luis on 24/6/21.
//

#ifndef SERVER_LISTPATH_H
#define SERVER_LISTPATH_H
#include <iostream>
#include "NodePath.h"

class ListPath {

private:

    NodePath* head;
    int size;

public:

    ListPath();
    void AddFinal(std::string name, std::string path);

};


#endif //SERVER_LISTPATH_H
