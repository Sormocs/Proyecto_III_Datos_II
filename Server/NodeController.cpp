//
// Created by luis on 24/6/21.
//

#include "NodeController.h"


/**
 * @brief constructor of NodeController
 */
NodeController::NodeController() {

    listNodes->Add(path1);
    listNodes->Add(path2);
    listNodes->Add(path3);

}

/**
 * @brief save file in Raid with disk nodes
 * @param text string data
 * @param path string name of file
 */

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

/**
 * @brief Delete file in raid with disk nodes
 * @param name string name of file
 */

void NodeController::DeleteFile(string name) {

    string dataFile = file->Read(path1 + "/" + name + ".txt");

    int bytes = dataFile.length()/8;

    file->Delete(path1 + "/" + name + ".txt");
    file->Delete(path2 + "/" + name + ".txt");
    file->Delete(path3 + "/" + name + ".txt");

    DeleteMetada(name,path1,bytes);
    DeleteMetada(name,path2,bytes);
    DeleteMetada(name,path3,bytes);

}

/**
 * Config meta after added file in raid
 * @param name string name of file
 * @param path string path of disk
 * @param bytes int bytes of file
 */

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

/**
 * Config meta after deleted file in raid
 * @param name string name of file
 * @param path string path of disk
 * @param bytes int bytes of file
 */

void NodeController::DeleteMetada(string name, string path, int bytes) {

    json obj = file->ReadJson(path  + "/metadata.json");

    json temp = obj;

    int num = obj["amount"].get<int>();
    int newBytes = obj["reserved"].get<int>();

    if(num == 1){
        temp.erase("Archivos");
    }else {
        temp.erase("Archivos");
        int newNum = 0;
        for (int i = 0; i < num; ++i) {
            if (obj["Archivos"][to_string(i)]["name"] != name) {
                temp["Archivos"][to_string(newNum)] = obj["Archivos"][to_string(i)];
                obj["Archivos"].erase(to_string(i));
                newNum++;
            }
        }
    }

    temp["amount"] = num-1;
    temp["reserved"] = newBytes-bytes;

    file->WriteJson(temp, path + "/metadata.json");

}
/**
 * @brief Read one book with or without parity
 * @param name strings name of file
 * @return string
 */

string NodeController::ReadBook(string name) {

    if(this->activeDisk1 && this->activeDisk2){
        return WithoutParity(name);
    } else if(this->activeDisk2 == 0){
        return ParityDisj2(name);
    } else {
        return ParityDisk1(name);
    }

}

/**
 * @brief Read alls file in raid
 * @param name string, names of files
 * @return json object
 */

json NodeController::ReadRaid(string name) {

    json obj = file->ReadJson(path3 + "/metadata.json");

    json temp;

    int size = obj["amount"].get<int>();
    int newSize = 0;

    for (int i = 0; i < size; ++i) {

        if(CheckMemory(name, obj["Archivos"][to_string(i)]["name"].get<string>())){
            string data = ReadBook(obj["Archivos"][to_string(i)]["name"].get<string>());
            temp[to_string(i)]["name"] = obj["Archivos"][to_string(i)]["name"].get<string>();
            temp[to_string(i)]["data"] = data;
            newSize++;
        }

    }

    temp["size"] = newSize;

    return temp;
}

/**
 * @brief read book without parity
 * @param name string name of file
 * @return string
 */

string NodeController::WithoutParity(string name) {

    string firstPart = file->Read(path1 + "/" + name + ".txt");
    string secondPart = file->Read(path2 + "/" + name + ".txt");

    string textComplete = firstPart + secondPart;

    textComplete = converter->GenerateString(converter->BytesToChar(converter->GetBytesChar(textComplete)));

    return textComplete;

}
/**
 * @brief read book with parity
 * @param name string name of file
 * @return string
 */

string NodeController::ParityDisk1(string name) {

    string firstPart = file->Read(path3 + "/" + name + ".txt");
    string secondPart = file->Read(path2 + "/" + name + ".txt");

    firstPart = converter->GetDisk(firstPart,secondPart);

    string textComplete = firstPart + secondPart;

    textComplete = converter->GenerateString(converter->BytesToChar(converter->GetBytesChar(textComplete)));

    return textComplete;

}

/**
 * @brief read book with parity
 * @param name string name of file
 * @return string
 */

string NodeController::ParityDisj2(string name) {

    string firstPart = file->Read(path1 + "/" + name + ".txt");
    string secondPart = file->Read(path3 + "/" + name + ".txt");

    secondPart = converter->GetDisk(firstPart,secondPart);

    string textComplete = firstPart + secondPart;

    textComplete = converter->GenerateString(converter->BytesToChar(converter->GetBytesChar(textComplete)));

    return textComplete;

}

/**
 * @brief Check if the name of file have name searched
 * @param search
 * @param name
 * @return boolean
 */

bool NodeController::CheckMemory(string search, string name) {

    auto check = name.find(search);

    if(check != string::npos){
        return 1;
    } else {
        return 0;
    }

}
/**
 * @brief Check free space in disk
 * @return json object
 */

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

/**
 * @brief change disk1
 * @return bool
 */

bool NodeController::ChangeDisk1() {

    this->activeDisk2 = true;

    this->activeDisk1 = !this->activeDisk1;

    return this->activeDisk1;

}

/**
 * @brief change disk2
 * @return bool
 */

bool NodeController::ChangeDisk2() {

    this->activeDisk1 = true;

    this->activeDisk2 = !this->activeDisk2;

    return this->activeDisk2;
}