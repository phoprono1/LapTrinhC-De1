#include "include/ChiTietHD.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "include/HoaDon.h"
#include "include/SanPham.h"
#include <unordered_map>

ChiTietHD::ChiTietHD() {}

ChiTietHD::ChiTietHD(const std::string &soHD, const std::string &maSP, int soLuong, double giaBan)
    : SoHD(soHD), MaSP(maSP), SoLuong(soLuong), GiaBan(giaBan) {}

std::string ChiTietHD::GetSoHD() const
{
    return SoHD;
}

std::string ChiTietHD::GetMaSP() const
{
    return MaSP;
}

int ChiTietHD::GetSoLuong() const
{
    return SoLuong;
}

double ChiTietHD::GetGiaBan() const
{
    return GiaBan;
}

void ChiTietHD::SetSoHD(const std::string &soHD)
{
    SoHD = soHD;
}

void ChiTietHD::SetMaSP(const std::string &maSP)
{
    MaSP = maSP;
}

void ChiTietHD::SetSoLuong(int soLuong)
{
    SoLuong = soLuong;
}

void ChiTietHD::SetGiaBan(double giaBan)
{
    GiaBan = giaBan;
}

void ChiTietHD::ThemChiTietHD(const ChiTietHD &chiTietHD)
{
    std::vector<ChiTietHD> danhSachChiTietHD = DocChiTietHD();
    danhSachChiTietHD.push_back(chiTietHD);
    GhiFileCSV(danhSachChiTietHD);
}

void ChiTietHD::ThemChiTietHD()
{
    std::string soHD;
    std::string maSP;
    int soLuong;
    double giaBan;

    // Hiển thị danh sách số hóa đơn để người dùng chọn
    std::vector<std::string> danhSachSoHD = LayDanhSachSoHD();
    std::cout << "Danh sach So Hoa Don:" << std::endl;
    for (size_t i = 0; i < danhSachSoHD.size(); ++i)
    {
        std::cout << i + 1 << ". " << danhSachSoHD[i] << std::endl;
    }

    int luaChonSoHD;
    std::cout << "Chon So Hoa Don: ";
    std::cin >> luaChonSoHD;
    if (luaChonSoHD < 1 || luaChonSoHD > danhSachSoHD.size())
    {
        std::cerr << "Lua chon khong hop le." << std::endl;
        return;
    }
    soHD = danhSachSoHD[luaChonSoHD - 1];

    // Hiển thị danh sách mã sản phẩm để người dùng chọn
    std::vector<std::string> danhSachMaSP = LayDanhSachMaSP();
    std::cout << "Danh sach Ma San Pham:" << std::endl;
    for (size_t i = 0; i < danhSachMaSP.size(); ++i)
    {
        std::cout << i + 1 << ". " << danhSachMaSP[i] << std::endl;
    }

    int luaChonMaSP;
    std::cout << "Chon Ma San Pham: ";
    std::cin >> luaChonMaSP;
    if (luaChonMaSP < 1 || luaChonMaSP > danhSachMaSP.size())
    {
        std::cerr << "Lua chon khong hop le." << std::endl;
        return;
    }
    maSP = danhSachMaSP[luaChonMaSP - 1];

    // Nhập số lượng và giá bán
    std::cout << "Nhap so luong: ";
    std::cin >> soLuong;
    std::cout << "Nhap gia ban: ";
    std::cin >> giaBan;

    // Thêm chi tiết hóa đơn mới
    ChiTietHD chiTietHD(soHD, maSP, soLuong, giaBan);
    ThemChiTietHD(chiTietHD);
    std::cout << "Da them chi tiet hoa don." << std::endl;
}

void ChiTietHD::SuaChiTietHD(const std::string &soHD, const std::string &maSP, const ChiTietHD &chiTietHD)
{
    std::vector<ChiTietHD> danhSachChiTietHD = DocChiTietHD();

    for (auto &cthd : danhSachChiTietHD)
    {
        if (cthd.GetSoHD() == soHD && cthd.GetMaSP() == maSP)
        {
            cthd = chiTietHD;
            break;
        }
    }

    GhiFileCSV(danhSachChiTietHD);
}

