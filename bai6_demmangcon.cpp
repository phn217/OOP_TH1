#include <iostream>
using namespace std;

void Nhap(int& n, int& m, int*& A, int*& B) //nhap so phan tu va cac phan tu cua hai mang
{
    cout << "Nhap so phan tu cua mang A: ";
    cin >> n;
    do {
        cout << "Nhap so phan tu cua mang B: ";
        cin >> m;
    } while (n > m);

    A = new int[n];
    B = new int[m];

    cout << "Nhap " << n << " phan tu cua mang A: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    cout << "Nhap " << m << " phan tu cua mang B : ";
    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }
}

int TimViTri(int A[], int n, int B[], int m, int vitri[]) 
{
    int dem = 0;
    for (int i = 0; i <= m - n; i++)  //dieu kien de A khong vuot qua gioi han cua B
    {
        bool khop = true;
        for (int j = 0; j < n; j++) {
            if (B[i + j] != A[j]) {
                khop = false;
                break;
            }
        }
        if (khop) 
        {
            vitri[dem] = i; //luu vi tri xuat hien cua mang A trong B
            dem++; //dem so lan xuat hien cua mang A trong B
        }
    }
    return dem;
}

void main() {
    int n, m;
    int* A = nullptr;
    int* B = nullptr;
    Nhap(n, m, A, B);

    int* vitri = new int[m];
    int solan = TimViTri(A, n, B, m, vitri);

    cout << "So lan xuat hien: " << solan << endl;
    if (solan > 0) {
        cout << "Cac vi tri bat dau: ";
        for (int i = 0; i < solan; i++) {
            cout << vitri[i] << " ";
        }
    }

    delete[] A;
    delete[] B;
    delete[] vitri;
}

