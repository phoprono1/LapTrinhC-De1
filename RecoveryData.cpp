#include "include/RecoveryData.h"

#include <filesystem>

void RecoveryData::ListBackupFiles() {
    std::cout << "Danh sach cac file backup co san:" << std::endl;

    // Đường dẫn đến thư mục backup
    std::filesystem::path backupFolder = "backup";

    // Kiểm tra xem thư mục backup có tồn tại không
    if (!std::filesystem::exists(backupFolder) || !std::filesystem::is_directory(backupFolder)) {
        std::cout << "Khong tim thay thu muc backup." << std::endl;
        return;
    }

    // Duyệt qua các file trong thư mục backup và hiển thị danh sách các file
    int count = 0;
    for (const auto& entry : std::filesystem::directory_iterator(backupFolder)) {
        if (entry.is_regular_file()) {
            std::cout << ++count << ". " << entry.path().filename() << std::endl;
        }
    }

    if (count == 0) {
        std::cout << "Khong co file backup nao." << std::endl;
    }
}

int RecoveryData::GetUserChoice() {
    int choice;
    std::cout << "Chon file backup muon khoi phuc: ";
    std::cin >> choice;
    return choice;
}

void RecoveryData::RecoveryDataFromBackup(const std::string& backupFileName) {
    // Trích xuất tên file gốc từ tên file backup
    size_t lastUnderscorePos = backupFileName.find_last_of("_");
    if (lastUnderscorePos == std::string::npos) {
        std::cerr << "Ten file backup khong hop le." << std::endl;
        return;
    }
    std::string originalFileName = backupFileName.substr(lastUnderscorePos + 1);

    // Kiểm tra xem file gốc đã tồn tại hay chưa
    if (std::filesystem::exists(originalFileName)) {
        std::cerr << "File " << originalFileName << " da ton tai. Ban co muon ghi de len no? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            std::cout << "Khong ghi de len file goc. Khoi phuc bi huy." << std::endl;
            return;
        }
    }

    // Mở file backup để đọc dữ liệu
    std::ifstream backupFile("backup/" + backupFileName);
    if (!backupFile.is_open()) {
        std::cerr << "Khong the mo file backup " << backupFileName << std::endl;
        return;
    }

    // Mở file data để ghi dữ liệu khôi phục
    std::ofstream dataFile("data/" + originalFileName);
    if (!dataFile.is_open()) {
        std::cerr << "Khong the mo file data " << originalFileName << " de ghi du lieu khôi phục." << std::endl;
        backupFile.close();
        return;
    }

    // Sao chép dữ liệu từ file backup sang file data
    dataFile << backupFile.rdbuf();

    // Đóng file backup và file data
    backupFile.close();
    dataFile.close();

    std::cout << "Da khoi phuc du lieu tu file backup " << "backup/" << backupFileName << " vao file " << "data/" << originalFileName << std::endl;
}

int RecoveryData::CountBackupFiles() {
    int count = 0;
    std::filesystem::path backupFolder = "backup";
    if (std::filesystem::exists(backupFolder) && std::filesystem::is_directory(backupFolder)) {
        for (const auto& entry : std::filesystem::directory_iterator(backupFolder)) {
            if (entry.is_regular_file()) {
                ++count;
            }
        }
    }
    return count;
}

std::string RecoveryData::GetBackupFileName(int index) {
    std::string fileName;
    std::filesystem::path backupFolder = "backup";
    if (std::filesystem::exists(backupFolder) && std::filesystem::is_directory(backupFolder)) {
        int count = 0;
        for (const auto& entry : std::filesystem::directory_iterator(backupFolder)) {
            if (entry.is_regular_file()) {
                if (count == index) {
                    fileName = entry.path().filename().string();
                    break;
                }
                ++count;
            }
        }
    }
    return fileName;
}