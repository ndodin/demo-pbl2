#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

void DataManager::setBasePath(const string& path) { basePath = path; }
string DataManager::getBasePath() const { return basePath; }

void DataManager::default_user_folder(const string& userFolder) {
   // file vi mac dinh
   ofstream fvi(userFolder + "vi.txt", ios::trunc);
   if (fvi.is_open()) {
       fvi << "1,Tien mat,0\n";
       fvi << "2,Ngan hang,0\n";
       fvi << "3,ShopeePay,0\n";
       fvi.close();
   }

   // file danh muc mac dinh
   ofstream fdm(userFolder + "danhmuc.txt", ios::trunc);
   if (fdm.is_open()) {
       fdm << "1,An uong,Chi\n";
       fdm << "2,Di lai,Chi\n";
       fdm << "3,Mua sam,Chi\n";
       fdm << "4,Luong,Thu\n";
       fdm << "5,Khac,Thu\n";
       fdm.close();
   }

   // tao file rong cho giao dich va chi tiet gd
   ofstream(userFolder + "giaodich.txt").close();
   ofstream(userFolder + "chitietgd.txt").close();
}

void DataManager::loadNguoiDung(const string& tenFile, MyVector<NguoiDung>& dsNguoiDung) {
   dsNguoiDung.clear();
   ifstream fin(tenFile);
   if (!fin.is_open()) return;
   string line;
   while (getline(fin, line)) {
       if (line.empty()) continue;
       stringstream ss(line);
       string id, ten, matKhau;
       getline(ss, id, ',');
       getline(ss, ten, ',');
       getline(ss, matKhau, ',');

       dsNguoiDung.push_back(NguoiDung(id, ten, matKhau));
   }
   fin.close();
}

void DataManager::loadVi(const string& tenFile, MyVector<Vi>& dsVi) {
   ifstream fin(tenFile);
   if (!fin.is_open()) return;
   string line;
   while (getline(fin, line)) {
       if (line.empty()) continue;
           stringstream ss(line);
           string maViStr, tenVi, soDuStr;
           getline(ss, maViStr, ','); int maVi = stoi(maViStr);
           getline(ss, tenVi, ',');
           getline(ss, soDuStr, ','); long long soDu = stoll(soDuStr);

       dsVi.push_back(Vi(maVi, tenVi, soDu));
   }
   fin.close();
}

void DataManager::loadDanhMuc(const string& tenFile, MyVector<DanhMuc*>& dsDanhMuc) {
   ifstream fin(tenFile);
   if (!fin.is_open()) return;
   string line;
   while (getline(fin, line)) {
       if (line.empty()) continue;
       stringstream ss(line);
       string maDMStr, tenDM, loaiDMStr;
       getline(ss, maDMStr, ','); int maDM = stoi(maDMStr);
       getline(ss, tenDM, ',');
       getline(ss, loaiDMStr, ','); string loaiDM = loaiDMStr;

       if (loaiDM == "Chi") {
           dsDanhMuc.push_back(new DanhMucChi(maDM, tenDM));
       } else if (loaiDM == "Thu") {
           dsDanhMuc.push_back(new DanhMucThu(maDM, tenDM));
       }
   }
   fin.close();
}

void DataManager::loadGiaoDich(const string& tenFile, MyVector<GiaoDich>& dsGiaoDich) {
   ifstream fin(tenFile);
   if (!fin.is_open()) return;
   string line;
   while (getline(fin, line)) {
       if (line.empty()) continue;
       stringstream ss(line);
       string thoiGian, maGD, tongTienStr;
       getline(ss, thoiGian, ',');
       getline(ss, maGD, ',');
       getline(ss, tongTienStr, ','); long long tongTien = stoll(tongTienStr);

       dsGiaoDich.push_back(GiaoDich(thoiGian,maGD,tongTien));
   }
   fin.close();
}

