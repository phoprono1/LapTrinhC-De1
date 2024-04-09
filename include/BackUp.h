#ifndef BACKUP_H
#define BACKUP_H

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

namespace fs = std::filesystem;
using namespace std;

class Backup {
public:
    static void DisplayDataFiles();
    static int GetUserChoice();
    static void BackupData(const string& fileName);
    static void ListCSVFiles();
};

#endif // BACKUP_H
