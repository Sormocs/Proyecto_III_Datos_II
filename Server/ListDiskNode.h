//
// Created by luis on 23/6/21.
//

#ifndef SERVER_LISTDISKNODE_H
#define SERVER_LISTDISKNODE_H

#include "DiskNode.h"
#include <iostream>


class ListDiskNode {

private:

    DiskNode* head;
    int size = 1;

public:

    ListDiskNode();
    void Add(std::string path);
    void DeleteNode(int i);

};


#endif //SERVER_LISTDISKNODE_H
