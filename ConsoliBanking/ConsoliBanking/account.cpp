#include "account.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Запись переменых в счёт
void Account::creat_accout() {
	cout << "\nВведите номер акаунта :";
	cin >> numAccount;
	cout << "\nВведите имя владельца акаута : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nВведите количиство денег на счету :";
	cin >> money;
	cout << "\n\nАкаунт создан.." << endl;
}

// Отоброжение переменых класса
void Account::show_account() {
	cout << "\nНомер акауньа : " << numAccount;
	cout << "\nИмя владельца : " << name;
	cout << "\nБалантс акаунта : " << money;
};

// Изменение счёта
void Account::modify() {
	cout << "\nВведите номер акаунта :";
	cin >> numAccount;
	cout << "\nВведите имя владельца акаута : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nВведите количиство денег на счету :";
	cin >> money;
}

// Отоброжение переменых класса в список
void Account::report()
{
	cout << numAccount << setw(10) << " " << name << setw(10) << " " << money << endl;
}

// Получение номера счёта
int Account::get_num_account()
{
	return numAccount;
}

// Получение значение средст счёта
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