void ChiTietHD::XoaChiTietHD(const std::string &soHD, const std::string &maSP)
{
    std::vector<ChiTietHD> danhSachChiTietHD = DocChiTietHD();

    auto it = std::remove_if(danhSachChiTietHD.begin(), danhSachChiTietHD.end(),
                             [soHD, maSP](const ChiTietHD &cthd)
                             { return cthd.GetSoHD() == soHD && cthd.GetMaSP() == maSP; });
    danhSachChiTietHD.erase(it, danhSachChiTietHD.end());

    GhiFileCSV(danhSachChiTietHD);
}

std::vector<ChiTietHD> ChiTietHD::DocChiTietHD()
{
    std::vector<ChiTietHD> danhSachChiTietHD;
    std::ifstream file("data/ChiTietHD.csv");

    if (!file.is_open())
    {
        std::cerr << "Khong the mo file ChiTietHD.csv" << std::endl;
        return danhSachChiTietHD;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string soHD, maSP, soLuongStr, giaBanStr;
        int soLuong;
        double giaBan;

        if (std::getline(iss, soHD, ',') && std::getline(iss, maSP, ',') &&
            std::getline(iss, soLuongStr, ',') && std::getline(iss, giaBanStr))
        {
            std::istringstream soLuongStream(soLuongStr);
            std::istringstream giaBanStream(giaBanStr);
            if (soLuongStream >> soLuong && giaBanStream >> giaBan)
            {
                danhSachChiTietHD.push_back(ChiTietHD(soHD, maSP, soLuong, giaBan));
            }
            else
            {
                std::cerr << "Loi doc du lieu tu file ChiTietHD.csv A" << std::endl;
            }
        }
        else
        {
            std::cerr << "Loi doc du lieu tu file ChiTietHD.csv B" << std::endl;
        }
    }

    file.close();
    return danhSachChiTietHD;
}

void ChiTietHD::HienThiChiTietHD(const std::vector<ChiTietHD> &danhSachChiTietHD)
{
    std::cout << "===== DANH SACH CHI TIET HOA DON =====" << std::endl;
    std::cout << std::setw(15) << "So HD" << std::setw(15) << "Ma SP" << std::setw(15) << "So Luong" << std::setw(15) << "Gia Ban" << std::endl;
    for (const auto &cthd : danhSachChiTietHD)
    {
        std::cout << std::setw(15) << cthd.GetSoHD() << std::setw(15) << cthd.GetMaSP() << std::setw(15) << cthd.GetSoLuong() << std::setw(15) << cthd.GetGiaBan() << std::endl;
    }
    std::cout << "=====================================" << std::endl;
}

void ChiTietHD::GhiFileCSV(const std::vector<ChiTietHD> &danhSachChiTietHD)
{
    std::ofstream file("data/ChiTietHD.csv");

    if (!file.is_open())
    {
        std::cerr << "Khong the mo file ChiTietHD.csv de ghi" << std::endl;
        return;
    }

    for (const auto &cthd : danhSachChiTietHD)
    {
        file << cthd.GetSoHD() << ',' << cthd.GetMaSP() << ',' << cthd.GetSoLuong() << ',' << cthd.GetGiaBan() << '\n';
    }

    file.close();
}

std::vector<std::string> ChiTietHD::LayDanhSachSoHD()
{
    std::vector<std::string> danhSachSoHD;
    HoaDon hoaDon;
    std::vector<HoaDon> danhSachHoaDon = hoaDon.DocHoaDon();

    for (const auto &hd : danhSachHoaDon)
    {
        danhSachSoHD.push_back(hd.GetSoHD());
    }

    return danhSachSoHD;
}

std::vector<std::string> ChiTietHD::LayDanhSachMaSP()
{
    std::vector<std::string> danhSachMaSP;
    SanPham sanPham;
    std::vector<SanPham> danhSachSanPham = sanPham.DocSanPham();

    for (const auto &sp : danhSachSanPham)
    {
        danhSachMaSP.push_back(sp.GetMaSP());
    }

    return danhSachMaSP;
}

