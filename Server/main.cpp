#include <iostream>
#include "BytesConverter.h"
#include <bitset>
#include <iomanip>
#include "FileManager.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;


int main() {

/*    string temp = "hola mundo me cago en el TEC de mierda";

    BytesConverter *converter = new BytesConverter;

    string bytes = converter->BytestoString(converter->GetBytes(converter->GetChars(temp)));

    converter->GetParity(bytes);

    cout << converter->text1 << endl;

    cout << converter->text2 << endl;

    cout << converter->parity << endl;

    string temp2 = converter->GenerateString(converter->BytesToChar(converter->GetBytesChar(converter->text)));

    cout << temp2 << endl;

    cout << temp << endl;*/

    //FileManager *file = new FileManager;
    //file->Write("hola", "../RAID/Node1/metadata.txt");

    //std::string temp = file->Read("../RAID/Node1/metadata.txt");

    json obj;

    obj["Archivo1"]["size"] = "2312";


    std::ofstream o("../file.json");
    o << std::setw(4) << obj << std::endl;

    std::ifstream i("../file.json");
    json j;
    i >> j;

    cout << j["Archivo1"]["size"];

}