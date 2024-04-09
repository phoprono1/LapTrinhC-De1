#include "include/BackUp.h"

void Backup::DisplayDataFiles()
{
    vector<string> dataFiles = {"HoaDon.csv", "SanPham.csv", "ChiTietHD.csv"};
    cout << "Danh sách các tệp dữ liệu:" << endl;
    for (size_t i = 0; i < dataFiles.size(); ++i)
    {
        cout << i + 1 << ". " << dataFiles[i] << endl;
    }
}

int Backup::GetUserChoice()
{
    int choice;
    cout << "Nhập tệp dữ liệu bạn muốn sao lưu: ";
    cin >> choice;
    return choice;
}

void Backup::BackupData(const string &fileName)
{
    fs::path filePath = "data/" + fileName;
    if (!fs::exists(filePath))
    {
        cerr << "File không tồn tại." << endl;
        return;
    }

    auto now = chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&now_c), "%Y-%m-%d_%H-%M-%S");
    string backupTime = ss.str();

    fs::path backupDir = "backup";
    if (!fs::exists(backupDir))
        fs::create_directory(backupDir);

    fs::path backupFilePath = backupDir / ("backup_" + backupTime + "_" + fileName);
    fs::copy(filePath, backupFilePath, fs::copy_options::overwrite_existing);
    cout << "Sao lưu thành công." << endl;
}

void Backup::ListCSVFiles()
{
    std::cout << "Danh sach cac tep CSV:\n";
    int count = 1;
    for (const auto &entry : fs::directory_iterator("data"))
    {
        if (entry.path().extension() == ".csv")
        {
            std::cout << count << ". " << entry.path().filename() << '\n';
            ++count;
        }
    }
}
