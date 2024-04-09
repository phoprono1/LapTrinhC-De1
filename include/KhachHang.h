#ifndef KHACHHANG_H
#define KHACHHANG_H

#include <string>
#include <vector>

struct KhachHang {
    std::string maKH;
    double tongTien;

    KhachHang(const std::string& _maKH, double _tongTien);
};

std::vector<KhachHang> ThongKeNKHCoTongTienNhieuNhat(int N);

#endif // KHACHHANG_H
