#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>
#include <ctime>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <chrono>
using namespace std;

struct SOTIETKIEM {
    string ma;
    string loai;
    string ten;
    string cmnd;
    string ngaymo;
    long long sotien;
};
string VietHoaChuCaiDau(string str) //viet hoa chu cai dau moi tu trong chuoi
{
    bool viethoa = true;
    for (char& ch : str) {
        if (isalpha(ch)) {
            if (viethoa) {
                ch = toupper(ch);
            }
            else {
                ch = tolower(ch);
            }
            viethoa = false;
        }
        else if (ch == ' ') {
            viethoa = true;
        }
    }
    return str;
}
bool ChuyenVaKiemTraNgay(const string& ngay, tm& tm_ngay) //chuyen doi va kiem tra ngay hop le
{
    auto LaNamNhuan = [](int nam) {
        return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
    };
    regex ngayRegex("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\\d{4}$");
    if (!regex_match(ngay, ngayRegex)) {
        return false;
    }
    istringstream ss(ngay);
    ss >> get_time(&tm_ngay, "%d/%m/%Y");
    if (ss.fail()) return false;

    int ngayInt = tm_ngay.tm_mday;
    int thangInt = tm_ngay.tm_mon + 1;
    int namInt = tm_ngay.tm_year + 1900;

    vector<int> ngayTrongThang = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (thangInt == 2 && LaNamNhuan(namInt)) {
        ngayTrongThang[2] = 29;
    }
    return ngayInt <= ngayTrongThang[thangInt];
}
//so sanh ngay de xuat danh sach theo thu tu
bool SoSanhNgay(const string& ngay1, const string& ngay2) 
{
    tm tm_ngay1 = {}, tm_ngay2 = {};
    if (!ChuyenVaKiemTraNgay(ngay1, tm_ngay1) || !ChuyenVaKiemTraNgay(ngay2, tm_ngay2)) {
        return false;
    }
    return mktime(&tm_ngay1) < mktime(&tm_ngay2);
}
bool KiemTraMa(string ma) //kiem tra ma so co toi da 5 ky tu/so, khong ky tu dac biet
{
    return regex_match(ma, regex("^[a-zA-Z0-9]{1,5}$"));
}
bool KiemTraCMND(string cmnd) //kiem tra cmnd co 9 hoac 12 so
{
    return regex_match(cmnd, regex("^\\d{9}$|^\\d{12}$"));
}
void Nhap(vector<SOTIETKIEM>& ds) //nhap danh sach so tiet kiem & kiem tra du lieu dau vao
{
    int soluong;
    cout << "Nhap so luong so tiet kiem: ";
    cin >> soluong;
    cin.ignore();

    for (int i = 0; i < soluong; i++) {
        SOTIETKIEM stk;
        cout << "\nNhap thong tin so tiet kiem thu " << i + 1 << ":\n";

        do {
            cout << "Nhap ma so (toi da 5 ky tu, khong ky tu dac biet): ";
            cin >> stk.ma;
            cin.ignore();  // Loại bỏ ký tự xuống dòng trong bộ đệm
        } while (!KiemTraMa(stk.ma));

        cout << "Nhap loai tiet kiem (ngan han, dai han, khong ky han): ";
        getline(cin, stk.loai);

        do {
            cout << "Nhap ho ten (khong chua so hoac ky tu dac biet): ";
            getline(cin, stk.ten);
        } while (!regex_match(stk.ten, regex("^[a-zA-Z ]{1,30}$")));
        stk.ten = VietHoaChuCaiDau(stk.ten);

        do {
            cout << "Nhap CMND (9 hoac 12 so): ";
            cin >> stk.cmnd;
        } while (!KiemTraCMND(stk.cmnd));

        tm tmNgayMo;
        do {
            cout << "Nhap ngay mo so (dd/mm/yyyy): ";
            cin >> stk.ngaymo;
        } while (!ChuyenVaKiemTraNgay(stk.ngaymo, tmNgayMo));

        do {
            cout << "Nhap so tien gui (> 0, chi nhap so): ";
            string input;
            cin >> input;
            if (!regex_match(input, regex("^[0-9]+$"))) {
                cout << "So tien gui khong hop le. Vui long nhap lai!\n";
                continue;
            }
            stk.sotien = stoll(input);
            if (stk.sotien <= 0) {
                cout << "So tien gui phai lon hon 0. Vui long nhap lai!\n";
            }
        } while (stk.sotien <= 0);
        ds.push_back(stk);
    }
}
void Xuat(const vector<SOTIETKIEM>& ds) //xuat thong tin danh sach so
{
    for (const auto& stk : ds) {
        cout << "-------------------------------\n";
        cout << "Ma so: " << stk.ma << endl;
        cout << "Loai tiet kiem: " << stk.loai << endl;
        cout << "Ho ten: " << stk.ten << endl;
        cout << "CMND: " << stk.cmnd << endl;
        cout << "Ngay mo so: " << stk.ngaymo << endl;
        cout << "So tien gui: " << fixed << setprecision(0) << stk.sotien << " VND\n";
        cout << "-------------------------------\n";
    }
}
void TimKiem(const vector<SOTIETKIEM>& ds) //tim kiem so theo cmnd/ma/ten
{
    string key;
    cout << "Nhap tu khoa can tim (CMND, ma so, ho ten): ";
    cin.ignore();
    getline(cin, key);
    bool found = false;
    for (const auto& stk : ds) {
        if (stk.cmnd.find(key) != string::npos || stk.ma.find(key) != string::npos || stk.ten.find(key) != string::npos) {
            Xuat({ stk });
            found = true;
        }
    }
    if (!found) {
        cout << "Khong tim thay so tiet kiem!\n";
    }
}
//liet ke danh sach so trong khoang thoi gian duoc nhap vao
void LietKeTrongKhoangThoiGian(const vector<SOTIETKIEM>& ds) 
{
    string ngay_bat_dau, ngay_ket_thuc;
    tm ngayBatDau, ngayKetThuc;

    do {
        cout << "Nhap ngay bat dau (dd/mm/yyyy): ";
        cin >> ngay_bat_dau;
    } while (!ChuyenVaKiemTraNgay(ngay_bat_dau, ngayBatDau));

    do {
        cout << "Nhap ngay ket thuc (dd/mm/yyyy): ";
        cin >> ngay_ket_thuc;
    } while (!ChuyenVaKiemTraNgay(ngay_ket_thuc, ngayKetThuc));

    cout << "\nDanh sach so tiet kiem trong khoang thoi gian:\n";
    bool tim_thay = false;

    for (const auto& stk : ds) {
        if (SoSanhNgay(ngay_bat_dau, stk.ngaymo) && SoSanhNgay(stk.ngaymo, ngay_ket_thuc)) {
            Xuat({ stk });
            tim_thay = true;
        }
    }
    if (!tim_thay) {
        cout << "Khong tim thay so tiet kiem nao trong khoang thoi gian nay.\n";
    }
}
void SapXepTienGiamDan(vector<SOTIETKIEM>& ds) //sap xep danh sach so theo so tien giam dan
{
    sort(ds.begin(), ds.end(), [](const SOTIETKIEM& a, const SOTIETKIEM& b) {
        return a.sotien > b.sotien;
        });
    cout << "\nDanh sach sau khi sap xep theo tien gui giam dan:\n";
    Xuat(ds);
}
void SapXepNgayMoTangDan(vector<SOTIETKIEM>& ds) //sap xep danh sach so theo ngay mo tang dan
{
    sort(ds.begin(), ds.end(), [](const SOTIETKIEM& a, const SOTIETKIEM& b) {
        return SoSanhNgay(a.ngaymo, b.ngaymo);
        });
    cout << "\nDanh sach sau khi sap xep theo ngay mo so tang dan:\n";
    for (const auto& stk : ds) {
        Xuat({ stk });
    }
}
int TinhSoNgayGui(const string& ngaymo) //tinh so ngay da gui ke tu ngay mo so
{
    tm tm_ngaymo = {};
    if (!ChuyenVaKiemTraNgay(ngaymo, tm_ngaymo)) return -1;
    chrono::system_clock::time_point t_ngaymo = chrono::system_clock::from_time_t(mktime(&tm_ngaymo));
    chrono::system_clock::time_point t_now = chrono::system_clock::now();
    //tinh so ngay giua hai moc thoi gian
    auto duration = chrono::duration_cast<chrono::hours>(t_now - t_ngaymo).count() / 24;
    return static_cast<int>(duration);
}
void CapNhatLaiSuat(double& nganhan, double& daihan, double& khongkyhan) //nhap lai suat cho tung loai gui tiet kiem
{
    cout << "Nhap lai suat ngan han (%/nam): ";
    cin >> nganhan;
    cout << "Nhap lai suat dai han (%/nam): ";
    cin >> daihan;
    cout << "Nhap lai suat khong ky han (%/nam): ";
    cin >> khongkyhan;
    cout << "Lai suat da duoc cap nhat!\n";
}
double TinhLaiSuat(const SOTIETKIEM& stk, double nganhan, double daihan, double khongkyhan) //tinh lai suat cua nguoi gui
{
    int songaygui = TinhSoNgayGui(stk.ngaymo);
    if (songaygui < 0) return -1; 
    double laisuat;
    if (songaygui < 30) laisuat = khongkyhan / 100;
    else if (songaygui < 365) laisuat = nganhan / 100;
    else laisuat = daihan / 100;
    return stk.sotien * laisuat * songaygui / 365;
}

