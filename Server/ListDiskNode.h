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

public:

    ListDiskNode();
    void Add(DiskNode* node);
    void DeleteNode(int i);

};


#endif //SERVER_LISTDISKNODE_H
