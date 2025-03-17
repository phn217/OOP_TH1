#include <iostream>
using namespace std;

bool NamNhuan(int nam) //kiem tra nam nhuan
{
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

int SoNgay(int thang, int nam) //so ngay trong tung thang
{
    int ngaytrongthang[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (thang == 2 && NamNhuan(nam)) return 29;
    return ngaytrongthang[thang - 1];
}

void Nhap(int& ngay, int& thang, int& nam)
{
    do {
        cout << "Nhap ngay: ";
        cin >> ngay;
    } while (ngay < 1 || ngay > 31);

    do {
        cout << "Nhap thang: ";
        cin >> thang;
    } while (thang < 1 || thang > 12);

    cout << "Nhap nam: ";
    cin >> nam;

    do {
        if (ngay < 1 || ngay > SoNgay(thang, nam)) {
            cout << "Ngay khong hop le! Vui long nhap lai ngay: ";
            cin >> ngay;
        }
    } while (ngay < 1 || ngay > SoNgay(thang, nam));
}


void NgayKe(int& ngay, int& thang, int& nam) //tim ngay ke tiep
{
    if (ngay < SoNgay(thang, nam)) {
        ngay++;
    }
    else {
        ngay = 1;
        if (thang == 12) {
            thang = 1;
            nam++;
        }
        else {
            thang++;
        }
    }
}

void NgayTruoc(int& ngay, int& thang, int& nam) //tim ngay truoc do
{
    if (ngay > 1) {
        ngay--;
    }
    else {
        if (thang == 1) {
            thang = 12;
            nam--;
        }
        else {
            thang--;
        }
        ngay = SoNgay(thang, nam);
    }
}

int NgayBaoNhieu(int ngay, int thang, int nam) //tinh ngay thu bao nhieu trong nam
{
    int vitri = ngay;
    for (int i = 1; i < thang; i++) {
        vitri += SoNgay(i, nam);
    }
    return vitri;
}

void main() {
    int ngay, thang, nam;
    Nhap(ngay, thang, nam);

    int ngayke = ngay, thangke = thang, namke = nam;
    NgayKe(ngayke, thangke, namke);
    cout << "Ngay ke tiep: " << ngayke << "/" << thangke << "/" << namke << endl;

    int ngaytruoc = ngay, thangtruoc = thang, namtruoc = nam;
    NgayTruoc(ngaytruoc, thangtruoc, namtruoc);
    cout << "Ngay truoc do: " << ngaytruoc << "/" << thangtruoc << "/" << namtruoc << endl;

    cout << "Ngay thu " << NgayBaoNhieu(ngay, thang, nam) << " trong nam";
}
