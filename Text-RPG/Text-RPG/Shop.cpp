#include "Shop.h"

// ����� ��� �������� �������� ��������
ItemShop::ItemShop(string nameItem, int price, string category, int stats) {
    this->nameItem = nameItem;
    this->price = price;
    this->category = category;
    this->stats = stats;
}

// ������ �������
map<string, ItemShop> ItemList{
{"1", ItemShop("��������� ���", 250, "�����", 50)},
{"2", ItemShop("�������� ����", 150, "������", 5)},
{"3", ItemShop("������", 200, "��������", 50)},
{"4", ItemShop("����� �������", 50, "���������", 1)},
{"5", ItemShop("������������� �����", 150, "���������", 1)}
};

// ����������� ���� ��������
void ShowShopMenu() {
    int i = 1;
    cout << "�������" << endl;

    for (auto item : ItemList)
    {
        cout << "[" << i << "] " << item.second.nameItem << "\t" << item.second.price << "\t" << item.second.category << endl;
        i++;
    }
    cout << "\n[0] �����" << endl;
}

void Shop(Player& player) {
    int nChoice; // ��������� ��� ������ ������������
    bool isConsumables = false;

    while (true) {

        ShowShopMenu(); // ����� ����������� ���� �������� 

        // ���������� ������ ������������
        if (!(cin >> nChoice)) {
            nChoice = -1;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "-------------------------------------------" << endl;


        if (nChoice == 0) 
            break;
        else if (nChoice > 0 && nChoice < ItemList.size() + 1) {
            // ���������� ������� ������ �� ������ ��������
            auto it = ItemList.begin();
            advance(it, nChoice - 1);
            auto item = it->second;

            // ���������� �������
            if (player.goold > item.price) {
                player.goold -= item.price; // ������ ����� � ������

                // ������������� �������� ��� ������� 
                if (item.category == "�����") player.damage += item.stats;
                else if (item.category == "������") player.armor += item.stats;
                else if (item.category == "��������") player.playerhp += item.stats;
                else {
                    isConsumables = true;
                    player.bonus.find(item.nameItem)->second += 1;
                }

                // �������� ����������� �������
                if (!isConsumables) {
                    ItemList.erase(it->first);
                }

                cout << "������� �� �������" << endl;
                isConsumables = false;
            }
            else cout << "� ��� �� ������� �����" << endl;
        }
        else cout << "������������ �����, ���������� ������" << endl;

        cout << "-------------------------------------------" << endl;
    }
}