#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct Account {
    std::string data;
    std::string status;
};
extern std::vector<Account> Accounts;

void DeleteLine(int lineToDelete);
void WriteToFile(std::string write);
void ReadFromFile();
void UpdateStatus(int index, std::string newStatus);
