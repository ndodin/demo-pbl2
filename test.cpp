#include "test.h"
#include <iostream>
#include <limits>
#include <cstdlib> // system("cls")

using namespace std;

test::test() {
   dm.setBasePath("D:/projects/finance_app/data/");
   dm.loadNguoiDung(dm.getBasePath() + "users.txt", dm.dsNguoiDung);
}

void test::run() {
   while (true) {
       showLoginMenu();
   }
}

// ==================== MENUS ====================

void test::showLoginMenu() {
   cout << "==============================\n";
   cout << " QUAN LY CHI TIEU\n";
   cout << "==============================\n";
   cout << "1. Dang nhap\n";
   cout << "2. Dang ky\n";
   cout << "0. Thoat\n";
   cout << "==============================\n";
   int choice = getIntInput("Chon: ");

   switch (choice) {
   case 1:
       XuLyDangNhap();
       break;
   case 2:
       XuLyDangKy();
       break;
   case 0:
       cout << "Tam biet!\n";
       exit(0);
   default:
       cout << "Lua chon khong hop le.\n";
       break;
   }
}

void test::showMainMenu() {
   int subChoice;
   do {
       cout << "\n==============================\n";
       cout << " 1. Xem danh sach vi\n";
       cout << " 2. Cap nhat so du vi\n";
       cout << " 3. Xem danh muc\n";
       cout << " 4. Them giao dich\n";
       cout << " 5. Xem danh sach giao dich\n";
       cout << " 0. Dang xuat\n";
       cout << "==============================\n";
       cout << "Chon: ";
       cin >> subChoice;
       cin.ignore();
switch (subChoice) {
       case 1: {
           cout << "\n--- DANH SACH VI ---\n";
           for (size_t i = 0; i < dm.dsVi.get_size(); ++i) {
               cout << dm.dsVi[i].getMaVi() << " | "
                    << dm.dsVi[i].getTenVi() << " | "
                    << dm.dsVi[i].getSoDu() << " VND\n";
           }
           break;
        }
       case 2: {
           cout << "\n--- DANH SACH VI ---\n";
           for (size_t i = 0; i < dm.dsVi.get_size(); ++i) {
               cout << dm.dsVi[i].getMaVi() << " | "
                    << dm.dsVi[i].getTenVi() << " | "
                    << dm.dsVi[i].getSoDu() << " VND\n";
           }
           int maVi;
           long long soDu;
           cout << "\nNhap ma vi can cap nhat: ";
           cin >> maVi;
           cout << "Nhap so du moi: ";
           cin >> soDu;

           bool found = false;
           for (size_t i = 0; i < dm.dsVi.get_size(); ++i) {
               if (dm.dsVi[i].getMaVi() == maVi) {
                   dm.dsVi[i].setSoDu(soDu);
                   cout << "Da cap nhat so du vi!\n";
                   found = true;
                   break;
               }
           }

           if (!found)
               cout << "Khong tim thay vi co ma " << maVi << "!\n";
           break;
         }
       case 3: {
           cout << "\n--- DANH MUC ---\n";
           for (size_t i = 0; i < dm.dsDanhMuc.get_size(); ++i) {
               DanhMuc* dmuc = dm.dsDanhMuc[i];
               cout << dmuc->getMaDM() << " | "
                    << dmuc->getTenDM() << " | "
                    << dmuc->getLoaiDM() << endl;
           }
           break;
        }
        case 4: {
           cout << "\n--- THEM GIAO DICH ---\n";
           XuLyThemGD();
          
           break;
        }
       case 0: {
           cout << "Dang xuat va luu du lieu...\n";
           dm.saveDataNguoiDung(nguoiDungHienTai);
           nguoiDungHienTai = nullptr;
           clearScreen();
           return;
           break;
        }
       default:
           cout << "Lua chon khong hop le.\n";  
    }
    } while (subChoice != 0);
}

// ==================== HANDLERS ====================

void test::XuLyDangNhap() {
   clearScreen();
   cout << "--- DANG NHAP ---\n";
   string tenDangNhap = getStringInput("Ten dang nhap: ");
   string matKhau = getStringInput("Mat khau: ");

   nguoiDungHienTai = dm.xacThuc(tenDangNhap, matKhau);

   if (nguoiDungHienTai) {
       cout << "Dang nhap thanh cong! Xin chao, " << nguoiDungHienTai->getTen() << "!\n";
       dm.loadDataNguoiDung(nguoiDungHienTai);
       showMainMenu();
   } else {
       cout << "Sai ten dang nhap hoac mat khau.\n";
   }
}

void test::XuLyDangKy() {
   clearScreen();
   cout << "--- DANG KY ---\n";
   string tenDangNhap = getStringInput("Ten dang nhap: ");
   string tenHienThi = getStringInput("Ten hien thi: ");
   string matKhau = getStringInput("Mat khau: ");

   if (dm.DangKy(tenDangNhap, tenHienThi, matKhau)) {
       cout << "Dang ky thanh cong! Ban co the dang nhap ngay.\n";
   } else {
       cout << "Ten dang nhap da ton tai.\n";
   }
}

void test::XuLyThemGD() {
   clearScreen();
   cout << "--- THEM GIAO DICH ---\n";
   string tg = getStringInput("Nhap thoi gian giao dich (YYYY-MM-DD): ");

    GiaoDich gd(tg);
    string maGD = gd.getMaGD();

    int maCTGD = 1;
    while(true){
        cout << "---THEM CHI TIET GIAO DICH---\n";
        cout << "\nDanh sach vi:";
        for (size_t i = 0; i < dm.dsVi.get_size(); ++i) {
               cout << dm.dsVi[i].getMaVi() << " | "
                    << dm.dsVi[i].getTenVi() << " | "
                    << dm.dsVi[i].getSoDu() << " VND\n";
           }
        int maVi = getIntInput("Nhap ma vi: ");

        cout << "\nDanh sach danh muc:";
        for (size_t i = 0; i < dm.dsDanhMuc.get_size(); ++i) {
               DanhMuc* dmuc = dm.dsDanhMuc[i];
               cout << dmuc->getMaDM() << " | "
                    << dmuc->getTenDM() << " | "
                    << dmuc->getLoaiDM() << endl;
           }
        int maDM = getIntInput("Nhap ma danh muc: ");

        string moTa = getStringInput("Nhap mo ta: ");

        long long soTienGD = getIntInput("Nhap so tien giao dich: ");

        ChiTietGD ctgd(maGD, maCTGD, maVi, maDM, moTa, soTienGD, 0);
        dm.themChiTietGD(ctgd);
        maCTGD++;

        string ans = getStringInput("Them chi tiet giao dich khac? (y/n): ");
        if (ans != "n" && ans != "N") break;
    }
    gd.capNhatTongTien();
    gd.tinhTongSoDu(dm.getDsViPtr());
    dm.dsGiaoDich.push_back(gd);
    dm.saveDataNguoiDung(nguoiDungHienTai);
}

// ==================== HELPERS ====================

int test::getIntInput(const string& prompt) {
   int value;
   while (true) {
       cout << prompt;
       if (cin >> value) {
           cin.ignore(numeric_limits<streamsize>::max(), '\n');
           return value;
       } else {
           cout << "Nhap sai! Vui long nhap so.\n";
           cin.clear();
           cin.ignore(numeric_limits<streamsize>::max(), '\n');
       }
   }
}

string test::getStringInput(const string& prompt) {
   cout << prompt;
   string input;
   getline(cin, input);
   return input;
}

void test::clearScreen() {
#ifdef _WIN32
   system("cls");
#else
   system("clear");
#endif
}