void DataManager::loadChiTietGD(const string& tenFile, MyVector<ChiTietGD*>& dsChiTietGD) {
   ifstream fin(tenFile);
   if (!fin.is_open()) return;
   string line;
   while (getline(fin, line)) {
       if (line.empty()) continue;
       stringstream ss(line);
       string maGD, maCTGDStr, maViStr, maDMStr, moTa, soTienGDStr;
       getline(ss, maGD, ',');
       getline(ss, maCTGDStr, ','); int maCTGD = stoi(maCTGDStr);
       getline(ss, maViStr, ','); int maVi = stoi(maViStr);
       getline(ss, maDMStr, ','); int maDM = stoi(maDMStr);
       getline(ss, moTa, ',');
       getline(ss, soTienGDStr, ','); long long soTienGD = stoll(soTienGDStr);

       dsChiTietGD.push_back(new ChiTietGD(maGD, maCTGD, maVi, maDM, moTa, soTienGD));

       /*for (auto& v : dsVi)
           if (v->getMaVi() == maVi) { viPtr = v; break; }

       for (auto& dm : dsDanhMuc)
           if (dm->getMaDM() == maDM) { dmPtr = dm; break; }

       if (viPtr && dmPtr) {
           dsChiTietGD.push_back(new ChiTietGD(maGD, maCTGD, viPtr, dmPtr, moTa, soTienGD, soDuVi));
       }


       dsChiTietGD.push_back(ct);*/
   }
   fin.close();
}

void DataManager::ganChiTietChoGiaoDich() {
    for (size_t i = 0; i < dsGiaoDich.get_size(); ++i) {
        GiaoDich& gd = dsGiaoDich[i];
        for (size_t j = 0; j < dsChiTietGD.get_size(); ++j) {
            ChiTietGD* ct = dsChiTietGD[j];
            if (ct->getMaGD() == gd.getMaGD()) {
                gd.getDanhSachChiTiet().push_back(*ct);
            }
        }
    }
}

void DataManager::saveNguoiDung(const string& tenFile, MyVector<NguoiDung>& dsNguoiDung){
       ofstream fout(tenFile, ios::trunc);
       if (!fout.is_open()) return;
       for(size_t i = 0; i < dsNguoiDung.get_size();i++){
           const NguoiDung& nd = dsNguoiDung[i];
           fout << nd.getID() << ","
                << nd.getTen() << ","
                << nd.getMatKhau();
           if(i<dsNguoiDung.get_size()-1) fout <<"\n";
       }
       fout.close();

   }
   void DataManager::saveVi(const string& tenFile, MyVector<Vi>& dsVi){
       ofstream fout(tenFile, ios::trunc);
       if (!fout.is_open()) return;
       for(size_t i = 0; i < dsVi.get_size();i++){
           const Vi& vi = dsVi[i];
           fout << vi.getMaVi() << ","
                << vi.getTenVi() << ","
                << vi.getSoDu();
           if(i<dsVi.get_size()-1) fout <<"\n";
       }
       fout.close();
   }
   void DataManager::saveDanhMuc(const string& tenFile, MyVector<DanhMuc*>& dsDanhMuc){
       ofstream fout(tenFile, ios::trunc);
       if (!fout.is_open()) return;
       for(size_t i = 0; i < dsDanhMuc.get_size();i++){
           const DanhMuc* dm = dsDanhMuc[i];
           fout << dm->getMaDM() << ","
                << dm->getTenDM() << ","
                << dm->getLoaiDM();
           if(i<dsDanhMuc.get_size()-1) fout <<"\n";
       }
       fout.close();
   }
   void DataManager::saveGiaoDich(const string& tenFile, MyVector<GiaoDich>& dsGiaoDich){
       ofstream fout(tenFile, ios::trunc);
       if (!fout.is_open()) return;
       for(size_t i = 0; i < dsGiaoDich.get_size();i++){
           const GiaoDich& gd = dsGiaoDich[i];
           fout << gd.getThoiGian() << ","
                << gd.getMaGD() << ","
                << gd.getTongTien();
           if(i<dsGiaoDich.get_size()-1) fout <<"\n";
       }
       fout.close();
   }
   void DataManager::saveChiTietGD(const string& tenFile, MyVector<ChiTietGD*>& dsChiTietGD){
       ofstream fout(tenFile, ios::trunc);
       if (!fout.is_open()) return;
       for(size_t i = 0; i < dsChiTietGD.get_size();i++){
           const ChiTietGD* ct = dsChiTietGD[i];
           fout << ct->getMaGD() << ","
                << ct->getMaCTGD() << ","
                << ct->getMaVi() << ","
                << ct->getMaDM() << ","
                << ct->getMoTa() << ","
                << ct->getSoTienGD();
           if(i<dsChiTietGD.get_size()-1) fout <<"\n";
       }
       fout.close();
   }

   NguoiDung* DataManager::xacThuc(const string& userid, const string& password){
       for(size_t i = 0; i < dsNguoiDung.get_size();i++){
           NguoiDung& nd = dsNguoiDung[i];
           if(nd.getID() == userid && nd.getMatKhau() == password){
               return &nd;
           }
       }
       return nullptr;
   }

   bool DataManager::DangKy(const string& userid, const string& name, const string& password){
       
    loadNguoiDung(basePath + "users.txt", dsNguoiDung);

       for(size_t i = 0; i < dsNguoiDung.get_size();i++){
           NguoiDung& nd = dsNguoiDung[i];
           if(nd.getID() == userid){
               //userid da ton tai
               return false;
           }
       }

       string userFolder = basePath + "user_" + userid + "/";
       if (fs::exists(userFolder)) return false;

       fs::create_directories(userFolder);
       default_user_folder(userFolder);

       dsNguoiDung.push_back(NguoiDung(userid, name, password));

       saveNguoiDung(basePath + "users.txt", dsNguoiDung);

       //cout <<"Dang ky thanh cong.\n" <<userFolder <<endl;
       return true;
   }

   bool DataManager::loadDataNguoiDung(NguoiDung* nd){

       string userFolder = basePath + "user_" + nd->getID() + "/";

       dsVi.clear();
       dsDanhMuc.clear();
       dsGiaoDich.clear();
       dsChiTietGD.clear();

       loadVi(userFolder + "vi.txt", dsVi);
       loadDanhMuc(userFolder + "danhmuc.txt", dsDanhMuc);
       loadGiaoDich(userFolder + "giaodich.txt", dsGiaoDich);
       loadChiTietGD(userFolder + "chitietgd.txt", dsChiTietGD);
        ganChiTietChoGiaoDich();
       return true;
   }

   bool DataManager::saveDataNguoiDung(NguoiDung* nd){
       string userFolder = basePath + "user_" + nd->getID() + "/";

       saveVi(userFolder + "vi.txt", dsVi);
       saveDanhMuc(userFolder + "danhmuc.txt", dsDanhMuc);
       saveGiaoDich(userFolder + "giaodich.txt", dsGiaoDich);
       saveChiTietGD(userFolder + "chitietgd.txt", dsChiTietGD);
       return true;
   }
    int DataManager::KiemTraMK(const string& userid, const string& password)
    {
    for (int i = 0; i < dsNguoiDung.get_size(); i++)
    {
        if (dsNguoiDung[i].getID() == userid)
        {
            return (dsNguoiDung[i].getMatKhau() == password) ? i : -1;
        }
    }
    return -1;
}

