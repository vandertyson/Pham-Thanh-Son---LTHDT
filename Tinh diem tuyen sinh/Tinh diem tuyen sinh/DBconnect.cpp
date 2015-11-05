#include "DBconnect.h"
#include <iostream>

DBconnect::DBconnect(string name)
{
	dbName = name;
	isConnected = false;
}

DBconnect::~DBconnect()
{
}
//ket noi vao databse
void DBconnect::connect()
{
	if (sqlite3_open(dbName.c_str(), &dbFile) == SQLITE_OK)
	{
		isConnected = true;
	}
}
//disconnect
void DBconnect::disconnect()
{
	if (isConnected == true)
	{
		sqlite3_close(dbFile);
		isConnected = false;
	}
}
//them du lieu vao csdl
void DBconnect::insert(ThiSinh s)
{
	if (isConnected == true)
	{
		string querry;
		int count = 0;
		for (int i = 0; i < 4; i++)
		{
			if (s.diemXetTuyenNV[i] >= 0) count++;
		}
		//cout << count << endl;
		for (int i = 0; i < count; i++)
		{
			querry = "";
			querry += "insert into nvxt values('" + s.soBaoDanh + "','" + to_string(i+1) + "','" + s.nv[i] + "','" + to_string(s.diemXetTuyenNV[i]) + "');";
			sqlite3_exec(dbFile, querry.c_str(), NULL, NULL, NULL);
		}
	}
	else cout << " Error!" << endl;
}
//tao bang  trong csdl
void DBconnect::createDB()
{
	sqlite3_exec(dbFile, "drop table nvxt;", NULL, NULL, NULL);
	sqlite3_exec(dbFile, "create table nvxt(sbd varchar(9), nvso int, manv varchar(4), diemxt double precision);", NULL, NULL, NULL);
}
//lay thong tin this sinh theo so bao danh
void DBconnect::select(ThiSinh s)
{
	sqlite3_stmt *statement;
	string querry;
	querry += "select * from nvxt where sbd = '" +s.soBaoDanh+ "'";
	if (sqlite3_prepare_v2(dbFile,querry.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while (true)
		{
			result = sqlite3_step(statement);
			if (result == SQLITE_ROW)
			{
				for (int col = 0; col < cols; col++)
				{
					string s = (char*)sqlite3_column_text(statement, col);
					cout << s << " ";
				}
				cout << endl;
			}
			else
			{
				break;
			}
		}
		sqlite3_finalize(statement);
	}
}