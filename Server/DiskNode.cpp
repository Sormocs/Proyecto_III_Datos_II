//
// Created by luis on 23/6/21.
//

#include "DiskNode.h"

/**
 * @brief constructor of disk node
 * @param path string
 */
DiskNode::DiskNode(std::string path) {

    this->path = path;
    back = nullptr;
    next = nullptr;
    FillPath();

}

/**
 * @brief get node back
 * @return DiskNode*
 */

DiskNode* DiskNode::GetBack() {
    return back;
}

/**
 * @brief get node next
 * @return DiskNode*
 */

DiskNode* DiskNode::GetNext() {
    return next;
}

/**
 * @brief Set back node
 * @param node DiskNode*
 */
void DiskNode::SetBack(DiskNode *node) {
    back = node;
}
/**
 * @brief Set back node
 * @param node DiskNode*
 */

void DiskNode::SetNext(DiskNode *node) {
    next = node;
}

/**
 * @brief Get data
 * @return ListPath*
 */

ListPath* DiskNode::GetData() {
    return data;
}

/**
 * @brief fill list path
 */
void DiskNode::FillPath() {

    FileManager *file = new FileManager;

    json obj = file->ReadJson(path + "/metadata.json");

    int size = obj["amount"].get<int>();

    for (int i = 0; i < size; ++i) {

        data->AddFinal(obj["Archivos"][to_string(i)]["name"], obj["Archivos"][to_string(i)]["path"]);

    }

    delete file;

}
