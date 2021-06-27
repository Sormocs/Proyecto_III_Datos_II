/**
 * @file HuffDict.cpp
 * @brief Conteiene las definiciones de los metodos de la lista enlazada del diccionario.
 */

#include "HuffDict.h"

/**
 * @breif Inserta un nodo nuevo en el diccionario.
 * @param node
 */
void HuffDict::Insert(DictNode *node) {

    if (start == nullptr){

        start = node;
        end = node;
        node->next = nullptr;

    } else {

        end->next = node;
        node->next = nullptr;
        end = node;

    }
    size += 1;

}

/**
 * @Muestra el diccionario en consola.
 */
void HuffDict::Show() {

    DictNode* temp = start;
    std::cout << "[ ";
    while(temp != nullptr){
        std::cout << "("+temp->character << " , " << temp->code << ")";
        temp = temp->next;
    }
    std::cout << "]" << std::endl;

}
