#pragma once
#include <string>
#include "DanhMuc.h"
#include "Vi.h"
using namespace std;

class ChiTietGD {
private:
    string maGD;
    int maCTGD;
    int maVi;
    int maDM;
    string moTa;
    long long soTienGD;
    long long soDuVi;

    Vi* vi;
    DanhMuc* danhMuc;
public:
    ChiTietGD() 
        : maGD(""), maCTGD(0), maVi(0), maDM(0), moTa(""),
          soTienGD(0), soDuVi(0), vi(nullptr), danhMuc(nullptr) {}

    ChiTietGD(const string& _maGD, int _maCTGD, int _maVi, int _maDM,
              const string& _moTa, long long _soTienGD, long long _soDuVi)
        : maGD(_maGD), maCTGD(_maCTGD), maVi(_maVi), maDM(_maDM),
          moTa(_moTa), soTienGD(_soTienGD), soDuVi(_soDuVi),
          vi(nullptr), danhMuc(nullptr) {}
    
    string getMaGD() const { return maGD; }
    int getMaCTGD() const { return maCTGD; }
    int getMaVi() const { return maVi; }
    int getMaDM() const { return maDM; }
    string getMoTa() const { return moTa; }
    long long getSoTienGD() const { return soTienGD; }
    long long getSoDuVi() const { return soDuVi; }

    Vi* getVi() const { return vi; }
    DanhMuc* getDanhMuc() const { return danhMuc; }
    
    void setVi(Vi* _vi) { vi = _vi; }
    void setDM(DanhMuc* _dm) {danhMuc = _dm;}
    void setMota(string _mota) {moTa = _mota;}
    void setSoTienGD(long long _tien) {soTienGD = _tien;}

    void capNhatSoDuVi(long long delta) { 
        if (danhMuc->getLoaiDM() == "Chi") 
            vi->truTien(soTienGD);
        else 
            vi->congTien(soTienGD);
    }    
};
