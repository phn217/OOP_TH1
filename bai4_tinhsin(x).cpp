#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double TinhSin(double x) { //ham tinh sin(x)
    double dochinhxac = 0.00001;
    double tong = x;
    double tu = x;
    double mau = 1;
    double dau = 1;

    for (int i = 1;; i++) {
        dau *= -1;
        tu *= x * x;
        mau *= (2 * i) * (2 * i + 1);
        double sohang = dau * (tu / mau);
        tong += sohang;
        if (fabs(sohang) < dochinhxac) break; //dung chuong trinh khi dat den do chinh xac mong muon
    }
    return tong;
}
void main() {
    double x;
    cout << "Nhap gia tri x: ";
    cin >> x;
    cout << setprecision(4) << "Gia tri sin(" << x << ") xap xi: " << TinhSin(x);
}
