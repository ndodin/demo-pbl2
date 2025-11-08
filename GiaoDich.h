#pragma once
#include <string>
#include "MyVector.h"
#include "ChiTietGD.h"
using namespace std;

class GiaoDich {
private:
    string thoiGian;
    string maGD;
    MyVector<ChiTietGD> danhSachChiTiet;
    long long tongTien;
    long long tongSoDu;

    string taoMaGD(const string& time) {
        if (time.size() != 10) return "";
        return time.substr(0,4) + time.substr(5,2) + time.substr(8,2);
    }
public:
    GiaoDich() : tongTien(0.0) {}
    GiaoDich(const string& time)
        : thoiGian(time), tongTien(0.0)
    {
        maGD = taoMaGD(time);
    }
    GiaoDich(const string& _thoiGian, const string& _maGD, long long _tongTien, long long _soDu)
    : thoiGian(_thoiGian), maGD(_maGD), tongTien(_tongTien), tongSoDu(_soDu) {}


    string getMaGD() const { return maGD; }
    string getThoiGian() const { return thoiGian; }
    long long getTongTien() const { return tongTien; }
    long long getTongSoDu() const {return tongSoDu;}
    int getSoLuongChiTiet() const { return danhSachChiTiet.get_size(); }
    const MyVector<ChiTietGD>& getDanhSachChiTiet() const { return danhSachChiTiet; }
    MyVector<ChiTietGD>& getDanhSachChiTiet() { return danhSachChiTiet; }

    void setThoiGian(string _tg) {thoiGian = _tg;}

    void capNhatTongTien() {
        tongTien = 0;
        for (size_t i = 0; i < danhSachChiTiet.get_size(); ++i) {
            danhSachChiTiet[i].capNhatSoDuVi(0);
            if (danhSachChiTiet[i].getDanhMuc()->getLoaiDM() == "Chi") {
                tongTien -= danhSachChiTiet[i].getSoTienGD();
            } else {
                tongTien += danhSachChiTiet[i].getSoTienGD();
            }
        }  
    }

    void tinhTongSoDu(const MyVector<Vi*>& dsVi) {
        tongSoDu = 0;
        for (size_t i = 0; i < dsVi.get_size(); ++i) {
            tongSoDu += dsVi[i]->getSoDu();
        }
    }
};

