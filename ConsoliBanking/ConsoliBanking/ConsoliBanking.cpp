#include <iostream>
#include <locale>
#include "OperationAccount.h"

using namespace std;


int main()
{
	setlocale(LC_ALL, "rus");
	char nChoice;
	int numAccount;

	do{
		system("cls");
		cout << "\tМеню\n"
				"[1] Создать новый счёт\n"
				"[2] Просмотор счета\n"
				"[3] Изменение счета \n"
				"[4] Перевод средс на доугой счёт\n"
				"[5] Все счета\n"
				"[6] Удуаление счёта\n"
				"[7] Выход" << endl;

		cout << "Вберети вариант: ";
		cin >> nChoice;
		system("cls");

		switch (nChoice)
		{
		case '1':
			CreatAccount();
			break;
		case '2':
			cout << "Введите номер счета : "; 
			cin >> numAccount;
			ReadAccount(numAccount);
			break;
		case '3':
			cout << "Введите номер счета : "; 
			cin >> numAccount;
			ModifyAccount(numAccount);
			break;
		case '4':
			cout << "Введите номер счета на которой будет передоваться сумма : ";
			cin >> numAccount;
			cout << "Введите номер счета с которого будут списыватььс сумма: ";
			int numAccount2;
			cin >> numAccount2;
			cout << "Введите номер суммы тронзакции : ";
			int sum;
			cin >> sum;
			Transactions(numAccount, numAccount2, sum);
			break;
		case '5':
			AllAccount();
			break;
		case '6':
			cout << "Введите номер счета : "; 
			cin >> numAccount;
			DeleteAccount(numAccount);
			break;
		case '7':
			break;
		default:
			cout << "Ввод не верного значения" << endl;
			break;
		}

		cin.ignore();
		cin.get();

	} while (nChoice != '7');
}