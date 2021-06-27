/**
 * @file Huffman.h
 * @author Sergio MB
 * @brief Contiene la definicion de la clase Huffman y sus metodos.
 */

#include <iostream>
#include <cstdlib>
#include <sstream>
#include "HuffDict.h"
#include "StrChar.h"
#include "json.hpp"

#pragma once

#define MAX_TREE_HT 100

/**
 * @brief Nodo del arbol de huffman.
 */
struct MinHeapNode {

    char data;

    unsigned freq;

    struct MinHeapNode *left, *right;
};

/**
 * @brief Nodo que contiene nodos y no caracteres
 */
struct MinHeap {

    unsigned size;

    unsigned capacity;

    struct MinHeapNode** array;
};

using json = nlohmann::json;
/**
 * @brief Clase Huffman, que se define para el algoritmo de compresion Huffman
 */
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
    std::string GetFreqs(std::string message);

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


