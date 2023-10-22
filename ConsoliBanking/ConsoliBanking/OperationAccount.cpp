#include "OperationAccount.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// ������ � ��������� ����� ����
void CreatAccount()
{
	Account ac;
	ofstream outFile;

	//�������� ����� � �������� ����� ��� ������
	outFile.open("account.dat", ios::binary | ios::app);
	ac.creat_accout();

	//����������� ������ ����� � ����
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(Account));
	outFile.close();
}

// ������ � ����������� ����� �� �����
void ReadAccount(int n)
{
	Account ac;
	bool flag = false;
	ifstream inFile;

	inFile.open("account.dat", ios::binary); // �������� �����
	// �������� �������� �����
	if (!inFile)
	{
		cout << "���� �� �������! ������ ������ ����� �����";
		return;
	}
	cout << "\n�������� � �ר��\n";

	//������ �����
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(Account)))
	{
		if (ac.get_num_account() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();

	// �������� �� �������������� �����
	if (flag == false)
		cout << "\n������ ������ ����� �� ����������";
}

// ��������� �����
void ModifyAccount(int n)
{
	bool found = false;
	Account ac;
	fstream File;

	File.open("account.dat", ios::binary | ios::in | ios::out);// �������� �����
	// �������� �������� �����
	if (!File)
	{
		cout << "���� �� �������! ������ ������ ����� �����";
		return;
	}

	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(Account));
		if (ac.get_num_account() == n)
		{
			ac.show_account();
			cout << "\n\n������� ����� �����" << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(Account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(Account));
			cout << "\n\t ������ ���������";
			found = true;
		}
	}
	File.close();

	// �������� �� �������������� �����
	if (found == false)
		cout << "\n������ �� ������� ";
}

// ������� ������� ����� �������
void Transactions(int nAccountOne, int nAccountTwo, int sumTransactions) {
	Account accountOne;
	Account accountTwo;

	bool ferstfound = false;
	bool secondfound = false;
	fstream ferstFile;
	fstream secondFile;

	ferstFile.open("account.dat", ios::binary | ios::in | ios::out); // �������� ����� ��� ��������� ������� �����
	secondFile.open("account.dat", ios::binary | ios::in | ios::out); // �������� ����� ��� ��������� ������� �����

	// �������� �������� �����
	if (!ferstFile || !secondFile)
	{
		cout << "���� �� �������! ������ ������ ����� �����";
		return;
	}
	cout << "\n������ ����������\n";

	// ��������� ������� �����
	while (!secondFile.eof() && secondfound == false)
	{
		secondFile.read(reinterpret_cast<char*> (&accountTwo), sizeof(Account));

		if (accountTwo.get_num_account() == nAccountTwo)
		{
			accountTwo -= sumTransactions;

			// �������� �� �������� ������ ��� ��������
			if (accountTwo.get_money() >= 0) {
				int pos = (-1) * static_cast<int>(sizeof(Account));

				secondFile.seekp(pos, ios::cur);
				secondFile.write(reinterpret_cast<char*> (&accountTwo), sizeof(Account));

				secondfound = true;
			}
			else {
				accountTwo += sumTransactions;
				ferstfound = true;
				cout << "������������ ������� ��� �������" << endl;
				break;
			}
		}
	}
	secondFile.close();

	cout << ferstfound << endl;

	// ��������� �������� �����
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

	//����� ������� �������
	if (ferstfound == false && secondfound == false)
		cout << "\n������ ������ ����� �� ����������";
	else if (ferstfound == false || secondfound == false)
		cout << "\n�������� ��������";
	else
		cout << "\n������� ������� ������� �������";
};

//�������� �����
void DeleteAccount(int n)
{
	Account ac;
	ifstream inFile; // �������� ������������ �����
	ofstream outFile; // �������� ���������������� �����

	inFile.open("account.dat", ios::binary);// �������� �����
	// �������� �������� �����
	if (!inFile)
	{
		cout << "���� �� �������! ������ ������ ����� �����";
		return;
	}

	// ������ ������ �� ������������ ����� � 
	// ��������������� ���� ����� ���������� �����
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

	// �������� ��������� �����
	remove("account.dat");
	// ������������ ���������������� �����
	rename("Temp.dat", "account.dat");
	cout << "\n������ �������";
}

// ����������� ���� ������
void AllAccount()
{
	Account ac;
	ifstream inFile;

	inFile.open("account.dat", ios::binary);// �������� �����
	// �������� �������� �����
	if (!inFile)
	{
		cout << "���� �� �������! ������ ������ ����� �����";
		return;
	}

	// ����������� ����� ������
	cout << "\n\t\t������ ���������� ������\n\n";
	cout << "====================================================\n";
	cout << "���. �/��      ���            ������\n";
	cout << "====================================================\n";

	// ����������� ������ ������
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(Account)))
	{
		ac.report();
	}
	inFile.close();
}