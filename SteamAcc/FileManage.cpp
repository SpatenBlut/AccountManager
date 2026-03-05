#include "FileManage.h"

const std::string ACC_PATH = "E:\\data\\apps\\SteamAcc\\SteamAcc.txt";
const std::string STATUS_PATH = "E:\\data\\apps\\SteamAcc\\Status.txt";

std::vector<Account> Accounts;

void DeleteLine(int SkippLine) {

    Accounts.clear();
    std::string SteamAcc;
    std::string AccStatus;

    std::ifstream AccRead(ACC_PATH);
    std::ifstream StatusRead(STATUS_PATH);
    while (getline(AccRead, SteamAcc) && getline(StatusRead, AccStatus)) {
        if (!AccStatus.empty() && AccStatus.back() == '\r') {
            AccStatus.pop_back();
        }
        Account acc;
        acc.data = SteamAcc;
        acc.status = AccStatus;
        Accounts.push_back(acc);
    }
    AccRead.close();
    StatusRead.close();

    std::ofstream AccWrite(ACC_PATH);
    std::ofstream StatusWrite(STATUS_PATH);
    for (int i = 0; i < Accounts.size(); i++) {
        if (i != SkippLine) {
            AccWrite << Accounts[i].data << std::endl;
            StatusWrite << Accounts[i].status << std::endl;
        }
    }
    AccWrite.close();
    StatusWrite.close();
}

void WriteToFile(std::string write) {
    std::ofstream AccWrite(ACC_PATH, std::ios::app);
    AccWrite << write << std::endl;
    AccWrite.close();

    std::ofstream StatusWrite(STATUS_PATH, std::ios::app);
    StatusWrite << "unused" << std::endl;
    StatusWrite.close();
}

// Read all accs from file and push back into the acc vector
void ReadFromFile() {

    Accounts.clear();

    std::string SteamAcc;
    std::string AccStatus;
    std::ifstream AccRead(ACC_PATH);
    std::ifstream StatusRead(STATUS_PATH);

    while (getline(AccRead, SteamAcc) && getline(StatusRead, AccStatus)) {
        if (!AccStatus.empty() && AccStatus.back() == '\r') {
            AccStatus.pop_back();
        }
        Account acc;
        acc.data = SteamAcc;
        acc.status = AccStatus;
        Accounts.push_back(acc);
    }
    AccRead.close();
    StatusRead.close();
}

void UpdateStatus(int index, std::string newStatus) {
    Accounts[index].status = newStatus;
    std::ofstream StatusWrite(STATUS_PATH);
    for (int i = 0; i < Accounts.size(); i++) {
        StatusWrite << Accounts[i].status << std::endl;
    }
    StatusWrite.close();
}