void XemTienLai(const vector<SOTIETKIEM>& ds, double nganhan, double daihan, double khongkyhan) //xem tien lai cua so
{
    for (const auto& stk : ds) {
        double tienLai = TinhLaiSuat(stk, nganhan, daihan, khongkyhan);
        cout << "-------------------------------\n";
        cout << "Ma so: " << stk.ma << "\nTien lai tinh den hien tai: " << fixed << setprecision(2) << tienLai << " VND\n";
        cout << "-------------------------------\n";
    }
}
//cho phep rut tien phu hop voi so du hien tai (da tinh lai suat)
void RutTien(vector<SOTIETKIEM>& ds, double nganhan, double daihan, double khongkyhan) 
{
    string ma;
    cout << "Nhap ma so tiet kiem can rut tien: ";
    cin >> ma;

    for (auto& stk : ds) {
        if (stk.ma == ma) {
            cout << "Nhap so tien muon rut: ";
            long long sotienRut;
            cin >> sotienRut;

            if (sotienRut > stk.sotien) {
                cout << "So tien rut vuot qua so du!\n";
                return;
            }
            double tienLai = TinhLaiSuat(stk, nganhan, daihan, khongkyhan);
            stk.sotien -= sotienRut;
            cout << "Rut thanh cong " << sotienRut << " VND. So du con lai: " << stk.sotien + tienLai << " VND\n";
            return;
        }
    }
    cout << "Khong tim thay so tiet kiem!\n";
}
void main() {
    vector<SOTIETKIEM> ds;
    Nhap(ds);
    int chon;
    double nganhan = 0.0;  
    double daihan = 0.0;
    double khongkyhan = 0.0;
    do {
        cout << "\nMENU:\n";
        cout << "1. Xuat thong tin danh sach cac so da nhap\n";
        cout << "2. Tim kiem so theo CMND hoac ma so\n";
        cout << "3. Liet ke cac so tiet kiem trong thoi gian nhat dinh\n";
        cout << "4. Sap xep danh sach so theo thu tu tien gui giam dan\n";
        cout << "5. Sap xep danh sach so theo thu tu ngay mo so tang dan\n";
        cout << "6. Cap nhat lai suat\n";
        cout << "7. Xem tien lai\n";
        cout << "8. Rut tien\n";
        cout << "0. Thoat\nChon: ";
        cin >> chon;
        cin.ignore();
        switch (chon) {
        case 1:
            cout << "\nDanh sach so tiet kiem:\n";
            Xuat(ds);
            break;
        case 2:
            TimKiem(ds);
            break;
        case 3:
            LietKeTrongKhoangThoiGian(ds);
            break;
        case 4:
            SapXepTienGiamDan(ds);
            break;
        case 5:
            SapXepNgayMoTangDan(ds);
            break;
        case 6:
            CapNhatLaiSuat(nganhan, daihan, khongkyhan);
            break;
        case 7:
            XemTienLai(ds, nganhan, daihan, khongkyhan);
            break;
        case 8:
            RutTien(ds, nganhan, daihan, khongkyhan);
            break;
        case 0:
            cout << "Thoat chuong trinh.\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 0);
}
