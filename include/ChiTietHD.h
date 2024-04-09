#ifndef CHITIETHD_H
#define CHITIETHD_H

#include <iostream>
#include <string>
#include <vector>

class ChiTietHD
{
private:
    std::string SoHD;
    std::string MaSP;
    int SoLuong;
    double GiaBan;

public:
    ChiTietHD();
    ChiTietHD(const std::string &soHD, const std::string &maSP, int soLuong, double giaBan);

    std::string GetSoHD() const;
    std::string GetMaSP() const;
    int GetSoLuong() const;
    double GetGiaBan() const;

    void SetSoHD(const std::string &soHD);
    void SetMaSP(const std::string &maSP);
    void SetSoLuong(int soLuong);
    void SetGiaBan(double giaBan);

    // Khai báo hàm thêm chi tiết hoá đơn
    void ThemChiTietHD(const ChiTietHD &chiTietHD);
    void ThemChiTietHD();
    // Khai báo hàm sửa chi tiết hoá đơn
    void SuaChiTietHD(const std::string &soHD, const std::string &maSP, const ChiTietHD &chiTietHD);
    // Khai báo hàm xóa chi tiết hoá đơn
    void XoaChiTietHD(const std::string &soHD, const std::string &maSP);
    // Khai báo hàm ghi vào file CSV
    void GhiFileCSV(const std::vector<ChiTietHD> &danhSachChiTietHD);
    // Khai báo hàm đọc từ file CSV
    std::vector<ChiTietHD> DocChiTietHD();
    void HienThiChiTietHD(const std::vector<ChiTietHD> &danhSachChiTietHD);

    void CRUDChiTietHoaDon();

    std::vector<std::string> LayDanhSachSoHD();
    std::vector<std::string> LayDanhSachMaSP();

    std::vector<std::pair<std::string, int>> ThongKeNSanPhamNhieuNhat(int N);

};

#endif // CHITIETHD_H
