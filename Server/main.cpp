#include <iostream>
#include "Huffman.h"

//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}




// Driver code
int main()
{

    char arr[] = { 'h','o','l','a' };
    int freq[] = { 1 , 1 , 1 , 1 };

    int size = sizeof(arr) / sizeof(arr[0]);

    //Huffman::getInstance()->HuffmanCodes(arr, freq, size);
    Huffman::getInstance()->GetFreqs("hola");

    return 0;
}

