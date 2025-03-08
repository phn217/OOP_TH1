#include <iostream>
using namespace std;

struct PHANSO 
{
	int ts, ms;
};

void KhoiTao(PHANSO& ps) //khoi tao gia tri hop ly, don gian de tranh loi
{
	ps.ts = 0;
	ps.ms = 1;
}

void Nhap(PHANSO& ps) //nhap tu so va mau so (!= 0) cua phan so
{
	cout << "Nhap tu so: ";
	cin >> ps.ts;
	do
	{
		cout << "Nhap mau so khac 0: ";
		cin >> ps.ms;
	} while (ps.ms == 0);
}

void Xuat(PHANSO ps) //xuat ra gia tri nhin dep hon
{
	if (ps.ms < -1) {
		cout << -ps.ts << "/" << -ps.ms;
	}
	else if (ps.ms == -1) {
		cout << -ps.ts;
	}
	else if (ps.ms == 0) {
		cout << "Khong xac dinh";
	}
	else if (ps.ms == 1) {
		cout << ps.ts;
	}
	else {
		cout << ps.ts << "/" << ps.ms;
	}
}

istream& operator>>(istream& is, PHANSO& ps) //gan chong toan tu >>: de cin ps hon
{
	Nhap(ps);
	return is;
}

ostream& operator<<(ostream& os, PHANSO ps) //gan chong toan tu <<: de cout ps hon
{
	Xuat(ps);
	return os;
}

PHANSO SoSanh(PHANSO &ps1, PHANSO &ps2) //qui dong 2 ps de so sanh tu so va tra ve ps lon hon
{
	if (ps1.ts * ps2.ms > ps2.ts * ps1.ms) {
		cout << "Phan so lon hon la: " << ps1; 
		return ps1;
	}
	else if (ps1.ts* ps2.ms == ps2.ts * ps1.ms) {
		cout << "Hai phan so bang nhau va bang: " << ps1;
		return ps1;
	}
	else {
		cout << "Phan so lon hon la: " << ps2;
		return ps2;
	}
}


void main()
{
	PHANSO ps1, ps2;
	KhoiTao(ps1);
	KhoiTao(ps2);
	cout << "Nhap phan so thu 1\n";
	cin >> ps1;
	cout << "Nhap phan so thu 2\n";
	cin >> ps2;
	SoSanh(ps1, ps2);
}