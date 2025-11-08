#include <iostream>
#include "Vi.h"
#include "DanhMucChi.h"
#include "DanhMucThu.h"
#include "ChiTietGD.h"
#include "GiaoDich.h"
#include "MyVector.h"

using namespace std;

int main() {
    Vi tienMat(1, "Tien mat", 100000);
    Vi bidv(2, "BIDV", 200000);
    Vi shopee(3, "ShopeePay", 800000);

    DanhMucChi anUong(1, "An uong");
    DanhMucChi diLai(2, "Di lai");
    DanhMucThu luong(3, "Luong");
    DanhMucChi muaSam(4, "Mua sam");

    GiaoDich gd("2025/10/23");

    gd.getDanhSachChiTiet().push_back(
        ChiTietGD(1, &tienMat, &diLai, "xang", 50000, 0)
    );
    gd.getDanhSachChiTiet().push_back(

        ChiTietGD(2, &tienMat, &luong, "lam them", 100000, 0)
    );
    gd.getDanhSachChiTiet().push_back(
        ChiTietGD(3, &shopee, &muaSam, "ao khoac", 70000, 0)
    );

    gd.capNhatTongTien();

    cout << "Ma GD: " << gd.getMaGD() << endl;
    cout << "Tong tien giao dich: " << gd.getTongTien() << endl;

    cout << "So du cac vi sau giao dich:" << endl;
    cout << tienMat.getTenVi() << ": " << tienMat.getSoDu() << endl;
    cout << shopee.getTenVi() << ": " << shopee.getSoDu() << endl;
    cout << bidv.getTenVi() << ": " << bidv.getSoDu() << endl;

    return 0;
}