void DataManager::DoiMK(int index, const string& mk )
{
    dsNguoiDung[index].setMatKhau(mk);
}
void DataManager::XoaTaiKhoan(int index)
{
    dsNguoiDung.erase(index);
}

bool DataManager::themChiTietGD(const ChiTietGD& ctgd){
    ChiTietGD* newCtgd = new ChiTietGD(ctgd);
    Vi* viPtr = nullptr;
    for (size_t i = 0; i < dsVi.get_size(); ++i) {
        if (dsVi[i].getMaVi() == ctgd.getMaVi()) {
            viPtr = &dsVi[i];
            break;
        }
    }
    if (!viPtr) {
        cout << "Vi khong ton tai!\n";
        delete newCtgd;
        return false;
    }
    newCtgd->setVi(viPtr);
   
    DanhMuc* dmPtr = nullptr;
    for (size_t i = 0; i < dsDanhMuc.get_size(); ++i) {
        if (dsDanhMuc[i]->getMaDM() == ctgd.getMaDM()) {
            dmPtr = dsDanhMuc[i];
            break;
        }
    }
    if (!dmPtr) {
        cout << "Danh muc khong ton tai!\n";
        delete newCtgd;
        return false;
    }
    newCtgd->setDM(dmPtr);
    if (dmPtr->getLoaiDM() == "Chi") 
        viPtr->truTien(ctgd.getSoTienGD());
    else
        viPtr->congTien(ctgd.getSoTienGD());
    for(size_t i = 0; i < dsGiaoDich.get_size(); ++i) {
        if (dsGiaoDich[i].getMaGD() == ctgd.getMaGD()) {
            dsGiaoDich[i].getDanhSachChiTiet().push_back(*newCtgd);
            break;
        }
    }
    dsChiTietGD.push_back(newCtgd);
    return true;
}

MyVector<Vi*> DataManager::getDsViPtr() {
    MyVector<Vi*> out;
    for (size_t i = 0; i < dsVi.get_size(); ++i) {
        out.push_back(&dsVi[i]);
    }
    return out;
}