#include "include/HoaDon.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

HoaDon::HoaDon() {}

HoaDon::HoaDon(const std::string &soHD, const std::string &ngayBan, const std::string &maKH)
    : SoHD(soHD), NgayBan(ngayBan), MaKH(maKH) {}

std::string HoaDon::GetSoHD() const
{
    return SoHD;
}

std::string HoaDon::GetNgayBan() const
{
    return NgayBan;
}

std::string HoaDon::GetMaKH() const
{
    return MaKH;
}

void HoaDon::SetSoHD(const std::string &soHD)
{
    SoHD = soHD;
}

void HoaDon::SetNgayBan(const std::string &ngayBan)
{
    NgayBan = ngayBan;
}

void HoaDon::SetMaKH(const std::string &maKH)
{
    MaKH = maKH;
}

void HoaDon::ThemHoaDon(const HoaDon &hoaDon)
{
    std::vector<HoaDon> danhSachHoaDon = DocHoaDon();
    danhSachHoaDon.push_back(hoaDon);
    GhiFileCSV(danhSachHoaDon);
}

void HoaDon::SuaHoaDon(const std::string &soHD, const HoaDon &hoaDon)
{
    std::vector<HoaDon> danhSachHoaDon = DocHoaDon();

    for (auto &hd : danhSachHoaDon)
    {
        if (hd.GetSoHD() == soHD)
        {
            hd = hoaDon;
            break;
        }
    }

    GhiFileCSV(danhSachHoaDon);
}

void HoaDon::XoaHoaDon(const std::string &soHD)
{
    std::vector<HoaDon> danhSachHoaDon = DocHoaDon();

    danhSachHoaDon.erase(std::remove_if(danhSachHoaDon.begin(), danhSachHoaDon.end(),
                                        [soHD](const HoaDon &hd)
                                        { return hd.GetSoHD() == soHD; }),
                         danhSachHoaDon.end());
    GhiFileCSV(danhSachHoaDon);
}

std::vector<HoaDon> HoaDon::DocHoaDon()
{
    std::vector<HoaDon> danhSachHoaDon;
    std::ifstream file("data/HoaDon.csv");

    if (!file.is_open())
    {
        std::cerr << "Khong the mo file HoaDon.csv" << std::endl;
        return danhSachHoaDon;
    }

    std::string line;
    std::cout << "===== DANH SACH HOA DON =====" << std::endl;
    std::cout << std::setw(15) << "So HD" << std::setw(15) << "Ngay Ban" << std::setw(15) << "Ma KH" << std::endl;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string soHD, ngayBan, maKH;

        if (std::getline(iss, soHD, ',') && std::getline(iss, ngayBan, ',') && std::getline(iss, maKH, ','))
        {
            danhSachHoaDon.push_back(HoaDon(soHD, ngayBan, maKH));
            std::cout << std::setw(15) << soHD << std::setw(15) << ngayBan << std::setw(15) << maKH << std::endl;
        }
        else
        {
            std::cerr << "Loi doc du lieu tu file HoaDon.csv" << std::endl;
        }
    }

    file.close();
    std::cout << "===============================" << std::endl;
    return danhSachHoaDon;
}

void HoaDon::GhiFileCSV(const std::vector<HoaDon> &danhSachHoaDon)
{
    std::ofstream file("data/HoaDon.csv");

    if (!file.is_open())
    {
        std::cerr << "Khong the mo file HoaDon.csv de ghi" << std::endl;
        return;
    }

    for (const auto &hd : danhSachHoaDon)
    {
        file << hd.GetSoHD() << ',' << hd.GetNgayBan() << ',' << hd.GetMaKH() << '\n';
    }

    file.close();
}

void MenuHoaDon()
{
    std::cout << "===== MENU =====" << std::endl;
    std::cout << "1. Them hoa don" << std::endl;
    std::cout << "2. Sua hoa don" << std::endl;
    std::cout << "3. Xoa hoa don" << std::endl;
    std::cout << "4. Doc hoa don" << std::endl;
    std::cout << "5. Thoat" << std::endl;
    std::cout << "================" << std::endl;
    std::cout << "Lua chon cua ban: ";
}

void HoaDon::CRUDHoaDon()
{
    HoaDon hd;
    int luaChon;

    do
    {
        MenuHoaDon();
        std::cin >> luaChon;
        std::cin.ignore(); // Clear input buffer

        switch (luaChon)
        {
        case 1:
        {
            std::string soHD, ngayBan, maKH;

            std::cout << "Nhap so hoa don: ";
            std::getline(std::cin, soHD);
            std::cout << "Nhap ngay ban: ";
            std::getline(std::cin, ngayBan);
            std::cout << "Nhap ma khach hang: ";
            std::getline(std::cin, maKH);

            HoaDon newHD(soHD, ngayBan, maKH);
            hd.ThemHoaDon(newHD);
            std::cout << "Hoa don da duoc them." << std::endl;
            break;
        }
        case 2:
        {
            std::string soHD, ngayBan, maKH;

            std::cout << "Nhap so hoa don can sua: ";
            std::getline(std::cin, soHD);
            std::cout << "Nhap ngay ban moi: ";
            std::getline(std::cin, ngayBan);
            std::cout << "Nhap ma khach hang moi: ";
            std::getline(std::cin, maKH);

            HoaDon newHD(soHD, ngayBan, maKH);
            hd.SuaHoaDon(soHD, newHD);
            std::cout << "Hoa don da duoc sua." << std::endl;
            break;
        }
        case 3:
        {
            std::string soHD;
            std::cout << "Nhap so hoa don can xoa: ";
            std::getline(std::cin, soHD);
            hd.XoaHoaDon(soHD);
            std::cout << "Hoa don da duoc xoa." << std::endl;
            break;
        }
        case 4:
        {
            // Hiển thị danh sách hoá đơn
            hd.DocHoaDon();
            break;
        }
        case 5:
            std::cout << "Thoat chuong trinh." << std::endl;
            break;
        default:
            std::cout << "Lua chon khong hop le. Vui long chon lai." << std::endl;
        }
    } while (luaChon != 5);
}
