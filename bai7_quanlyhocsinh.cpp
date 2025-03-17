#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct HOCSINH {
    string hoten;
    float diemtoan, diemvan, diemanh, diemtb;
    string xeploai;
};

void TenHoa(string& ten) //chuan hoa ten thanh viet hoa chu cai dau
{
    bool viethoa = true;
    for (char& x : ten) {
        if (viethoa && isalpha(x)) {
            x = toupper(x);
            viethoa = false;
        }
        else {
            x = tolower(x);
        }
        if (x == ' ') viethoa = true;
    }
}

void Nhap(HOCSINH& hs) //nhap thong tin hoc sinh
{
    do {
        cout << "Nhap ho ten: ";
        getline(cin, hs.hoten);
        bool valid = true;
        for (char x : hs.hoten) {
            if (isdigit(x)) {
                valid = false;
                break;
            }
        }
        if (valid) break;
        cout << "Ho ten khong hop le. Nhap lai!\n";
    } while (true);

    TenHoa(hs.hoten);

    do {
        cout << "Nhap diem Toan: ";
        cin >> hs.diemtoan;
    } while (hs.diemtoan < 0 || hs.diemtoan > 10);

    do {
        cout << "Nhap diem Van: ";
        cin >> hs.diemvan;
    } while (hs.diemvan < 0 || hs.diemvan > 10);

    do {
        cout << "Nhap diem Anh: ";
        cin >> hs.diemanh;
    } while (hs.diemanh < 0 || hs.diemanh > 10);

    cin.ignore();
}

void XepLoai(HOCSINH& hs) //tinh dtb de xep loai hoc sinh
{
    hs.diemtb = (2 * hs.diemtoan + hs.diemvan + hs.diemanh) / 4;

    if (hs.diemtb >= 9) {
        hs.xeploai = "Xuat sac";
    }
    else if (hs.diemtb >= 8) {
        hs.xeploai = "Gioi";
    }
    else if (hs.diemtb >= 6.5) {
        hs.xeploai = "Kha";
    }
    else if (hs.diemtb >= 5) {
        hs.xeploai = "Trung binh";
    }
    else {
        hs.xeploai = "Yeu";
    }
}

void Xuat(const HOCSINH& hs) //xuat thong tin cua hoc sinh
{
    cout << "Ho ten: " << hs.hoten << "\n";
    cout << "Diem Toan: " << hs.diemtoan << "\n";
    cout << "Diem Van: " << hs.diemvan << "\n";
    cout << "Diem Ngoai ngu: " << hs.diemanh << "\n";
    cout << "Diem TB: " << hs.diemtb << "\n";
    cout << "Xep loai: " << hs.xeploai << "\n\n";
}

void TimKiem(HOCSINH* hs, int n)  //tim kiem hoc sinh bang tu khoa co trong ten
{
    string tuKhoa;
    bool timThay;
    do {
        cout << "\nNhap ten hoc sinh can tim: ";
        getline(cin, tuKhoa);
        transform(tuKhoa.begin(), tuKhoa.end(), tuKhoa.begin(), ::tolower);
        timThay = false;
        for (int i = 0; i < n; i++) {
            string ten = hs[i].hoten;
            transform(ten.begin(), ten.end(), ten.begin(), ::tolower);
            if (ten.find(tuKhoa) != string::npos) {
                Xuat(hs[i]);
                timThay = true;
            }
        }
        if (!timThay) cout << "Khong tim thay hoc sinh. Vui long nhap lai!\n";
    } while (!timThay);
}

void DiemCaoNhat(HOCSINH* hs, int n) //tim kiem va xuat thong tin hoc sinh co diem trung binh cao nhat
{
    float maxDiem = hs[0].diemtb;
    for (int i = 1; i < n; i++) {
        if (hs[i].diemtb > maxDiem) maxDiem = hs[i].diemtb;
    }
    cout << "Hoc sinh co diem trung binh cao nhat:\n";
    for (int i = 0; i < n; i++) {
        if (hs[i].diemtb == maxDiem) Xuat(hs[i]);
    }
}

void DiemToanThapNhat(HOCSINH* hs, int n) //tim kiem va xuat thong tin danh sach hoc sinh co diem toan thap nhat
{
    float min = hs[0].diemtoan;
    for (int i = 1; i < n; i++) {
        if (hs[i].diemtoan < min) min = hs[i].diemtoan;
    }
    cout << "Hoc sinh co diem Toan thap nhat:\n";
    for (int i = 0; i < n; i++) {
        if (hs[i].diemtoan == min) Xuat(hs[i]);
    }
}

void main() {
    int n;
    cout << "Nhap so luong hoc sinh: ";
    cin >> n;
    cin.ignore();

    HOCSINH* hs = new HOCSINH[n];
    for (int i = 0; i < n; i++) {
        cout << "\nNhap thong tin hoc sinh thu " << i + 1 << ":\n";
        Nhap(hs[i]);
        XepLoai(hs[i]);
    }

    cout << "\nDanh sach hoc sinh:\n";
    for (int i = 0; i < n; i++) Xuat(hs[i]);

    int chon;
    do {
        cout << "\nMENU:\n";
        cout << "1. Hien thi hoc sinh co diem trung binh cao nhat\n";
        cout << "2. Tim kiem hoc sinh theo ten\n";
        cout << "3. Hien thi danh sach hoc sinh co diem Toan thap nhat\n";
        cout << "0. Thoat\nChon: ";
        cin >> chon;
        cin.ignore();
        switch (chon) {
        case 1:
            DiemCaoNhat(hs, n);
            break;
        case 2:
            TimKiem(hs, n);
            break;
        case 3:
            DiemToanThapNhat(hs, n);
            break;
        case 0:
            cout << "Thoat chuong trinh.\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 0);
    delete[] hs;
}
