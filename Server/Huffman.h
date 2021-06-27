#include <iostream>
#include <cstdlib>
#include <sstream>
#include "HuffDict.h"
#include "StrChar.h"
#include "json.hpp"

#pragma once

#define MAX_TREE_HT 100

// A Huffman tree node
struct MinHeapNode {

    // One of the input characters
    char data;

    // Frequency of the character
    unsigned freq;

    // Left and right child of this node
    struct MinHeapNode *left, *right;
};

// A Min Heap: Collection of
// min-heap (or Huffman tree) nodes
struct MinHeap {

    // Current size of min heap
    unsigned size;

    // capacity of min heap
    unsigned capacity;

    // Attay of minheap node pointers
    struct MinHeapNode** array;
};

using json = nlohmann::json;
class Huffman {

private:

    json j1;
    std::string msg;
    int dictcount = 0, wordc = 0;

    static Huffman* instance;
    Huffman();
    HuffDict* dictionary = new HuffDict;

    void FormJson();

public:
    static Huffman* getInstance();

    std::string GetCode(int index);
    void GetFreqs(std::string message);

    void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
    void minHeapify(struct MinHeap* minHeap, int idx);
    int isSizeOne(struct MinHeap* minHeap);
    struct MinHeapNode* extractMin(struct MinHeap* minHeap);
    struct MinHeapNode* newNode(char data, unsigned freq);
    struct MinHeap* createMinHeap(unsigned capacity);
    void insertMinHeap(struct MinHeap* minHeap,struct MinHeapNode* minHeapNode);
    void buildMinHeap(struct MinHeap* minHeap);
    void printArr(int arr[], int n, DictNode* node);
    int isLeaf(struct MinHeapNode* root);
    struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);
    struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size);
    void printCodes(struct MinHeapNode* root, int arr[], int top);

    void HuffmanCodes(char data[], int freq[], int size);

    std::string GetChar(HuffDict* dict, std::string code);
    std::string Decode(std::string message);
};


