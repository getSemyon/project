#include "account.h"
#include <iostream>
#include <iomanip>

using namespace std;

// ������ ��������� � ����
void Account::creat_accout() {
	cout << "\n������� ����� ������� :";
	cin >> numAccount;
	cout << "\n������� ��� ��������� ������ : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n������� ���������� ����� �� ����� :";
	cin >> money;
	cout << "\n\n������ ������.." << endl;
}

// ����������� ��������� ������
void Account::show_account() {
	cout << "\n����� ������� : " << numAccount;
	cout << "\n��� ��������� : " << name;
	cout << "\n������� ������� : " << money;
};

// ��������� �����
void Account::modify() {
	cout << "\n������� ����� ������� :";
	cin >> numAccount;
	cout << "\n������� ��� ��������� ������ : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n������� ���������� ����� �� ����� :";
	cin >> money;
}

// ����������� ��������� ������ � ������
void Account::report()
{
	cout << numAccount << setw(10) << " " << name << setw(10) << " " << money << endl;
}

// ��������� ������ �����
int Account::get_num_account()
{
	return numAccount;
}

// ��������� �������� ������ �����
int Account::get_money() {
	return money;
}

Account& Account::operator+=(int value)
{
	money += value;
	return *this;
}

Account& Account::operator-=(int value)
{
		money -= value;
		return *this;
}