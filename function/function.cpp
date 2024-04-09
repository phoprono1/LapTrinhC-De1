#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <limits>

#include "../include/CRUDfunction.h"
#include "../include/BackupMenu.h"
#include "../include/ChiTietHD.h"

using namespace std;

void menu()
{
    int input;
    CRUDFunction crudFunction;
    BackupMenu backupMenu;
    ChiTietHD chiTietHD;
    int N;

    do
    {
        cout << "---------------Menu---------------" << endl;
        cout << "1. Lựa chọn bảng" << endl;
        cout << "2. Sao lưu và khôi phục dữ liệu" << endl;
        cout << "3. Tính toán Tổng tiền của một hoá đơn" << endl;
        cout << "4. Thống kê số Sản Phẩm bán nhiều nhất" << endl;
        cout << "5. Thống kê số Khách Hàng mua nhiều nhất" << endl;
        cin >> input;
        switch (input)
        {
        case 0:
            cout << "Thoát chương trình." << endl;
            break;
        case 1:
            crudFunction.CRUDMenu();
            break;
        case 2:
            backupMenu.ShowMenu();
            break;
        case 3:
            crudFunction.TinhTongTienHoaDon();
            break;
        case 4:
            cout << "Nhap so luong san pham ban nhieu nhat can thong ke: ";
            cin >> N;
            crudFunction.ThongKeNSanPhamNhieuNhat(N);
            break;
        case 5:
            cout << "Nhap so luong khach hang mua nhieu nhat can thong ke: ";
            cin >> N;
            crudFunction.ThongKeNKHMuaNhieuNhat(N);
            break;
        default:
            break;
        }

        // Xóa bộ nhớ đệm đầu vào sau mỗi lần nhập dữ liệu
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (input != 0);
}
