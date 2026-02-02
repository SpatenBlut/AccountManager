#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>
#include "FileManage.h"

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

        if (cmd == "delete") {


            ReadFromFile();

            int lineToDelete;
            std::cout << "select line to delete\n";
            std::cin >> lineToDelete;

            lineToDelete -= 1; // match vector index
            DeleteFirstLine(lineToDelete);
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