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

    converter->ResetText();

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

string NodeController::ReadBook(string name) {

    if(this->activeDisk1 && this->activeDisk2){
        return WithoutParity(name);
    } else if(this->activeDisk2 == 0){
        return ParityDisj2(name);
    } else {
        return ParityDisk1(name);
    }

}

json NodeController::ReadRaid(string name) {

    json obj = file->ReadJson(path3 + "/metadata.json");

    json temp;

    int size = obj["amount"].get<int>();

    for (int i = 0; i < size; ++i) {

        if(CheckMemory(name, obj["Archivos"][to_string(i)]["name"].get<string>())){
            string data = ReadBook(name);
            temp[to_string(i)]["name"] = obj["Archivos"][to_string(i)]["name"].get<string>();
            temp[to_string(i)]["data"] = data;
        }

    }

    temp["size"] = size;

    return temp;
}

string NodeController::WithoutParity(string name) {

    string firstPart = file->Read(path1 + "/" + name + ".txt");
    string secondPart = file->Read(path2 + "/" + name + ".txt");

    string textComplete = firstPart + secondPart;

    textComplete = converter->GenerateString(converter->BytesToChar(converter->GetBytesChar(textComplete)));

    return textComplete;

}

string NodeController::ParityDisk1(string name) {

    string firstPart = file->Read(path3 + "/" + name + ".txt");
    string secondPart = file->Read(path2 + "/" + name + ".txt");

    firstPart = converter->GetDisk(firstPart,secondPart);

    string textComplete = firstPart + secondPart;

    textComplete = converter->GenerateString(converter->BytesToChar(converter->GetBytesChar(textComplete)));

    return textComplete;

}

string NodeController::ParityDisj2(string name) {

    string firstPart = file->Read(path1 + "/" + name + ".txt");
    string secondPart = file->Read(path3 + "/" + name + ".txt");

    secondPart = converter->GetDisk(firstPart,secondPart);

    string textComplete = firstPart + secondPart;

    textComplete = converter->GenerateString(converter->BytesToChar(converter->GetBytesChar(textComplete)));

    return textComplete;

}

bool NodeController::CheckMemory(string search, string name) {

    auto check = name.find(search);

    if(check != string::npos){
        return 1;
    } else {
        return 0;
    }

}

json NodeController::CheckSpace() {

    json Node1 = file->ReadJson(path1 + "/metadata.json");
    json Node2 = file->ReadJson(path2 + "/metadata.json");
    json Node3 = file->ReadJson(path3 + "/metadata.json");

    json temp;

    temp["Node1"] = Node1["size"].get<int>() - Node1["reserved"].get<int>();
    temp["Node2"] = Node2["size"].get<int>() - Node2["reserved"].get<int>();
    temp["Node3"] = Node3["size"].get<int>() - Node3["reserved"].get<int>();

    return temp;

}