#pragma once
#include <boost\algorithm\string.hpp>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "sqlite3.h"
using namespace std;
using namespace boost;
class ThiSinh
{
public:
	ThiSinh();
	~ThiSinh();
	string soBaoDanh;
	string hoTen;
	string ngaySinh;
	string khuVuc;
	string doiTuong;
	string uuTien;
	string nv[4];
	string toHop[12];
	double diemCong;
	double bangDiem[13];
	double diemNV[4][4];
	double diemXetTuyenNV[4];
	void tinhDiemCong();
	void layThongTin(int stt);
	void layBangDiem(int stt);
	double timDiem(string monHoc);
	void tinhDiem();
	void hienThi();
};

