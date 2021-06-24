//
// Created by luis on 23/6/21.
//

#include "DiskNode.h"


DiskNode::DiskNode() {

    back = nullptr;
    next = nullptr;

}

DiskNode* DiskNode::GetBack() {
    return back;
}

DiskNode* DiskNode::GetNext() {
    return next;
}

void DiskNode::SetBack(DiskNode *node) {
    back = node;
}

void DiskNode::SetNext(DiskNode *node) {
    next = node;
}
