//
// Created by luis on 23/6/21.
//

#ifndef SERVER_DISKNODE_H
#define SERVER_DISKNODE_H

#include <iostream>


class DiskNode {

private:

    std::string data;
    DiskNode* back;
    DiskNode* next;

public:

    DiskNode();
    DiskNode* GetNext();
    DiskNode* GetBack();
    void SetBack(DiskNode* node);
    void SetNext(DiskNode* node);

};


#endif //SERVER_DISKNODE_H
