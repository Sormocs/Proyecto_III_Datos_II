//
// Created by luis on 23/6/21.
//

#include "ListDiskNode.h"

ListDiskNode::ListDiskNode() {
    head = nullptr;
}

void ListDiskNode::Add(std::string path) {
    DiskNode* node = new DiskNode(path);
    if(head == nullptr){
        head = node;
    } else{
        DiskNode* temp = new DiskNode(path);
        for (temp = head; temp->GetNext() != nullptr; temp = temp->GetNext());
        temp->SetNext(node);
        node->SetBack(temp);
    }

}

void ListDiskNode::DeleteNode(int i) {

    if(head == nullptr || i < 0){
        return;
    } if (i == 0){
        DiskNode* temp = head->GetNext();
        delete head;
        head = temp;
        head->SetBack(nullptr);
    } else{
        DiskNode* temp = head;
        for(int k = 0; k < i; k++){
            temp = temp->GetNext();
            if(temp == nullptr){
                return;
            }
        }

        temp->SetBack(temp->GetNext()->GetBack());
        temp->SetNext(temp->GetBack()->GetNext());

        delete temp;
    }

}