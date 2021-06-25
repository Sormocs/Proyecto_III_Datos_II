//
// Created by luis on 23/6/21.
//

#ifndef SERVER_DISKNODE_H
#define SERVER_DISKNODE_H

#include <iostream>
#include "ListPath.h"


class DiskNode {

private:

    std::string path;
    ListPath *data = new ListPath();
    DiskNode* back;
    DiskNode* next;

public:

    DiskNode(std::string path);
    DiskNode* GetNext();
    DiskNode* GetBack();
    void SetBack(DiskNode* node);
    void SetNext(DiskNode* node);
    ListPath* GetData();
    void FillPath();

};


#endif //SERVER_DISKNODE_H
