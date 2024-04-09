#include "include/KhachHang.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

KhachHang::KhachHang(const std::string& _maKH, double _tongTien) : maKH(_maKH), tongTien(_tongTien) {}

std::vector<KhachHang> ThongKeNKHCoTongTienNhieuNhat(int N)
{
    std::ifstream hoaDonFile("data/HoaDon.csv");
    std::ifstream chiTietHDFile("data/ChiTietHD.csv");

    std::unordered_map<std::string, double> tongTienKH; // Lưu tổng tiền của từng khách hàng

    // Đọc dữ liệu từ file ChiTietHD.csv và tính tổng tiền mỗi khách hàng
    std::string line;
    while (std::getline(chiTietHDFile, line))
    {
        std::istringstream iss(line);
        std::string soHD, maSP, soLuongStr, giaBanStr;
        int soLuong;
        double giaBan;

        if (std::getline(iss, soHD, ',') && std::getline(iss, maSP, ',') &&
            std::getline(iss, soLuongStr, ',') && std::getline(iss, giaBanStr, ','))
        {
            std::istringstream soLuongStream(soLuongStr);
            std::istringstream giaBanStream(giaBanStr);
            if (soLuongStream >> soLuong && giaBanStream >> giaBan)
            {
                // Tính tổng tiền cho từng mã khách hàng
                tongTienKH[soHD] += soLuong * giaBan;
            }
        }
    }

    // Đọc dữ liệu từ file HoaDon.csv để lấy mã khách hàng
    while (std::getline(hoaDonFile, line))
    {
        std::istringstream iss(line);
        std::string soHD, ngayBan, maKH;
        if (std::getline(iss, soHD, ',') && std::getline(iss, ngayBan, ',') && std::getline(iss, maKH, ','))
        {
            // Nếu tồn tại mã hoá đơn trong danh sách tổng tiền khách hàng
            if (tongTienKH.find(soHD) != tongTienKH.end())
            {
                // Lấy tổng tiền của mã hoá đơn và gán cho mã khách hàng tương ứng
                tongTienKH[maKH] += tongTienKH[soHD];
                // Xóa tổng tiền của mã hoá đơn để tránh trùng lặp
                tongTienKH.erase(soHD);
            }
        }
    }

    // Chuyển dữ liệu từ unordered_map sang vector để sắp xếp
    std::vector<KhachHang> danhSachKH;
    for (const auto &[maKH, tongTien] : tongTienKH)
    {
        danhSachKH.emplace_back(maKH, tongTien);
    }

    // Sắp xếp danh sách khách hàng theo tổng tiền mua hàng giảm dần
    std::sort(danhSachKH.begin(), danhSachKH.end(), [](const auto &a, const auto &b)
              { return a.tongTien > b.tongTien; });

    // Lấy N khách hàng có tổng tiền mua hàng nhiều nhất
    std::vector<KhachHang> topNKH;
    for (int i = 0; i < std::min(N, static_cast<int>(danhSachKH.size())); ++i)
    {
        topNKH.push_back(danhSachKH[i]);
    }

    return topNKH;
}

