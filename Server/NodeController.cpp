//
// Created by luis on 24/6/21.
//

#include "NodeController.h"

NodeController::NodeController() {

    listNodes->Add(path1);
    listNodes->Add(path2);
    listNodes->Add(path3);

}

void NodeController::SaveFile(string text, string path) {

    string bytes = converter->BytestoString(converter->GetBytes(converter->GetChars(text)));

    converter->GetParity(bytes);

    file->Write(converter->text1,path1 + "/" + path + ".txt");
    file->Write(converter->text2,path2 + "/" + path + ".txt");
    file->Write(converter->parity,path3 + "/" + path+ ".txt");

    ConfigMetada(path,  path1, converter->text1.length()/8);
    ConfigMetada(path,  path2, converter->text1.length()/8);
    ConfigMetada(path,  path3, converter->text1.length()/8);

}

void NodeController::DeleteFile( string name) {

    string dataFile = file->Read(path1 + "/" + name + ".txt");

    int bytes = dataFile.length()/8;

    file->Delete(path1 + "/" + name + ".txt");
    file->Delete(path2 + "/" + name + ".txt");
    file->Delete(path3 + "/" + name + ".txt");

    DeleteMetada(name,path1,bytes);
    DeleteMetada(name,path2,bytes);
    DeleteMetada(name,path3,bytes);

}

void NodeController::ConfigMetada(string name, string path, int bytes) {

    json obj = file->ReadJson(path  + "/metadata.json");

    string newPath = path + "/" + name + ".txt";

    int num = obj["amount"].get<int>();
    int newBytes = obj["reserved"].get<int>();

    obj["Archivos"][to_string(num)]["name"] = name;
    obj["Archivos"][to_string(num)]["path"] = newPath;
    obj["amount"] = num+1;
    obj["reserved"] = newBytes+bytes;

    file->WriteJson(obj, path + "/metadata.json");

}

void NodeController::DeleteMetada(string name, string path, int bytes) {

    json obj = file->ReadJson(path  + "/metadata.json");

    int num = obj["amount"].get<int>();
    int newBytes = obj["reserved"].get<int>();

    if(num == 1){
        obj.erase("Archivos");
    }else {
        int newNum = 0;
        for (int i = 0; i < num; ++i) {

            if (obj["Archivos"][to_string(i)]["name"] == name) {
                obj["Archivos"].erase(to_string(i));
            } else {
                obj["Archivos"][to_string(newNum)] = obj["Archivos"][to_string(i)];
                obj["Archivos"].erase(to_string(i));
                newNum++;
            }
        }
    }

    obj["amount"] = num-1;
    obj["reserved"] = newBytes-bytes;

    file->WriteJson(obj, path + "/metadata.json");

}

json NodeController::ReadBook(string name) {

    if(this->activeDisk1 && this->activeDisk2){

        return WithoutParity(name);

    } else if(this->activeDisk2 == 0){

    } else {

    }

}

json NodeController::WithoutParity(string name) {

    string firstPart = file->Read(path1 + "/" + name + ".txt");
    string secondPart = file->Read(path2 + "/" + name + ".txt");

    firstPart = converter->GenerateString(converter->BytesToChar(converter->GetBytesChar(firstPart)));
    secondPart = converter->GenerateString(converter->BytesToChar(converter->GetBytesChar(secondPart)));

    string textComplete = firstPart + secondPart;

    json obj;

    obj["text"] = textComplete;
    obj["nameFile"] = name;

    return obj;

}

json NodeController::ParityDisk1(string name) {

    string firstPart = file->Read(path3 + "/" + name + ".txt");
    string secondPart = file->Read(path2 + "/" + name + ".txt");

    firstPart = converter->GetDisk(firstPart,secondPart);

    firstPart = converter->GenerateString(converter->BytesToChar(converter->GetBytesChar(firstPart)));
    secondPart = converter->GenerateString(converter->BytesToChar(converter->GetBytesChar(secondPart)));

    string textComplete = firstPart + secondPart;

    json obj;

    obj["text"] = textComplete;
    obj["nameFile"] = name;

    return obj;

}

json NodeController::ParityDisj2(string name) {

    string firstPart = file->Read(path1 + "/" + name + ".txt");
    string secondPart = file->Read(path3 + "/" + name + ".txt");

    secondPart = converter->GetDisk(firstPart,secondPart);

    firstPart = converter->GenerateString(converter->BytesToChar(converter->GetBytesChar(firstPart)));
    secondPart = converter->GenerateString(converter->BytesToChar(converter->GetBytesChar(secondPart)));

    string textComplete = firstPart + secondPart;

    json obj;

    obj["text"] = textComplete;
    obj["nameFile"] = name;

    return obj;

}