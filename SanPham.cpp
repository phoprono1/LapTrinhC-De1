#include <algorithm>
#include <fstream>
#include <sstream>

#include "include/SanPham.h"
#include <iomanip>

SanPham::SanPham() {}

SanPham::SanPham(const string &maSP, const string &tenSP, double trongLuong, const string &qcDongGoi)
    : MaSP(maSP), TenSP(tenSP), TrongLuong(trongLuong), QCDongGoi(qcDongGoi) {}

string SanPham::GetMaSP() const
{
    return MaSP;
}

string SanPham::GetTenSP() const
{
    return TenSP;
}

double SanPham::GetTrongLuong() const
{
    return TrongLuong;
}

string SanPham::GetQCDongGoi() const
{
    return QCDongGoi;
}

void SanPham::SetMaSP(const string &maSP)
{
    MaSP = maSP;
}

void SanPham::SetTenSP(const string &tenSP)
{
    TenSP = tenSP;
}

void SanPham::SetTrongLuong(double trongLuong)
{
    TrongLuong = trongLuong;
}

void SanPham::SetQCDongGoi(const string &qcDongGoi)
{
    QCDongGoi = qcDongGoi;
}

void SanPham::ThemSanPham(const SanPham &sanPham)
{
    vector<SanPham> danhSachSanPham = DocSanPham();
    danhSachSanPham.push_back(sanPham);
    GhiFileCSV(danhSachSanPham);
}

void SanPham::SuaSanPham(const string &maSP, const SanPham &sanPham)
{
    vector<SanPham> danhSachSanPham = DocSanPham();

    for (auto &sp : danhSachSanPham)
    {
        if (sp.GetMaSP() == maSP)
        {
            sp = sanPham;
            break;
        }
    }

    GhiFileCSV(danhSachSanPham);
}

void SanPham::XoaSanPham(const string &maSP)
{
    vector<SanPham> danhSachSanPham = DocSanPham();

    auto it = remove_if(danhSachSanPham.begin(), danhSachSanPham.end(),
                        [maSP](const SanPham &sp)
                        { return sp.GetMaSP() == maSP; });
    danhSachSanPham.erase(it, danhSachSanPham.end());

    GhiFileCSV(danhSachSanPham);
}

vector<SanPham> SanPham::DocSanPham()
{
    vector<SanPham> danhSachSanPham;
    ifstream file("data/SanPham.csv");

    if (!file.is_open())
    {
        cerr << "Khong the mo file SanPham.csv" << endl;
        return danhSachSanPham;
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string maSP, tenSP, qcDongGoi, trongLuongStr; // Khai báo biến trongLuongStr ở đây
        double trongLuong;

        if (getline(iss, maSP, ',') &&
            getline(iss, tenSP, ',') &&
            getline(iss, trongLuongStr, ',') && // Sử dụng trongLuongStr ở đây
            getline(iss, qcDongGoi))
        {
            // Chuyển đổi trongLuong từ string sang double
            trongLuong = stod(trongLuongStr);
            danhSachSanPham.push_back(SanPham(maSP, tenSP, trongLuong, qcDongGoi));
        }
        else
        {
            cerr << "Loi doc du lieu tu file SanPham.csv" << endl;
        }
    }

    file.close();
    return danhSachSanPham;
}

void SanPham::GhiFileCSV(const vector<SanPham> &danhSachSanPham)
{
    ofstream file("data/SanPham.csv");

    if (!file.is_open())
    {
        cerr << "Khong the mo file SanPham.csv de ghi" << endl;
        return;
    }

    for (const auto &sp : danhSachSanPham)
    {
        file << sp.GetMaSP() << ',' << sp.GetTenSP() << ',' << sp.GetTrongLuong() << ',' << sp.GetQCDongGoi() << '\n';
    }

    file.close();
}

void SanPham::HienThiDanhSachSanPham()
{
    vector<SanPham> danhSachSanPham = DocSanPham();

    cout << "===== DANH SACH SAN PHAM =====" << endl;
    cout << setw(20) << "Ma SP" << setw(30) << "Ten SP" << setw(20) << "Trong Luong" << setw(30) << "Quy Cach Dong Goi" << endl;
    for (const auto &sp : danhSachSanPham)
    {
        cout << setw(20) << sp.GetMaSP() << setw(30) << sp.GetTenSP() << setw(20) << sp.GetTrongLuong() << setw(30) << sp.GetQCDongGoi() << endl;
    }
    cout << "===============================" << endl;
}

void MenuSanPham()
{
    cout << "===== MENU =====" << endl;
    cout << "1. Them san pham" << endl;
    cout << "2. Sua san pham" << endl;
    cout << "3. Xoa san pham" << endl;
    cout << "4. Doc san pham" << endl;
    cout << "5. Thoat" << endl;
    cout << "================" << endl;
    cout << "Lua chon cua ban: ";
}

void SanPham::CRUDSanPham()
{
    SanPham sp;
    int luaChon;

    do
    {
        MenuSanPham();
        cin >> luaChon;
        cin.ignore(); // Clear input buffer

        switch (luaChon)
        {
        case 1:
        {
            string maSP, tenSP, qcDongGoi;
            double trongLuong;

            cout << "Nhap ma san pham: ";
            getline(cin, maSP);
            cout << "Nhap ten san pham: ";
            getline(cin, tenSP);
            cout << "Nhap trong luong: ";
            cin >> trongLuong;
            cin.ignore(); // Clear input buffer
            cout << "Nhap quy cach dong goi: ";
            getline(cin, qcDongGoi);

            SanPham newSP(maSP, tenSP, trongLuong, qcDongGoi);
            sp.ThemSanPham(newSP);
            cout << "San pham da duoc them." << endl;
            break;
        }
        case 2:
        {
            string maSP, tenSP, qcDongGoi;
            double trongLuong;

            cout << "Nhap ma san pham can sua: ";
            getline(cin, maSP);
            cout << "Nhap ten san pham moi: ";
            getline(cin, tenSP);
            cout << "Nhap trong luong moi: ";
            cin >> trongLuong;
            cin.ignore(); // Clear input buffer
            cout << "Nhap quy cach dong goi moi: ";
            getline(cin, qcDongGoi);

            SanPham newSP(maSP, tenSP, trongLuong, qcDongGoi);
            sp.SuaSanPham(maSP, newSP);
            cout << "San pham da duoc sua." << endl;
            break;
        }
        case 3:
        {
            string maSP;
            cout << "Nhap ma san pham can xoa: ";
            getline(cin, maSP);
            sp.XoaSanPham(maSP);
            cout << "San pham da duoc xoa." << endl;
            break;
        }
        case 4:
        {
            // Hiển thị danh sách sản phẩm
            sp.HienThiDanhSachSanPham();
            break;
        }
        case 5:
            cout << "Thoat chuong trinh." << endl;
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    } while (luaChon != 5);
}
