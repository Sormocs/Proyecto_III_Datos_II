//
// Created by luis on 24/6/21.
//

#include "NodePath.h"

/**
 * @brief Constructor
 * @param name string
 * @param path string
 */

NodePath::NodePath(std::string name, std::string path) {
    this->path = path;
    this->name = name;
}

/**
 * @brief Get Next
 * @return NodePath
 */

NodePath* NodePath::GetNext() {
    return this->next;
}

/**
 * @brief set next node
 * @param node node*
 */
void NodePath::SetNext(NodePath *node) {
    this->next = node;
}