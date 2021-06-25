#include "NodeController.h"


using namespace std;



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

    NodeController *controller = new NodeController();

    controller->SaveFile("El TEC es una mierda entera, me quiero morir porfavor", "test");


}