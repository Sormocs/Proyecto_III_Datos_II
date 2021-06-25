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

    ConfigMetada(path,  path1, converter->text1.length());
    ConfigMetada(path,  path2, converter->text1.length());
    ConfigMetada(path,  path3, converter->text1.length());

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