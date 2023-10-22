#include <iostream>
#include <locale>
#include <list>
#include <map>
#include "PlayerEnemy.h"
#include "Shop.h"
#include "Fight.h"

using namespace std;

// Отоброжение главного меню
void ShowMenu() {
    cout << "Меню\n"
        "[1] Статус\n"
        "[2] Арена\n"
        "[3] Магазин\n \n"
        "[0] Выход\n";
}

void Menu() {
    bool isExit = false; // Переменая для выхода из программы
    int nChoice; // Переменая для выбора
    Player player = Player(); // Создание игрока

    while (!isExit) {

        ShowMenu(); // Вызов отоброжения главного меню

        // Считывание выбора пользователя
        if (!(cin >> nChoice)) {
            nChoice = -1;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "-------------------------------------------" << endl;

            switch (nChoice)
            {
            case(1):
                player.GetStatys(); // Вызов статуса игра
                cout << "-------------------------------------------" << endl;
                break;
            case(2):
                FightingMenu(player); // Вызов меню срожения
                break;
            case(3):
                Shop(player); // Вызов меню магазина
                break;
            case(0):
                // Выхоод
                cout << "Досвидание, " << player.name << endl;
                isExit = !isExit;
                break;
            default:
                cout << "Неправильный выбор, попробуйти занова" << endl;
                cout << "-------------------------------------------" << endl;
                break;
            }
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    Menu();
}