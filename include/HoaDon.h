#ifndef HOADON_H
#define HOADON_H

#include <iostream>
#include <string>
#include <vector>

class HoaDon
{
private:
    std::string SoHD;
    std::string NgayBan;
    std::string MaKH;

public:
    HoaDon();
    HoaDon(const std::string &soHD, const std::string &ngayBan, const std::string &maKH);

    std::string GetSoHD() const;
    std::string GetNgayBan() const;
    std::string GetMaKH() const;

    void SetSoHD(const std::string &soHD);
    void SetNgayBan(const std::string &ngayBan);
    void SetMaKH(const std::string &maKH);

    void ThemHoaDon(const HoaDon &hoaDon);
    void SuaHoaDon(const std::string &soHD, const HoaDon &hoaDon);
    void XoaHoaDon(const std::string &soHD);
    std::vector<HoaDon> DocHoaDon();
    void GhiFileCSV(const std::vector<HoaDon> &danhSachHoaDon);
    void CRUDHoaDon();
};

#endif // HOADON_H