std::vector<std::pair<std::string, int>> ChiTietHD::ThongKeNSanPhamNhieuNhat(int N)
{
    std::unordered_map<std::string, int> soLuongBan;

    // Đọc dữ liệu từ file ChiTietHD.csv và tính tổng số lượng bán của mỗi sản phẩm
    std::ifstream file("data/ChiTietHD.csv");
    if (!file.is_open())
    {
        std::cerr << "Khong the mo file ChiTietHD.csv" << std::endl;
        return {};
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string soHD, maSP, soLuongStr, giaBanStr;
        int soLuong;

        if (std::getline(iss, soHD, ',') &&
            std::getline(iss, maSP, ',') &&
            std::getline(iss, soLuongStr, ',') &&
            std::getline(iss, giaBanStr, ','))
        {
            std::istringstream soLuongStream(soLuongStr);
            if (soLuongStream >> soLuong)
            {
                soLuongBan[maSP] += soLuong; // Tính tổng số lượng bán của mỗi sản phẩm
            }
            else
            {
                std::cerr << "Loi doc du lieu tu file ChiTietHD.csv" << std::endl;
            }
        }
        else
        {
            std::cerr << "Loi doc du lieu tu file ChiTietHD.csv" << std::endl;
        }
    }

    file.close();

    // Chuyển dữ liệu từ unordered_map sang vector để sắp xếp
    std::vector<std::pair<std::string, int>> danhSachSanPham;
    for (const auto &kv : soLuongBan)
    {
        danhSachSanPham.emplace_back(kv.first, kv.second);
    }

    // Sắp xếp các sản phẩm theo số lượng bán giảm dần
    std::sort(danhSachSanPham.begin(), danhSachSanPham.end(), [](const auto &a, const auto &b)
              { return a.second > b.second; });

    // Lấy N sản phẩm có số lượng bán cao nhất
    std::vector<std::pair<std::string, int>> topNSanPham;
    for (int i = 0; i < std::min(N, static_cast<int>(danhSachSanPham.size())); ++i)
    {
        topNSanPham.push_back(danhSachSanPham[i]);
    }

    return topNSanPham;
}

void MenuChiTietHoaDon()
{
    std::cout << "===== MENU CHI TIET HOA DON =====" << std::endl;
    std::cout << "1. Them chi tiet hoa don" << std::endl;
    std::cout << "2. Sua chi tiet hoa don" << std::endl;
    std::cout << "3. Xoa chi tiet hoa don" << std::endl;
    std::cout << "4. Doc chi tiet hoa don" << std::endl;
    std::cout << "5. Thoat" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "Lua chon cua ban: ";
}

void ChiTietHD::CRUDChiTietHoaDon()
{
    ChiTietHD cthd;
    int luaChon;

    do
    {
        MenuChiTietHoaDon();
        std::cin >> luaChon;
        std::cin.ignore(); // Clear input buffer

        switch (luaChon)
        {
        case 1:
        {
            cthd.ThemChiTietHD();
            break;
        }
        case 2:
        {
            std::string soHD, maSP;
            int soLuong;
            double giaBan;

            std::cout << "Nhap so hoa don can sua: ";
            std::getline(std::cin, soHD);
            std::cout << "Nhap ma san pham can sua: ";
            std::getline(std::cin, maSP);
            std::cout << "Nhap so luong moi: ";
            std::cin >> soLuong;
            std::cout << "Nhap gia ban moi: ";
            std::cin >> giaBan;

            ChiTietHD newCTHD(soHD, maSP, soLuong, giaBan);
            cthd.SuaChiTietHD(soHD, maSP, newCTHD);
            std::cout << "Chi tiet hoa don da duoc sua." << std::endl;
            break;
        }
        case 3:
        {
            std::string soHD, maSP;
            std::cout << "Nhap so hoa don can xoa: ";
            std::getline(std::cin, soHD);
            std::cout << "Nhap ma san pham can xoa: ";
            std::getline(std::cin, maSP);
            cthd.XoaChiTietHD(soHD, maSP);
            std::cout << "Chi tiet hoa don da duoc xoa." << std::endl;
            break;
        }
        case 4:
        {
            // Hiển thị danh sách chi tiết hoá đơn
            std::vector<ChiTietHD> danhSachChiTietHD = cthd.DocChiTietHD();
            ChiTietHD::HienThiChiTietHD(danhSachChiTietHD);
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
