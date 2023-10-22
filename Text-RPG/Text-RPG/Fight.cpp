#include "Fight.h"

// Список всех врагов
map<string, Enemy> EnemyList{
    {"1", Enemy("Червяк", 1, 25, 50, 10, 0, 25)},
    {"2", Enemy("Краб", 3, 100, 100, 15, 3, 75)},
    {"3", Enemy("Злой кролик", 5, 300, 150, 25, 1, 125)},
};

// Отображение и функционал меня бонусов игрока
void PlayerFight(Player &player, Enemy &enemy) {
    int nChoice;

    while (true) {
        int i = 1;

        // Отоброжение бонусов игрока
        cout << "Арена" << endl;
        for (auto item : player.bonus)
        {
            cout << "[" << i << "] " << item.first << endl;
            i++;
        }
        cout << "\n[0] Выход" << endl;

        // Считывание выбора пользователя
        if (!(cin >> nChoice)) {
            nChoice = -1;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // Использование вброного буноса играка
        if (nChoice == 0) break;
        else if (nChoice > 0 && nChoice < player.bonus.size() + 1) {
            auto it = player.bonus.begin();
            advance(it, nChoice - 1);

            player.UseBonus(it->first, enemy);
            break;
        }
        else cout << "Неправильный выбор, попробуйти занова" << endl;

        cout << "-------------------------------------------" << endl;
    }
}

// Сражение игрока и врагов
void Fighting(Player& player, Enemy& enemy) {
    int enemyHp = enemy.hp; // Здоровье врага
    int damage = player.damage + (100 + player.level) / 100; // Отака игрока

    int nChoice;
    bool isPLayer = true;

    while (player.hp > 0 && enemyHp > 0) {

        if (isPLayer) {
            // Меню сражение
            cout << "[1] Сражаться\n"
                    "[2] Расходники\n"
                    "[3] Сбежать\n";

            // Считывание выбора пользователя
            if (!(cin >> nChoice)) {
                nChoice = -1;
                cin.clear();
                cin.ignore(1000, '\n');
            }

            switch (nChoice)
            {
            case(1): // Нанесение урона игроком
                enemyHp -= damage;
                cout << "Вы нанесли " << damage << " урона " << enemy.name << endl;
                break;
            case(2): // Открытие меню бонусов
                PlayerFight(player, enemy);
                break;
            case(3): // Попег из сроения
                cout << "Вы сбежали" << endl;
                break;
            default:
                cout << "-------------------------------------------" << endl;
                cout << "Неправильный выбор, попробуйти занова" << endl;
                isPLayer = !isPLayer;
                break;
            }
        }
        else { // Нанесение урон врагом

            if (enemy.stats == StatsEnemyPlayer::STUNNED) { // Пропуск хода врага, если враг оглушон
                enemy.stats == StatsEnemyPlayer::NONE;
                isPLayer = !isPLayer;
                continue;
            }

            cout << enemy.name << "нанёс вам " << enemy.damage << " урона" << endl;
            player.hp -= enemy.damage;
        }

        if (nChoice == 3) break;

        isPLayer = !isPLayer;
        cout << "-------------------------------------------" << endl;
    }

    if (nChoice != 3) {
        // Отоброжение окончание сражения
        if (player.hp > 0) { // если игрок победит
            cout << "Вы побидили " << enemy.name << endl;
            cout << "Вы получили:\t" << "Золото: " << enemy.goold << "\tОпыт: " << enemy.xp << endl;

            // получение золота и опыта после срожения
            player.goold += enemy.goold;
            player.SetXp(enemy.xp);
        }
        else {
            cout << "Вы проиграли " << enemy.name << endl;
        }
    }
}

// Отоброжение меню сражения
void ShowFightingMenu() {
    int i = 1;
    cout << "Арена" << endl;
    for (auto item : EnemyList)
    {
        cout << "[" << i << "] " << item.second.name << "\t" << item.second.level << endl;
        i++;
    }
    cout << "\n[0] Выход" << endl;
}


void FightingMenu(Player& player) {
    int nChoice; // Переная для выбора пользователя

    while (true) {

        ShowFightingMenu(); // Вызов отоброжения меню магазина

                // Считывание выбора пользователя
        if (!(cin >> nChoice)) {
            nChoice = -1;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "-------------------------------------------" << endl;

        if (nChoice == 0) break;
        else if (nChoice > 0 && nChoice < EnemyList.size() + 1) {
            // Получение выброного врага
            auto it = EnemyList.begin();
            advance(it, nChoice - 1);
            auto enemy = it->second;

            Fighting(player, enemy); // Вызов метода сражения игрока и врага
        }
        else cout << "Неправильный выбор, попробуйти занова" << endl;

        cout << "-------------------------------------------" << endl;
    }
}