//
// Created by luis on 24/6/21.
//

#include "NodePath.h"

NodePath::NodePath(std::string name, std::string path) {
    this->path = path;
    this->name = name;
}

NodePath* NodePath::GetNext() {
    return this->next;
}

void NodePath::SetNext(NodePath *node) {
    this->next = node;
}