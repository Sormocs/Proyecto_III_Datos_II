//
// Created by luis on 24/6/21.
//

#ifndef SERVER_NODEPATH_H
#define SERVER_NODEPATH_H
#include <iostream>

class NodePath {

private:

    std::string name;
    std::string path;

    NodePath* next;

public:

    NodePath(std::string name, std::string path);
    NodePath* GetNext();
    void SetNext(NodePath* node);

};


#endif //SERVER_NODEPATH_H
