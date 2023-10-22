#pragma once
#include <iostream>
#include <map>

class Account {
public:
	void creat_accout();

	void show_account();

	void modify();

	void report();

	int get_num_account();
	
	int get_money();

	Account& operator += (int value);

	Account& operator -= (int value);

private:
	int numAccount;
	char name[50];
	int money;
};
