#include "../include/CRUDFunction.h"
#include "../include/SanPham.h"
#include "../include/HoaDon.h"
#include "../include/ChiTietHD.h"
#include "../include/KhachHang.h"
#include <limits>
#include <iomanip>

using namespace std;

void CRUDFunction::CRUDSanPham()
{
    SanPham sp;
    sp.CRUDSanPham();
}

void CRUDFunction::CRUDHoaDon()
{
    HoaDon hd;
    hd.CRUDHoaDon();
}

void CRUDFunction::CRUDChiTietHD()
{
    ChiTietHD cthd;
    cthd.CRUDChiTietHoaDon();
}

void CRUDFunction::TinhTongTienHoaDon()
{
    // Lấy danh sách chi tiết hóa đơn có số hóa đơn là soHD
    ChiTietHD chiTietHD;
    vector<ChiTietHD> danhSachChiTietHD = chiTietHD.DocChiTietHD();
    double tongTien = 0;

    chiTietHD.LayDanhSachSoHD();
    string soHD;
    cout << "Nhập số hóa đơn cần tính tổng tiền: ";
    cin >> soHD;
    // Duyệt qua danh sách chi tiết hóa đơn và tính tổng tiền
    for (const auto &cthd : danhSachChiTietHD)
    {
        if (cthd.GetSoHD() == soHD)
        {
            tongTien += cthd.GetSoLuong() * cthd.GetGiaBan();
        }
    }

    cout << "Tổng tiền của hóa đơn có số " << soHD << " là: " << tongTien << endl;
}

void CRUDFunction::ThongKeNSanPhamNhieuNhat(int N)
{
    ChiTietHD chiTietHD;
    std::vector<std::pair<std::string, int>> topNSanPham = chiTietHD.ThongKeNSanPhamNhieuNhat(N);
    std::cout << "===== " << N << " SAN PHAM BAN NHIEU NHAT =====" << std::endl;
    int count = 0; // Số lượng sản phẩm đã được xuất ra
    for (const auto &[maSP, soLuong] : topNSanPham)
    {
        std::cout << maSP << ": " << soLuong << " san pham" << std::endl;
        count++;
        if (count >= N)
            break;
    }
}

void CRUDFunction::ThongKeNKHMuaNhieuNhat(int N)
{
    auto topNKHMuaNhieuNhat = ThongKeNKHCoTongTienNhieuNhat(N);
    std::cout << "===== " << N << " KHACH HANG MUA NHIEU NHAT =====" << std::endl;
    int count = 0; // Số lượng khách hàng đã được xuất ra
    for (const auto &kh : topNKHMuaNhieuNhat)
    {
        std::cout << kh.maKH << ": " << std::fixed << std::setprecision(2) << kh.tongTien << std::endl;
        count++;
        if (count >= N)
            break;
    }
}

void CRUDFunction::CRUDMenu()
{
    int input;

    do
    {
        std::cout << "1. Hoa Don" << std::endl;
        std::cout << "2. Chi Tiet Hoa Don" << std::endl;
        std::cout << "3. San Pham" << std::endl;
        cin >> input;
        switch (input)
        {
        case 0:
            cout << "Thoát chương trình." << endl;
            break;

        case 1:
            CRUDHoaDon();
            break;

        case 2:
            CRUDChiTietHD();
            break;

        case 3:
            CRUDSanPham();
            break;

        default:
            break;
        }

    } while (input != 0);
}
