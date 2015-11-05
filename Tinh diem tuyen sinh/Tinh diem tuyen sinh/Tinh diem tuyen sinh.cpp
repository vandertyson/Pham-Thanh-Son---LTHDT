// Tinh diem tuyen sinh.cpp : Defines the entry point for the console application.
//

#pragma warning(disable:4996);
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include "DBconnect.h"
#include <boost\algorithm\string\split.hpp>
#include <boost\algorithm\string.hpp>
#include <vector>
#include "ThiSinh.h"
using namespace std;
using namespace boost;

int _tmain(int argc, _TCHAR* argv[])
{
	// tao tao 1 doi tuong de thuc hien ket noi den database
	DBconnect mydb("31.db");
	// ket noi toi database 31.db. Neu chua co se tu dong tao moi
	mydb.connect();
	// tao bang nvxt trong 31.db
	mydb.createDB();
	// khoi tao mang chua thong tin 100 thi sinh
	ThiSinh dsThiSinh[100];
	for (int i = 0; i < 100; i++)
	{
		//lay thong tin thi sinh tu so 3100 den 3199 trong danh sach
		//tinh toan diem cho thi sinh
		dsThiSinh[i].layThongTin(3100 + i);
		dsThiSinh[i].layBangDiem(3100 + i);
		dsThiSinh[i].tinhDiem();
		//them vao csdl
		mydb.insert(dsThiSinh[i]);
		//hien thi thong tin da them vao
		mydb.select(dsThiSinh[i]);
	}
	//ngat ket noi toi database
	mydb.disconnect();
	system("pause");
}


