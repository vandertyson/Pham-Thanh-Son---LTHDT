#pragma once
#include <stdlib.h>
#include "sqlite3.h"
#include <string>
#include "ThiSinh.h"
#include <exception>
using namespace std;
class DBconnect
{
public:
	DBconnect(string name);
	~DBconnect();
	void connect();
	void disconnect();
	void insert(ThiSinh s);
	void select(ThiSinh s);
	void createDB();
	bool isConnected;
	string dbName;
	sqlite3* dbFile;
};

