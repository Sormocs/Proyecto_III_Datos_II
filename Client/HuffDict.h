/**
 * @file HuffDict.h
 * @author Sergio MB
 * @brief Contiene la declaracion de los metodos de la lista enlazada que guarda caracteres con frecuencia en el huffman.
 */

#include <iostream>

#pragma once

/**
 * @brief Nodo para el diccionario.
 */
struct DictNode{

    std::string character;
    std::string code;
    DictNode* next;

};

/**
 * @brief Lista enlazada que contiene nodos de DictNode con cada caracter y su codigo en el arbol.
 */
class HuffDict {

public:
    int size = 0;
    DictNode* start;
    DictNode* end;
    HuffDict() = default;
    void Insert(DictNode* node);
    void Show();


};


