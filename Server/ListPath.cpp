//
// Created by luis on 24/6/21.
//

#include "ListPath.h"

/**
 * @brief constuctor
 */

ListPath::ListPath() {

    this->size = 0;
    this->head = nullptr;
}

/**
 * @brief Add final element
 * @param name string
 * @param path string
 */

void ListPath::AddFinal(std::string name, std::string path) {

    NodePath* nodePath = new NodePath(name,path);
    nodePath->SetNext(nullptr);

    if(size == 0){
        head = nodePath;
    } else{
        NodePath* temp = head;
        while (temp->GetNext() != nullptr){
            temp = temp->GetNext();
        }
        temp->SetNext(nodePath);
    }
    size++;


}