#include <iostream>
#include <limits>
#include "DataManager.h"
using namespace std;

int main() {
    DataManager dm;
    dm.setBasePath("D:/projects/finance_app/data/");
    dm.loadNguoiDung(dm.getBasePath() + "users.txt", dm.dsNguoiDung);
    NguoiDung* nd = nullptr;

    while (true) {
        int choice;
        cout << "==============================\n";
        cout << " 1. Dang nhap\n";
        cout << " 2. Dang ky\n";
        cout << " 0. Thoat\n";
        cout << "==============================\n";
        cout << "Chon: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string userID, ten, pass;

        if (choice == 1) {
            cout << "\nNhap ID nguoi dung: ";
            getline(cin, userID);
            cout << "Nhap mat khau: ";
            string pass = dm.AnMK();

            nd = dm.xacThuc(userID, pass);
            if (nd) {
                cout << "\n Dang nhap thanh cong! Xin chao " << nd->getTen() << "!\n";
                dm.loadDataNguoiDung(nd);
                break;
            }
            else {
                cout << "\n Sai tai khoan hoac mat khau.\n";
                cout << "\nNhan Enter de quay lai menu...";
                cin.get();
                system("cls");
                continue;
            }
        }
        else if (choice == 2) {
            cout << "\nNhap ID nguoi dung moi: ";
            getline(cin, userID);
            cout << "Nhap ten: ";
            getline(cin, ten);
            cout << "Nhap mat khau: ";
            string pass = dm.AnMK();

            if (dm.DangKy(userID, ten, pass)) {
                cout << "\n Dang ky thanh cong! Ban co the dang nhap ngay.\n";
                cout << "\nNhan Enter de quay lai menu...";
                cin.get();
                system("cls");
                continue;
            }
            else {
                cout << "\n ID nguoi dung da ton tai. Vui long chon ID khac.\n";
                cout << "\nNhan Enter de quay lai menu...";
                cin.get();
                system("cls");
                continue;
            }
        }
        else if (choice == 0) {
            cout << "Tam biet!\n";
            return 0;
        }
        else {
            cout << "Lua chon khong hop le.\n";
            cout << "\nNhan Enter de quay lai menu...";
            cin.get();
            system("cls");
            continue;
        }
    }

    // ====== MENU SAU KHI DANG NHAP ======
    int subChoice;
    do {
        cout << "\n==============================\n";
        cout << " 1. Xem danh sach vi\n"
             << " 2. Cap nhat so du vi\n"
             << " 3. Xem danh muc\n"
             << " 4. Thay doi mat khau\n"
             << " 5. Xoa tai khoan\n"
             << " 6. Them giao dich\n"
             << " 7. Xoa giao dich\n"
             << " 8. Dang xuat\n"
             << " 0. Thoat & luu du lieu\n";
        cout << "==============================\n";
        cout << "Chon: ";
        cin >> subChoice;
        cin.ignore();

        if (subChoice == 1) {
            cout << "\n--- DANH SACH VI ---\n";
            for (size_t i = 0; i < dm.dsVi.get_size(); ++i) {
                cout << dm.dsVi[i].getMaVi() << ". "
                    << dm.dsVi[i].getTenVi() << " . "
                    << dm.dsVi[i].getSoDu() << " VND\n";
            }
        }
        else if (subChoice == 2) { // Cập nhật số dư ví
            int maVi;
            long long soDu;
            cout << "\nNhap ma vi can cap nhat: ";
            cin >> maVi;
            cout << "Nhap so du moi: ";
            cin >> soDu;

            bool found = false;
            for (size_t i = 0; i < dm.dsVi.get_size(); ++i) {
                if (dm.dsVi[i].getMaVi() == maVi) {
                    dm.dsVi[i].setSoDu(soDu); // Cập nhật số dư mới
                    cout << "Da cap nhat so du vi!\n";
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Khong tim thay vi co ma " << maVi << "!\n";
            }
        }
        else if (subChoice == 3) {
            cout << "\n--- DANH MUC HIEN CO ---\n";
            for (size_t i = 0; i < dm.dsDanhMuc.get_size(); ++i) {
                DanhMuc* dmuc = dm.dsDanhMuc[i];
                cout << dmuc->getMaDM() << ". "
                    << dmuc->getTenDM() << " . "
                    << dmuc->getLoaiDM() << endl;
            }
        }
        //
        else if (subChoice == 4)
        {
            string userID = nd->getID();
            cout << "Nhap mat khau cu cua ban: ";
            string pass = dm.AnMK();
            int index = dm.KiemTraMK(userID, pass);
            if (index != -1)
            {
                string mk;
                cout << "Nhap lai mat khau moi cua ban: "; getline(cin, mk);
                if (dm.dsNguoiDung[index].getMatKhau() != mk)
                {
                    dm.DoiMK(index, mk);
                    cout << "Doi mat khau thanh cong!" << endl;
                }
                else
                {
                    cout << "Mat khau moi trung voi mat khau cu!";
                }
                dm.saveNguoiDung(dm.getBasePath() + "users.txt", dm.dsNguoiDung);
            }
            else
            {
                cout << "Sai mat khau, yeu cau bi huy bo!!" << endl;
                cout << "\nNhan Enter de quay lai menu...";
                cin.get();
                system("cls");
                continue;
            }
        }
        else if (subChoice == 5)
        {
            string userID = nd->getID();
            cout << "Nhap mat khau cua ban: ";
            string pass = dm.AnMK();
            int index = dm.KiemTraMK(userID, pass);
            if (index != -1)
            {
                char temp;
                cout << "Xac nhan xoa tai khoan!! (Y/N): "; 
                cin >> temp;
                if (temp == 'Y')
                {
                    dm.XoaTaiKhoan(index);
                }
                dm.saveNguoiDung(dm.getBasePath() + "users.txt", dm.dsNguoiDung);
                try {
                    if (fs::exists(dm.getBasePath() + "user_" + userID + "/"))
                    {
                        fs::remove_all(dm.getBasePath() + "user_" + userID + "/");
                        cout << "Da xoa thu muc " << endl;
                    }
                }
                catch (const std::exception& e) {
                    cout << "Loi khi xoa thu muc: " << e.what() << endl;
                }
            }
            else
            {
                cout << "Sai mat khau, yeu cau bi huy bo!!" << endl;
                cout << "\nNhan Enter de quay lai menu...";
                cin.get();
                system("cls");
                continue;
            }
        }
        //
        else if (subChoice == 0) {
            cout << "Dang thoat va luu du lieu...\n";
        }
        else {
            cout << "Lua chon khong hop le.\n";
        }
    } while (subChoice != 0);

    cout << "\n Dang luu du lieu..\n";
    dm.saveDataNguoiDung(nd);
    cout << " Luu du lieu thanh cong. Tam biet!\n";

    return 0;
}
