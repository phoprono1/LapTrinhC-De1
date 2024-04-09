cmake_minimum_required(VERSION 3.5)

project(MyProject)

# Định nghĩa các biến chứa các file nguồn của bạn
set(SOURCES 
    main.cpp
    function/function.cpp
    function/CRUDfunction.cpp
    SanPham.cpp
    HoaDon.cpp
    ChiTietHD.cpp
    BackUp.cpp
    RecoveryData.cpp
    function/BackUpMenu.cpp
    KhachHang.cpp
)

# Thêm biên dịch cho tất cả các file nguồn
add_executable(main ${SOURCES})
