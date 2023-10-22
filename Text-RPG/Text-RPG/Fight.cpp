#include "Fight.h"

// ������ ���� ������
map<string, Enemy> EnemyList{
    {"1", Enemy("������", 1, 25, 50, 10, 0, 25)},
    {"2", Enemy("����", 3, 100, 100, 15, 3, 75)},
    {"3", Enemy("���� ������", 5, 300, 150, 25, 1, 125)},
};

// ����������� � ���������� ���� ������� ������
void PlayerFight(Player &player, Enemy &enemy) {
    int nChoice;

    while (true) {
        int i = 1;

        // ����������� ������� ������
        cout << "�����" << endl;
        for (auto item : player.bonus)
        {
            cout << "[" << i << "] " << item.first << endl;
            i++;
        }
        cout << "\n[0] �����" << endl;

        // ���������� ������ ������������
        if (!(cin >> nChoice)) {
            nChoice = -1;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // ������������� �������� ������ ������
        if (nChoice == 0) break;
        else if (nChoice > 0 && nChoice < player.bonus.size() + 1) {
            auto it = player.bonus.begin();
            advance(it, nChoice - 1);

            player.UseBonus(it->first, enemy);
            break;
        }
        else cout << "������������ �����, ���������� ������" << endl;

        cout << "-------------------------------------------" << endl;
    }
}

// �������� ������ � ������
void Fighting(Player& player, Enemy& enemy) {
    int enemyHp = enemy.hp; // �������� �����
    int damage = player.damage + (100 + player.level) / 100; // ����� ������

    int nChoice;
    bool isPLayer = true;

    while (player.hp > 0 && enemyHp > 0) {

        if (isPLayer) {
            // ���� ��������
            cout << "[1] ���������\n"
                    "[2] ����������\n"
                    "[3] �������\n";

            // ���������� ������ ������������
            if (!(cin >> nChoice)) {
                nChoice = -1;
                cin.clear();
                cin.ignore(1000, '\n');
            }

            switch (nChoice)
            {
            case(1): // ��������� ����� �������
                enemyHp -= damage;
                cout << "�� ������� " << damage << " ����� " << enemy.name << endl;
                break;
            case(2): // �������� ���� �������
                PlayerFight(player, enemy);
                break;
            case(3): // ����� �� �������
                cout << "�� �������" << endl;
                break;
            default:
                cout << "-------------------------------------------" << endl;
                cout << "������������ �����, ���������� ������" << endl;
                isPLayer = !isPLayer;
                break;
            }
        }
        else { // ��������� ���� ������

            if (enemy.stats == StatsEnemyPlayer::STUNNED) { // ������� ���� �����, ���� ���� �������
                enemy.stats == StatsEnemyPlayer::NONE;
                isPLayer = !isPLayer;
                continue;
            }

            cout << enemy.name << "���� ��� " << enemy.damage << " �����" << endl;
            player.hp -= enemy.damage;
        }

        if (nChoice == 3) break;

        isPLayer = !isPLayer;
        cout << "-------------------------------------------" << endl;
    }

    if (nChoice != 3) {
        // ����������� ��������� ��������
        if (player.hp > 0) { // ���� ����� �������
            cout << "�� �������� " << enemy.name << endl;
            cout << "�� ��������:\t" << "������: " << enemy.goold << "\t����: " << enemy.xp << endl;

            // ��������� ������ � ����� ����� ��������
            player.goold += enemy.goold;
            player.SetXp(enemy.xp);
        }
        else {
            cout << "�� ��������� " << enemy.name << endl;
        }
    }
}

// ����������� ���� ��������
void ShowFightingMenu() {
    int i = 1;
    cout << "�����" << endl;
    for (auto item : EnemyList)
    {
        cout << "[" << i << "] " << item.second.name << "\t" << item.second.level << endl;
        i++;
    }
    cout << "\n[0] �����" << endl;
}


void FightingMenu(Player& player) {
    int nChoice; // ������� ��� ������ ������������

    while (true) {

        ShowFightingMenu(); // ����� ����������� ���� ��������

                // ���������� ������ ������������
        if (!(cin >> nChoice)) {
            nChoice = -1;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "-------------------------------------------" << endl;

        if (nChoice == 0) break;
        else if (nChoice > 0 && nChoice < EnemyList.size() + 1) {
            // ��������� ��������� �����
            auto it = EnemyList.begin();
            advance(it, nChoice - 1);
            auto enemy = it->second;

            Fighting(player, enemy); // ����� ������ �������� ������ � �����
        }
        else cout << "������������ �����, ���������� ������" << endl;

        cout << "-------------------------------------------" << endl;
    }
}