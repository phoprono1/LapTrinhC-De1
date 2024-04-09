#ifndef CRUDFUNCTION_H
#define CRUDFUNCTION_H

#include <iostream>
#include <vector>

class CRUDFunction
{
public:
    void CRUDMenu();
    void TinhTongTienHoaDon();
    void ThongKeNSanPhamNhieuNhat(int N);
    void ThongKeNKHMuaNhieuNhat(int N);

private:
    void CRUDSanPham();
    void CRUDHoaDon();
    void CRUDChiTietHD();
};

#endif // CRUDFUNCTION_H
