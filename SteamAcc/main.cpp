#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>

std::vector<std::string> Accounts;

void DeleteFirstLine() {

    std::string SteamAcc;

    std::ifstream MyReadFile("SteamAcc.txt");

    while (getline(MyReadFile, SteamAcc)) {
        Accounts.push_back(SteamAcc); // store each line in vector
    }
    MyReadFile.close();

    std::ofstream("SteamAcc.txt"); // clear file content

    for (int i = 1; i < Accounts.size(); i++) {

        std::ofstream MyFile("SteamAcc.txt", std::ios::app); // open file without deleting content
        MyFile << Accounts[i] << std::endl; // write line to file

        MyFile.close();

    }
}

void WriteToFile(std::string write) {
    std::ofstream MyFile("SteamAcc.txt", std::ios::app);
    MyFile << write << std::endl;
    MyFile.close();
}

std::string ReadFromFile() {

    std::string SteamAcc;

    // Read from the text file
    std::ifstream MyReadFile("SteamAcc.txt");

    while (getline(MyReadFile, SteamAcc)) {
        std::cout << SteamAcc << std::endl;
    }

    // Close the file
    MyReadFile.close();
}

int main() {

    bool loop = true;
    bool inputValid = true;
    std::string input;
    std::string cmd;

    while (loop = true) {

        system("cls");
        std::cout << "---Steam Account Manager---" << std::endl;
        std::cout << "Commands: add, read, delete, exit" << std::endl;

        std::cin >> cmd;
        std::cin.ignore(); // to ignore the newline character after cmd input
        system("cls");

        if (cmd == "add") {

            while (inputValid = true) {

                std::cout << "q for exiting:\n";

                std::getline(std::cin, input);
                system("cls");

                if (input == "Q" || input == "q") {
                    break;
                }
                else {
                    WriteToFile(input);
                }
            }

            continue;
        }

        if (cmd == "read") {

            ReadFromFile();
            std::cin.get();

            continue;
            system("cls");
        }

        if (cmd == "delete") { // todo: choose line to delete

            std::cout << "First Account got deleted\n";
            DeleteFirstLine();
            std::cin.get();

            continue;
            system("cls");
        }

        if (cmd == "exit") {
            break;
        }

        else {
            std::cout << "Invalid command\n";
            continue;
        }
    }

    return 0;
}