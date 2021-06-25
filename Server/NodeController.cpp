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




}