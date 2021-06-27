/**
 * @file StrChar.h
 * @author Sergio MB
 * @brief Contiene la declaracion de metodos de la lista enlazada que cuenta caracteres y frecuencia
 */

#include <iostream>

#pragma once

/**
 * @brief Nodo de la lista enlazada que contiene un caracter con su frecuencia.
 */
struct Character{

    char character;
    int freq;
    Character* next;

};

/**
 * @brief Lista enlazada que contiene nodos de Character.
 */
class StrChar {

public:
    int size = 0;
    Character* start;
    Character* end;
    StrChar() = default;
    void Insert(Character* node);
    void Show();

};


