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

int TimUCLN(int a, int b) //tim ucln 
{
	int ucln;
	a = a < 0 ? -a : a;
	b = b < 0 ? -b : b;
	if (a == 0 || b == 0) {
		ucln = a + b;
	}
	else {
		while (a != b)
		{
			if (a > b)
				a -= b;
			else
				b -= a;
		}
		ucln = a;
	}
	return ucln;
}

void RutGon(PHANSO& ps) //rut gon phan so bang cach chia cho ucln
{
	int ucln = TimUCLN(ps.ts, ps.ms);
	if (ucln > 0) {
		ps.ts /= ucln;
		ps.ms /= ucln;
	}

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

istream& operator>>(istream& is, PHANSO& ps) //gan chong toan tu >> de cin ps de hon
{
	Nhap(ps);
	return is;
}

ostream& operator<<(ostream& os, PHANSO ps) //gan chong toan tu << de cout ps de hon
{
	Xuat(ps);
	return os;
}

PHANSO operator+(PHANSO ps1, PHANSO ps2) //gan chong toan tu + de cong ps de hon
{
	PHANSO pstong;
	pstong.ts = ps1.ts * ps2.ms + ps2.ts * ps1.ms;
	pstong.ms = ps1.ms * ps2.ms;
	RutGon(pstong);
	return pstong;
}

PHANSO operator-(PHANSO ps1, PHANSO ps2) //gan chong toan tu - de tru ps de hon
{
	PHANSO pshieu;
	pshieu.ts = ps1.ts * ps2.ms - ps2.ts * ps1.ms;
	pshieu.ms = ps1.ms * ps2.ms;
	RutGon(pshieu);
	return pshieu;
}

PHANSO operator*(PHANSO ps1, PHANSO ps2) //gan chong toan tu * de nhan ps de hon
{
	PHANSO pstich;
	pstich.ts = ps1.ts * ps2.ts;
	pstich.ms = ps1.ms * ps2.ms;
	RutGon(pstich);
	return pstich;
}

PHANSO operator/(PHANSO ps1, PHANSO ps2) //gan chong toan tu / de chia ps de hon
{
	PHANSO psthuong;
	psthuong.ts = ps1.ts * ps2.ms;
	psthuong.ms = ps1.ms * ps2.ts;
	RutGon(psthuong);
	return psthuong;
}

void main()
{
	PHANSO ps1, ps2;
	KhoiTao(ps1);
	KhoiTao(ps2);
	cout << "Nhap 2 phan so: \n";
	cin >> ps1 >> ps2;
	cout << ps1 << " + " << ps2 << " = " << ps1 + ps2 << endl;
	cout << ps1 << " - " << ps2 << " = " << ps1 - ps2 << endl;
	cout << ps1 << " * " << ps2 << " = " << ps1 * ps2 << endl;
	cout << ps1 << " : " << ps2 << " = " << ps1 / ps2;
}
