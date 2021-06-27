/**
 * @file StrChar.cpp
 * @brief Contiene la  definicion de los metodos de la lista de StrChar
 */

#include "StrChar.h"

/**
 * @brief Inserta un nuevo elemento en la lista.
 * @param node
 */
void StrChar::Insert(Character *node) {

    if (start == nullptr){

        start = node;
        end = node;
        node->next = nullptr;
        node->freq = 1;

    } else {

        end->next = node;
        node->next = nullptr;
        end = node;
        node->freq = 1;

    }
    size += 1;

}

/**
 * @brief Metodo para mostrar la lista en consola.
 */
void StrChar::Show() {

    Character* temp = start;
    std::cout << "[ ";
    while(temp != nullptr){
        std::cout << "("+std::string(1,temp->character) << " , " << temp->freq << ")";
        temp = temp->next;
    }
    std::cout << "]" << std::endl;

}
