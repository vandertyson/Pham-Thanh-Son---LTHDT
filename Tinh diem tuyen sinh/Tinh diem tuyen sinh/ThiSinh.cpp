#pragma warning(disable:4996);
#include "ThiSinh.h"
#include <fstream>
#include <iostream>
#include <boost\algorithm\string.hpp>
#include <vector>
using namespace std;
using namespace boost;
ThiSinh::ThiSinh()
{
	auto bangDiem = new double[13];
	auto diemNV = new double[4][14];
	auto diemXetTuyenNV = new double[4];
	diemCong = 0;
}

ThiSinh::~ThiSinh()
{
}
// tinh diem xet tuyen cho thi sinh
void ThiSinh::tinhDiem()
{
	tinhDiemCong();
	for (int i = 0; i < 4; i++)
	{
		double s;
		if (diemNV[i][3] == 1)
		{
			s = (diemNV[i][0] * 2 + diemNV[i][1] + diemNV[i][2]) / 4 + diemCong;
		}
		else
		{
			s = (diemNV[i][0] + diemNV[i][1] + diemNV[i][2]) / 3 + diemCong;
		}
		if (s >= 0) diemXetTuyenNV[i] = round(s*100.0) / 100.0;
		else diemXetTuyenNV[i] = -1;
	}
}
//trich xuat thong tin tu file dangky-nv.csv
void ThiSinh::layThongTin(int stt)
{
	fstream a;
	//a.open(R"(C:\Users\Son Pham\Desktop\OOP\dangkynv-bk.csv)", ios::in);
	a.open("dangkynv-bk.csv", ios::in);
	// tao mot 1 vector chua cac token lay dc
	std::vector<string> m;
	//tao 1 mang chua cac ki tu doc duoc tu dong
	char b[500] = "";
	//1 string de split
	string c;
	//doc vao den dung stt thi lay du lieu do ra
	for (int i = 1; i < 10000; i++)
	{
		a.getline(b, 500);
		if (i == stt+1)
		{
			break;
		}
	}
	// tokenise va luu token vao vecto
	boost::split(m, b, boost::is_any_of(","));
	// bo sung de vecto du 21 thanh phan
	int bu = 21 - m.size();
	if (bu > 0)
	{
		for (int i = 0; i < bu; i++)
		{
			m.insert(m.end(), "NA");
		}
	}
	// gan cac token thich hop vao thong tin thi sinh
	// nguyen vong
	soBaoDanh = boost::replace_all_copy(m[0], "\"", "");
	for (int k = 0, h = 1; k < 4; k++, h = h + 5)
	{
		nv[k] = boost::replace_all_copy(m[h], "\"", "");
	}
	// cac to hop mon
	int i, j;
	for (i = 0, j = 2; i < 12; i++, j++)
	{
		if (i == 3) { j += 2; toHop[i] = boost::replace_all_copy(m[j], "\"", ""); }
		else toHop[i] = boost::replace_all_copy(m[j], "\"", "");
		if (i == 6) { j += 2; toHop[i] = boost::replace_all_copy(m[j], "\"", ""); }
		else toHop[i] = boost::replace_all_copy(m[j], "\"", "");
		if (i == 9) { j += 2; toHop[i] = boost::replace_all_copy(m[j], "\"", ""); }
		else toHop[i] = boost::replace_all_copy(m[j], "\"", "");
	}
	// he so nhan
	for (i = 0, j = 5; i < 4; i++, j = j + 5)
	{
		if (boost::replace_all_copy(m[j], "\"", "") != "NA") diemNV[i][3] = stod(boost::replace_all_copy(m[j], "\"", ""));
		else diemNV[i][3] = 90;
		//cout << diemNV[i][3] << " ";
	}
}
//trich xuat thong tin tu file csdl-bk.csv
void ThiSinh::layBangDiem(int stt)
{
	// tao 1 filestream de doc file
	fstream a;
	//a.open(R"(C:\Users\Son Pham\Desktop\OOP\csdl-bk.csv)", ios::in);
	a.open("csdl-bk.csv", ios::in);
	// tao mot 1 vector chua cac token lay dc
	std::vector<string> m;
	//tao 1 mang chua cac ki tu doc duoc tu dong
	char b[500] = "";
	//1 string de split
	string c;
	//doc vao den dung stt thi lay du lieu do ra
	for (int i = 1; i < 10000; i++)
	{
		a.getline(b, 500);
		if (i == stt+1)
		{
			break;
		}
	}
	// tokenise va luu token vao vecto
	boost::split(m, b, boost::is_any_of(","));
	//loai bo ki tu "
	for each (string var in m)
	{
		var = boost::replace_all_copy(var, "\"", "");
	}
	//gan cac token thich hop vao thong tin thi sinh
	hoTen = m[1];
	ngaySinh = m[2];
	khuVuc = m[3];
	doiTuong = m[4];
	uuTien = m[5];
	//dien bang diem
	for (int i = 0, j = 6; i < 13; i++, j++)
	{
		if (m[j] == "NA") bangDiem[i] = -1;
		else bangDiem[i] = stod(m[j]);
	}
	// bang diem cac nguyen vong
	int i, j = 0;
	for (i = 0; i < 3; i++, j++)
	{
		diemNV[0][i] = timDiem(toHop[j]);
	}
	for (i = 0; i < 3; i++, j++)
	{
		diemNV[1][i] = timDiem(toHop[j]);
	}
	for (i = 0; i < 3; i++, j++)
	{
		diemNV[2][i] = timDiem(toHop[j]);
	}
	for (i = 0; i < 3; i++, j++)
	{
		diemNV[3][i] = timDiem(toHop[j]);
	}
	//dien bang diem cho tung nguyen vong
	/*for (int k = 0; k < 4; k++)
	{
		for (i = 0; i < 3; i++, j++)
		{
			diemNV[k][i] = timDiem(toHop[j]);
		}
	}*/
}
//tim diem tuong voi mon hoc
double ThiSinh::timDiem(string monHoc)
{
	if (monHoc == "Toan") return bangDiem[0];
	if (monHoc == "Van") return bangDiem[1];
	if (monHoc == "Ly") return bangDiem[2];
	if (monHoc == "Hoa") return bangDiem[3];
	if (monHoc == "Sinh") return bangDiem[4];
	if (monHoc == "Su") return bangDiem[5];
	if (monHoc == "Dia") return bangDiem[6];
	if (monHoc == "Anh") return bangDiem[7];
	if (monHoc == "Nga") return bangDiem[8];
	if (monHoc == "Phap") return bangDiem[9];
	if (monHoc == "Trung") return bangDiem[10];
	if (monHoc == "Duc") return bangDiem[11];
	if (monHoc == "Nhat") return bangDiem[12];
	if (monHoc == "NA") return -1;
}
//tinh diem cong cho thi sinh
void ThiSinh::tinhDiemCong()
{
	// s la bien diem cong doi tuong
	double s = 0;
	if (khuVuc == "KV1") s += 1.5;
	if (khuVuc == "KV2-NT") s += 1.0;
	if (khuVuc == "KV2") s += 0.5;
	if (doiTuong == "NDT1") s += 2.0;
	if (doiTuong == "NDT2") s += 1.0;
	// xu ly diem uu tien
	if (uuTien == "Co") diemCong = s / 3 + 1.0;
	if (uuTien == "Khong") diemCong = s / 3;
}
//hien thi thong tin thi sinh
void ThiSinh::hienThi()
{
	cout << "So bao danh: "<< soBaoDanh << endl;
	cout << "Ho va ten: " <<hoTen << endl;
	cout << "Ngay sinh: "<<ngaySinh << endl;
	cout << "Khu vuc: " <<khuVuc << endl;
	cout << "Uu tien: "<<uuTien << endl;
	cout << "Doi tuong: "<<doiTuong << endl;
	cout << "Diem cong: "<<diemCong << endl;
	cout << "--NV---Diem--" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << nv[i] << " " << diemXetTuyenNV[i] << endl;
	}

	for (int i = 0; i < 12; i++)
	{
		cout << toHop[i] << " ";
	}
	cout << endl;
	cout << "---------BANG DIEM------------" << endl;
	cout << "Toan Van Ly Hoa Sinh Su Dia Anh Nga Phap Trung Duc Nhat" << endl;
	for (int i = 0; i < 13; i++)
	{
		cout << bangDiem[i] << "  ";
	}
	cout << endl;
	cout << "Bang diem xet tuyen" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << diemNV[i][j] << " ";
		}
		cout << endl;
	}
}
