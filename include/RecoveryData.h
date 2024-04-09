#ifndef RECOVERYDATA_H
#define RECOVERYDATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class RecoveryData {
public:
    static void ListBackupFiles();
    static int GetUserChoice();
    static void RecoveryDataFromBackup(const std::string& backupFileName);
    static int CountBackupFiles();
    static std::string GetBackupFileName(int index);
};

#endif // RECOVERYDATA_H
