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

int TimUCLN(int a, int b) //tim ucln cua 2 so
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

void RutGon(PHANSO& ps) //rut gon ps bang cach chia ts va ms cho ucln
{
	int ucln = TimUCLN(ps.ts, ps.ms);
	if (ucln > 0) {
		ps.ts /= ucln;
		ps.ms /= ucln;
	}

}

void Xuat(PHANSO ps) //xuat ra gia tri nhin dep hon
{
	RutGon(ps);
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

void main()
{
	PHANSO ps;
	KhoiTao(ps);
	Nhap(ps);
	cout << "Phan so da rut gon la: ";
	Xuat(ps);
}