#pragma once
#include "DataManager.h"
#include <string>

class test {
private:
    DataManager dm;
    NguoiDung* nguoiDungHienTai = nullptr;

    // --- Menus ---
    void showLoginMenu();
    void showMainMenu();

    // --- Handlers ---
    void XuLyDangNhap();
    void XuLyDangKy();
    void XuLyThemGD();
    //void XuLyXemDSGD();
    //void XuLyXemThongKe();


    // --- Helpers ---
    int getIntInput(const std::string& prompt);
    std::string getStringInput(const std::string& prompt);
    //wait->enter
    //display danhsach
    void clearScreen();

public:
    test();
    void run();
};
