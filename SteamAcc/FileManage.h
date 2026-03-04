#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

extern std::vector<std::string> Accounts;

void DeleteLine(int lineToDelete);
void WriteToFile(std::string write);
void ReadFromFile();
