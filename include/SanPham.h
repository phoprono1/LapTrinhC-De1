#ifndef SANPHAM_H
#define SANPHAM_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class SanPham
{
private:
    string MaSP;
    string TenSP;
    double TrongLuong;
    string QCDongGoi;

public:
    SanPham();
    SanPham(const string &maSP, const string &tenSP, double trongLuong, const string &qcDongGoi);

    string GetMaSP() const;
    string GetTenSP() const;
    double GetTrongLuong() const;
    string GetQCDongGoi() const;

    void SetMaSP(const string &maSP);
    void SetTenSP(const string &tenSP);
    void SetTrongLuong(double trongLuong);
    void SetQCDongGoi(const string &qcDongGoi);

    void ThemSanPham(const SanPham &sanPham);
    void SuaSanPham(const string &maSP, const SanPham &sanPham);
    void XoaSanPham(const string &maSP);
    void HienThiDanhSachSanPham();

    vector<SanPham> DocSanPham();

    void GhiFileCSV(const vector<SanPham> &danhSachSanPham);
    // Khai báo hàm CRUDSanPham
    void CRUDSanPham();
};

#endif // SANPHAM_H
