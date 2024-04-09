#include "../include/BackUpMenu.h"
#include "../include/BackUp.h"
#include "../include/RecoveryData.h"
#include <iostream>

void BackupMenu::ShowMenu()
{
    int choice;
    do
    {
        std::cout << "--------------- Backup Menu ---------------" << std::endl;
        std::cout << "1. Sao lưu dữ liệu" << std::endl;
        std::cout << "2. Khôi phục dữ liệu" << std::endl;
        std::cout << "0. Thoát" << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
        std::cout << "Chọn tính năng (0-2): ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            {
                int choice;
                do
                {
                    Backup::ListCSVFiles();
                    choice = Backup::GetUserChoice(); // Chọn file sao lưu
                    vector<string> dataFiles = {"ChiTietHD.csv", "HoaDon.csv", "SanPham.csv"};
                    if (choice >= 1 && choice <= 3)
                    {
                        Backup::BackupData(dataFiles[choice - 1]);
                    }
                    else
                    {
                        cerr << "Lựa chọn không hợp lệ." << endl;
                    }
                } while (choice < 1 || choice > 3); // Lặp lại nếu lựa chọn không hợp lệ
                break;
            }
        case 2:
            {
                int subChoice;
                do
                {
                    RecoveryData::ListBackupFiles();
                    std::cout << "--------------- Khôi Phục Dữ Liệu ---------------" << std::endl;
                    
                    // Đếm số lượng file backup
                    int count = RecoveryData::CountBackupFiles();
                    if (count > 0) {
                        for (int i = 0; i < count; ++i) {
                            std::cout << i + 1 << ". Khôi Phục dữ liệu " << RecoveryData::GetBackupFileName(i) << std::endl;
                        }
                    } else {
                        std::cout << "Không có file backup nào." << std::endl;
                    }
                    
                    std::cout << "0. Quay lại" << std::endl;
                    std::cout << "-----------------------------------------------" << std::endl;
                    std::cout << "Chọn file muốn Khôi Phục(0-" << count << "): ";
                    std::cin >> subChoice;

                    if (subChoice >= 1 && subChoice <= count) {
                        RecoveryData::RecoveryDataFromBackup(RecoveryData::GetBackupFileName(subChoice - 1));
                    } else if (subChoice != 0) {
                        std::cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại!" << std::endl;
                    }
                } while (subChoice != 0);
                break;
            }
        case 0:
            std::cout << "Thoát khỏi Backup Menu." << std::endl;
            break;
        default:
            std::cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại!" << std::endl;
            break;
        }
    } while (choice != 0);
}
