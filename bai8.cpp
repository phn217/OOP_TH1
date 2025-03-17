#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>
#include <iomanip>
#include <sstream>
using namespace std;

struct CHUYENBAY {
    string ma;
    string ngay;
    string gio;
    string noidi;
    string noiden;
};

string VietHoaChuCaiDau(string str) //viet hoa chu cai dau cua moi tu trong noi di/den
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

string ToLowerCase(string str) //chuyen chuoi ve chu thuong
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
//chuyen ngay va gio thanh chuoi yyyymmddhhmm de so sanh de hon
string ChuyenDoiNgayGio(const string& ngay, const string& gio) 
{
    stringstream ss;
    ss << ngay.substr(6, 4) << ngay.substr(3, 2) << ngay.substr(0, 2) << gio.substr(0, 2) << gio.substr(3, 2);
    return ss.str();
}

bool LaMaHopLe(const string& ma) //kiem tra ma chuyen bay co toi da 5 ky tu (chu/so) khong
{
    return regex_match(ma, regex("^[A-Za-z0-9]{1,5}$"));
}

bool LaNamNhuan(int nam) // kiem tra nam nhuan
{
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

bool LaNgayHopLe(const string& ngay) //kiem tra ngay co ton tai va dung dinh dang khong
{
    regex ngayRegex("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\\d{4}$");
    if (!regex_match(ngay, ngayRegex)) {
        return false;
    }

    int ngayInt = stoi(ngay.substr(0, 2));
    int thangInt = stoi(ngay.substr(3, 2));
    int namInt = stoi(ngay.substr(6, 4));

    vector<int> ngayTrongThang = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (thangInt == 2 && LaNamNhuan(namInt)) {
        ngayTrongThang[2] = 29;
    }
    return ngayInt <= ngayTrongThang[thangInt];
}

bool LaGioHopLe(const string& gio) //kiem tra gio co ton tai va dung dinh dang khong
{
    return regex_match(gio, regex("^([01][0-9]|2[0-3]):[0-5][0-9]$"));
}

bool LaNoiHopLe(const string& noi) //kiem tra noi di/den co hop le khong
{
    return regex_match(noi, regex("^[A-Za-z\\ \\x20]{1,20}$"));
}

void Nhap(vector<CHUYENBAY>& ds) //nhap danh sach cac chuyen bay
{
    int soluong;
    cout << "Nhap so luong chuyen bay: ";
    cin >> soluong;
    cin.ignore();

    for (int i = 0; i < soluong; i++) {
        CHUYENBAY cb;
        cout << "\nNhap thong tin chuyen bay thu " << i + 1 << ":\n";

        cout << "Nhap ma chuyen bay: ";
        cin >> cb.ma;
        while (!LaMaHopLe(cb.ma)) {
            cout << "Ma khong hop le! Nhap lai: ";
            cin >> cb.ma;
        }

        cout << "Nhap ngay bay (dd/mm/yyyy): ";
        cin >> cb.ngay;
        while (!LaNgayHopLe(cb.ngay)) {
            cout << "Ngay khong hop le! Nhap lai: ";
            cin >> cb.ngay;
        }

        cout << "Nhap gio bay (hh:mm - 24 gio): ";
        cin >> cb.gio;
        while (!LaGioHopLe(cb.gio)) {
            cout << "Gio khong hop le! Nhap lai: ";
            cin >> cb.gio;
        }

        cin.ignore();
        cout << "Nhap noi di: ";
        getline(cin, cb.noidi);
        while (!LaNoiHopLe(cb.noidi)) {
            cout << "Noi di khong hop le! Nhap lai: ";
            getline(cin, cb.noidi);
        }

        cout << "Nhap noi den: ";
        getline(cin, cb.noiden);
        while (!LaNoiHopLe(cb.noiden)) {
            cout << "Noi den khong hop le! Nhap lai: ";
            getline(cin, cb.noiden);
        }

        cb.noidi = VietHoaChuCaiDau(cb.noidi);
        cb.noiden = VietHoaChuCaiDau(cb.noiden);
        ds.push_back(cb);
    }
}

void Xuat(const CHUYENBAY& cb) //xuat thong tin mot chuyen bay
{
    cout << "Ma: " << cb.ma
        << " | Ngay: " << cb.ngay
        << " | Gio: " << cb.gio
        << " | Noi di: " << cb.noidi
        << " | Noi den: " << cb.noiden << endl;
}

void HienThi(vector<CHUYENBAY>& ds) //xuat danh sach chuyen bay da sap xep
{
    sort(ds.begin(), ds.end(), [](const CHUYENBAY& a, const CHUYENBAY& b) {
        return ChuyenDoiNgayGio(a.ngay, a.gio) < ChuyenDoiNgayGio(b.ngay, b.gio);
        });

    cout << "Danh sach chuyen bay da sap xep:\n";
    for (const auto& cb : ds) {
        Xuat(cb);
    }
}

//tim va xuat chuyen bay theo ma/noi di/noi den
void TimKiem(const vector<CHUYENBAY>& ds, const string& tukhoa) 
{
    string tukhoaLower = ToLowerCase(tukhoa);
    bool timThay = false;

    for (const auto& cb : ds) {
        if (ToLowerCase(cb.ma).find(tukhoaLower) != string::npos ||
            ToLowerCase(cb.noidi).find(tukhoaLower) != string::npos ||
            ToLowerCase(cb.noiden).find(tukhoaLower) != string::npos) {
            Xuat(cb);
            timThay = true;
        }
    }
    if (!timThay) {
        cout << "Khong tim thay chuyen bay phu hop!" << endl;
    }
}
//tim va xuat chuyen bay theo noi di & ngay
void HienThiTheoNoiDi_Ngay(const vector<CHUYENBAY>& danhSach, string noi, string ngay) 
{
    bool timThay = false;
    transform(noi.begin(), noi.end(), noi.begin(), ::tolower);

    for (const auto& cb : danhSach) {
        string noidiThuong = cb.noidi;
        transform(noidiThuong.begin(), noidiThuong.end(), noidiThuong.begin(), ::tolower);
        if (noidiThuong == noi && cb.ngay == ngay) {
            Xuat(cb);
            timThay = true;
        }
    }
    if (!timThay) {
        cout << "Khong tim thay chuyen bay phu hop!\n";
    }
}
//dem so chuyen bay tu noi nay den noi khac
int DemCB(const vector<CHUYENBAY>& danhSach, const string& tu, const string& den) 
{
    int count = 0;
    string tuLower = ToLowerCase(tu);
    string denLower = ToLowerCase(den);

    for (const auto& cb : danhSach) {
        if (ToLowerCase(cb.noidi) == tuLower && ToLowerCase(cb.noiden) == denLower) {
            count++;
        }
    }
    return count;
}

void main() {
    vector<CHUYENBAY> ds;
    Nhap(ds);
    int chon;
    do {
        cout << "\nMENU:\n";
        cout << "1. Sap xep danh sach chuyen bay theo ngay va gio bay\n";
        cout << "2. Tim kiem chuyen bay theo ma, noi di hoac noi den\n";
        cout << "3. Hien thi danh sach chuyen bay theo noi di va ngay\n";
        cout << "4. Dem so chuyen bay theo noi di va noi den\n";
        cout << "0. Thoat\nChon: ";
        cin >> chon;
        cin.ignore();

        switch (chon) {
        case 1: {
            HienThi(ds);
            break;
        }
        case 2: {
            string tukhoa;
            cout << "Nhap ma, noi di hoac noi den: ";
            getline(cin, tukhoa);
            TimKiem(ds, tukhoa);
            break;
        }
        case 3: {
            string noi, ngay;
            cout << "Nhap noi di: ";
            getline(cin, noi);
            cout << "Nhap ngay: ";
            getline(cin, ngay);
            HienThiTheoNoiDi_Ngay(ds, noi, ngay);
            break;
        }
        case 4:
            string tu, den;
            cin.ignore();
            cout << "Nhap noi di: ";
            getline(cin, tu);
            cout << "Nhap noi den: ";
            getline(cin, den);
            cout << "So luong chuyen bay: " << DemCB(ds, tu, den) << "\n";
            break;
        }
    } while (chon != 0);
}
