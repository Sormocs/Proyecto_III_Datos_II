//
// Created by luis on 24/6/21.
//


#include "FileManager.h"

/**
 * @brief write txt
 * @param text data
 * @param path location
 */

void FileManager::Write(std::string text, std::string path) {

    std::ofstream ofs(path);
    if (ofs) {
        ofs << text << std::endl;
    }

}
/**
 * @brief Read txt
 * @param path location
 * @return string
 */

std::string FileManager::Read(std::string path) {

    std::string temp;

    std::ifstream openPort1;
    openPort1.open(path);
    openPort1 >> temp;

    return temp;

}

/**
 * @brief write .json
 * @param obj json
 * @param path location
 */

void FileManager::WriteJson(json obj, std::string path) {

    std::ofstream o(path);
    o << std::setw(4) << obj << std::endl;

}

/**
 * @brief Read .json
 * @param path location
 * @return json object
 */

json FileManager::ReadJson(std::string path) {

    std::ifstream i(path);
    json j;
    i >> j;

    return j;

}

/**
 * Generate xml file with params
 */

void FileManager::GenerateXML() {

    XMLDocument doc;

    doc.LinkEndChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));

    auto nodesElement = doc.NewElement("Nodes");

    auto node1Element = doc.NewElement("Node1");

    auto node1Ip = doc.NewElement("IP");
    node1Ip->SetText("127.0.0.1");
    node1Element->LinkEndChild(node1Ip);

    auto node1Port = doc.NewElement("Port");
    node1Port->SetText("5000");
    node1Element->LinkEndChild(node1Port);

    auto node1Path = doc.NewElement("Path");
    node1Path->SetText("../RAID/NODE1");
    node1Element->LinkEndChild(node1Path);

    nodesElement->LinkEndChild(node1Element);

    auto node2Element = doc.NewElement("Node2");

    auto node2Ip = doc.NewElement("IP");
    node2Ip->SetText("127.0.0.1");
    node2Element->LinkEndChild(node2Ip);

    auto node2Port = doc.NewElement("Port");
    node2Port->SetText("5001");
    node2Element->LinkEndChild(node2Port);

    auto node2Path = doc.NewElement("Path");
    node2Path->SetText("../RAID/NODE2");
    node2Element->LinkEndChild(node2Path);

    nodesElement->LinkEndChild(node2Element);

    auto node3Element = doc.NewElement("Node3");

    auto node3Ip = doc.NewElement("IP");
    node3Ip->SetText("127.0.0.1");
    node3Element->LinkEndChild(node3Ip);

    auto node3Port = doc.NewElement("Port");
    node3Port->SetText("5002");
    node3Element->LinkEndChild(node3Port);

    auto node3Path = doc.NewElement("Path");
    node3Path->SetText("../RAID/NODE3");
    node3Element->LinkEndChild(node3Path);

    nodesElement->LinkEndChild(node3Element);

    doc.LinkEndChild(nodesElement);

    doc.SaveFile("../RAID/parametros.xml");

}

/**
 * @brief Get ip from xml
 * @param node string
 * @return string
 */

string FileManager::GetIP(std::string node) {

    XMLDocument doc;
    doc.LoadFile("../RAID/parametros.xml");

    auto nodesElement = doc.FirstChildElement("Nodes");
    auto nodeElement = nodesElement->FirstChildElement(node.c_str());
    auto nodePort = nodeElement->FirstChildElement("IP");

    return nodePort->GetText();

}

/**
 * @brief Get port from xml
 * @param node string
 * @return string
 */

string FileManager::GetPort(std::string node) {

    XMLDocument doc;
    doc.LoadFile("../RAID/parametros.xml");

    auto nodesElement = doc.FirstChildElement("Nodes");
    auto nodeElement = nodesElement->FirstChildElement(node.c_str());
    auto nodePort = nodeElement->FirstChildElement("Port");

    return nodePort->GetText();
}

/**
 * @brief Get path from xml
 * @param node string
 * @return string
 */

string FileManager::GetPath(std::string node) {

    XMLDocument doc;
    doc.LoadFile("../RAID/parametros.xml");

    auto nodesElement = doc.FirstChildElement("Nodes");
    auto nodeElement = nodesElement->FirstChildElement(node.c_str());
    auto nodePort = nodeElement->FirstChildElement("Path");



    return nodePort->GetText();
}

/**
 * @brief delete .txt
 * @param path
 */

void FileManager::Delete(std::string path) {

    remove(path.c_str());

}