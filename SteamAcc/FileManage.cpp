#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FileManage.h"


std::vector<std::string> Accounts;

void DeleteFirstLine(int SkippLine) {

    std::string SteamAcc;

    std::ifstream MyReadFile("SteamAcc.txt");

    while (getline(MyReadFile, SteamAcc)) {
        Accounts.push_back(SteamAcc); // store each line in vector
    }
    MyReadFile.close();

    std::ofstream("SteamAcc.txt"); // clear file content

    for (int i = 0; i < Accounts.size(); i++) {

        std::ofstream MyFile("SteamAcc.txt", std::ios::app); // open file without deleting content

        if (i != SkippLine) {
            MyFile << Accounts[i] << std::endl; // write line to file
        }

        MyFile.close();

    }
}

void WriteToFile(std::string write) {
    std::ofstream MyFile("SteamAcc.txt", std::ios::app);
    MyFile << write << std::endl;
    MyFile.close();
}

void ReadFromFile() {

    std::string SteamAcc;

    // Read from the text file
    std::ifstream MyReadFile("SteamAcc.txt");

    int lineNumber = 1;
    while (getline(MyReadFile, SteamAcc)) {
        std::cout << lineNumber << ": " << SteamAcc << std::endl;
        lineNumber++;
    }

    // Close the file
    MyReadFile.close();
}