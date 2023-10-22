#include "OperationAccount.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Создаёт и сохроняет новый счёт
void CreatAccount()
{
	Account ac;
	ofstream outFile;

	//Создание счёта и открытие файла для записи
	outFile.open("account.dat", ios::binary | ios::app);
	ac.creat_accout();

	//Записывание нового счёта в файл
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(Account));
	outFile.close();
}

// Чтение и отоброжение счёта из файла
void ReadAccount(int n)
{
	Account ac;
	bool flag = false;
	ifstream inFile;

	inFile.open("account.dat", ios::binary); // открытие файлы
	// Проверка открытия файла
	if (!inFile)
	{
		cout << "Файл не открыть! Ведить другой номер счёта";
		return;
	}
	cout << "\nСВЕДЕНИЯ О СЧЁТЕ\n";

	//Чтение счёта
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(Account)))
	{
		if (ac.get_num_account() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();

	// Проверка на существоввание счёта
	if (flag == false)
		cout << "\nТакого номера счёта не сушествует";
}

// Изменение счёта
void ModifyAccount(int n)
{
	bool found = false;
	Account ac;
	fstream File;

	File.open("account.dat", ios::binary | ios::in | ios::out);// открытие файлы
	// Проверка открытия файла
	if (!File)
	{
		cout << "Файл не открыть! Ведить другой номер счёта";
		return;
	}

	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(Account));
		if (ac.get_num_account() == n)
		{
			ac.show_account();
			cout << "\n\nВведити новые данне" << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(Account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(Account));
			cout << "\n\t Данные обнавлены";
			found = true;
		}
	}
	File.close();

	// Проверка на существоввание счёта
	if (found == false)
		cout << "\nЗапись не найдена ";
}

// Перевод средств между счётами
void Transactions(int nAccountOne, int nAccountTwo, int sumTransactions) {
	Account accountOne;
	Account accountTwo;

	bool ferstfound = false;
	bool secondfound = false;
	fstream ferstFile;
	fstream secondFile;

	ferstFile.open("account.dat", ios::binary | ios::in | ios::out); // открытие файлы для изменения первого счёта
	secondFile.open("account.dat", ios::binary | ios::in | ios::out); // открытие файлы для изменения второго счёта

	// Проверка открытия файла
	if (!ferstFile || !secondFile)
	{
		cout << "Файл не открыть! Ведить другой номер счёта";
		return;
	}
	cout << "\nНачало транзакции\n";

	// Изменение второго счёта
	while (!secondFile.eof() && secondfound == false)
	{
		secondFile.read(reinterpret_cast<char*> (&accountTwo), sizeof(Account));

		if (accountTwo.get_num_account() == nAccountTwo)
		{
			accountTwo -= sumTransactions;

			// Проверка на достаток средст для перевода
			if (accountTwo.get_money() >= 0) {
				int pos = (-1) * static_cast<int>(sizeof(Account));

				secondFile.seekp(pos, ios::cur);
				secondFile.write(reinterpret_cast<char*> (&accountTwo), sizeof(Account));

				secondfound = true;
			}
			else {
				accountTwo += sumTransactions;
				ferstfound = true;
				cout << "Недостаточно средств для переода" << endl;
				break;
			}
		}
	}
	secondFile.close();

	cout << ferstfound << endl;

	// Изменение перевого счёта
	while (!ferstFile.eof() && ferstfound == false)
	{
		cout << ferstfound << endl;
		ferstFile.read(reinterpret_cast<char*> (&accountOne), sizeof(Account));

		if (accountOne.get_num_account() == nAccountOne)
		{
			accountOne += sumTransactions;
			int pos = (-1) * static_cast<int>(sizeof(Account));
			ferstFile.seekp(pos, ios::cur);
			ferstFile.write(reinterpret_cast<char*> (&accountOne), sizeof(Account));
			ferstfound = true;
		}
	}
	ferstFile.close();

	//Вывод степени переода
	if (ferstfound == false && secondfound == false)
		cout << "\nТакого номера счёта не сушествует";
	else if (ferstfound == false || secondfound == false)
		cout << "\nОперация прервона";
	else
		cout << "\nПеревод средств проведн успешно";
};

//Удаление счёта
void DeleteAccount(int n)
{
	Account ac;
	ifstream inFile; // Создание изночального файла
	ofstream outFile; // Создание вспомогательного файла

	inFile.open("account.dat", ios::binary);// открытие файлы
	// Проверка открытия файла
	if (!inFile)
	{
		cout << "Файл не открыть! Ведить другой номер счёта";
		return;
	}

	// Запись данных из изночального файла в 
	// вспомогательный файл кроме удаляемого счёта
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(Account)))
	{
		if (ac.get_num_account() != n)
		{
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(Account));
		}
	}
	inFile.close();
	outFile.close();

	// Удаление исходного файла
	remove("account.dat");
	// Пременование вспомогательного файла
	rename("Temp.dat", "account.dat");
	cout << "\nЗапись удалена";
}

// Отоброжение всех счетов
void AllAccount()
{
	Account ac;
	ifstream inFile;

	inFile.open("account.dat", ios::binary);// открытие файлы
	// Проверка открытия файла
	if (!inFile)
	{
		cout << "Файл не открыть! Ведить другой номер счёта";
		return;
	}

	// Отоброжение шапки списка
	cout << "\n\t\tСПИСОК ВЛАДЕЛЬЦЕВ СЧЕТОВ\n\n";
	cout << "====================================================\n";
	cout << "Ном. А/та      Имя            Баланс\n";
	cout << "====================================================\n";

	// Отоброжение списка счетов
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(Account)))
	{
		ac.report();
	}
	inFile.close();
}