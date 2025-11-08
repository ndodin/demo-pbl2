#pragma once
#include <string>
using namespace std;

class Vi {
private:
    int maVi;
    string tenVi;
    long long soDu;
public:
    Vi() : maVi(0), tenVi(""), soDu(0){}
    Vi(int _id, const string& _ten, long long _sodu) 
        : maVi(_id), tenVi(_ten), soDu(_sodu) {}

    int getMaVi() const { return maVi; }
    string getTenVi() const { return tenVi; }
    long long getSoDu() const { return soDu; }

    void setSoDu(long long sodu) {soDu = sodu;}

    void congTien(long long tien) { soDu += tien; }
    void truTien(long long tien) { soDu -= tien; }
};
