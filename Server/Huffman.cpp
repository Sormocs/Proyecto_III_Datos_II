#include "Huffman.h"

Huffman* Huffman::instance = nullptr;

Huffman::Huffman() {

    dictionary->start = nullptr;
    dictionary->end = nullptr;

}

Huffman* Huffman::getInstance() {

    if (instance == nullptr){
        instance = new Huffman;
    }
    return instance;

}

std::string Huffman::GetCode(int index){

    DictNode* temp = dictionary->start;
    while (temp != nullptr){

        if (temp->character == std::string(1,msg[index])) return temp->code;
        else temp = temp->next;

    }

}

void Huffman::FormJson() {
    j1["DictSize"] = dictionary->size;

    DictNode* temp = dictionary->start;
    for (int i = 0; i < dictionary->size; i++ ){

        j1["Dictionary"]["node"+std::to_string(dictcount)]["char"] = temp->character;
        j1["Dictionary"]["node"+std::to_string(dictcount)]["code"] = temp->code;
        dictcount ++;
        temp = temp->next;

    }

    for (int i = 0; i < msg.length(); i++){

        if (msg[i] == ' '){
            continue;
        } else{
            j1["Message"]["lnum"+std::to_string(wordc)+"code"] = GetCode(i);
            wordc++;
        }

    }

    j1["MsgSize"] = wordc;
    std::cout << to_string(j1) << std::endl;

    wordc = 0;
    dictcount = 0;

}

/**
 * @brief Metodo que crea las listas con lass frecuencias de cada caracter del mensaje
 * @param message
 */
void Huffman::GetFreqs(std::string message) {

    msg = message;
    StrChar* freqArr = new StrChar;
    freqArr->start = nullptr;
    freqArr->end = nullptr;
    freqArr->size = 0;
    for (int i = 0; i < message.length(); i++){

        char c = message[i];
        if (c ==  ' ') continue;
        else{
            bool in = false;
            Character* temp = freqArr->start;
            while (temp != nullptr){
                if (c == temp->character){
                    in = true;
                    break;
                } else{
                    temp = temp->next;
                }
            }
            if (in){
                temp->freq += 1;
            } else{
                Character* node = new Character;
                node->character = c;
                node->freq = 1;
                node->next = nullptr;
                freqArr->Insert(node);
            }
        }
    }
    freqArr->Show();
    char arr[freqArr->size];
    int freq[freqArr->size];

    Character* temp = freqArr->start;
    int i = 0;
    while (temp != nullptr) {

        arr[i] = temp->character;
        freq[i] = temp->freq;
        i++;
        temp = temp->next;

    }

    int size = sizeof(arr) / sizeof(arr[0]);
    HuffmanCodes(arr,freq,size);
    FormJson();
}

// A utility function allocate a new
// min heap node with given character
// and frequency of the character
struct MinHeapNode* Huffman::newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp
            = (struct MinHeapNode*)malloc
                    (sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

// A utility function to create
// a min heap of given capacity
struct MinHeap* Huffman::createMinHeap(unsigned capacity)

{

    struct MinHeap* minHeap
            = (struct MinHeap*)malloc(sizeof(struct MinHeap));

    // current size is 0
    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array
            = (struct MinHeapNode**)malloc(minHeap->
            capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// A utility function to
// swap two min heap nodes
void Huffman::swapMinHeapNode(struct MinHeapNode** a,struct MinHeapNode** b)

{

    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// The standard minHeapify function.
void Huffman::minHeapify(struct MinHeap* minHeap, int idx)

{

    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->
            freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->
            freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check
// if size of heap is 1 or not
int Huffman::isSizeOne(struct MinHeap* minHeap)
{

    return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct MinHeapNode* Huffman::extractMin(struct MinHeap* minHeap)

{

    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0]
            = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

// A utility function to insert
// a new node to Min Heap
void Huffman::insertMinHeap(struct MinHeap* minHeap,struct MinHeapNode* minHeapNode)

{

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap
void Huffman::buildMinHeap(struct MinHeap* minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void Huffman::printArr(int arr[], int n, DictNode* node){

    std::string code = "";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i];
        code += std::to_string(arr[i]);
    }
    node->code = code;

    std::cout<<"\n";
}

// Utility function to check if this node is leaf
int Huffman::isLeaf(struct MinHeapNode* root)

{

    return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHeap* Huffman::createAndBuildMinHeap(char data[], int freq[], int size)

{

    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

// The main function that builds Huffman tree
struct MinHeapNode* Huffman::buildHuffmanTree(char data[], int freq[], int size)

{
    struct MinHeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity
    // equal to size. Initially, there are
    // modes equal to size.
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap)) {

        // Step 2: Extract the two minimum
        // freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3: Create a new internal
        // node with frequency equal to the
        // sum of the two nodes frequencies.
        // Make the two extracted node as
        // left and right children of this new node.
        // Add this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the
    // root node and the tree is complete.
    return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void Huffman::printCodes(struct MinHeapNode* root, int arr[], int top)

{

    // Assign 0 to left edge and recur
    if (root->left) {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right) {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (isLeaf(root)) {

        std::cout<< root->data <<": ";
        DictNode* temp = new DictNode;
        temp->character = root->data;
        printArr(arr, top, temp);
        dictionary->Insert(temp);
    }
}

// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
void Huffman::HuffmanCodes(char data[], int freq[], int size)

{
    // Construct Huffman Tree
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

    // Print Huffman codes using
    // the Huffman tree built above
    int arr[MAX_TREE_HT], top = 0;

    printCodes(root, arr, top);
    dictionary->Show();
}

std::string Huffman::GetChar(HuffDict* dict, std::string code) {

    DictNode* temp = dict->start;
    while (temp != nullptr){

        if (temp->code == code) return temp->character;
        else temp = temp->next;

    }

}


std::string Huffman::Decode(std::string message) {

    json recv = json::parse(message);
    int size = recv["DictSize"].get<int>();
    HuffDict* new_dict = new HuffDict;
    new_dict->start = nullptr;

    for (int i=0; i < size; i++){

        DictNode* temp = new DictNode;
        temp->character = recv["Dictionary"]["node"+std::to_string(i)]["char"].get<std::string>();
        temp->code = recv["Dictionary"]["node"+std::to_string(i)]["code"].get<std::string>();
        new_dict->Insert(temp);
        std::cout << "(" + temp->character + ","+ temp->code +")";

    }
    std::cout << "\n";

    std::string msg = "";
    for (int i = 0; i < recv["MsgSize"].get<int>() ; i++){

        std::cout << i << std::endl;
        msg += GetChar(new_dict ,recv["Message"]["lnum"+std::to_string(i)+"code"].get<std::string>());

    }

    std::cout << msg << std::endl;

    return msg;

}
