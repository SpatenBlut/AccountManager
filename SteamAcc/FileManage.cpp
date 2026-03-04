#include "FileManage.h"

std::vector<std::string> Accounts;

void DeleteLine(int SkippLine) {

    Accounts.clear();
    std::string SteamAcc;

    std::ifstream MyReadFile("SteamAcc.txt");
    while (getline(MyReadFile, SteamAcc)) {
        Accounts.push_back(SteamAcc); // store each line in vector
    }
    MyReadFile.close();

    std::ofstream MyFile("SteamAcc.txt");
    for (int i = 0; i < Accounts.size(); i++) {
        if (i != SkippLine) {
            MyFile << Accounts[i] << std::endl; // write line to file
        }
    }
    MyFile.close();
}

void WriteToFile(std::string write) {
    std::ofstream MyFile("SteamAcc.txt", std::ios::app);
    MyFile << write << std::endl;
    MyFile.close();
}

// Read all accs from file and push back into the acc vector
void ReadFromFile() {

    Accounts.clear();

    std::string SteamAcc;
    std::ifstream MyReadFile("SteamAcc.txt");

    while (getline(MyReadFile, SteamAcc)) {
        Accounts.push_back(SteamAcc);
    }
    MyReadFile.close();
}