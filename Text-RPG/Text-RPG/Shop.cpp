#include "Shop.h"

// Класс для создания элемента магазина
ItemShop::ItemShop(string nameItem, int price, string category, int stats) {
    this->nameItem = nameItem;
    this->price = price;
    this->category = category;
    this->stats = stats;
}

// Список пакупак
map<string, ItemShop> ItemList{
{"1", ItemShop("Двуручный меч", 250, "Атака", 50)},
{"2", ItemShop("Железные латы", 150, "Защита", 5)},
{"3", ItemShop("Амулет", 200, "Здоровье", 50)},
{"4", ItemShop("Зелье леченья", 50, "Расходник", 1)},
{"5", ItemShop("Оглушительная бомба", 150, "Расходник", 1)}
};

// Отоброжение меню магазина
void ShowShopMenu() {
    int i = 1;
    cout << "Магазин" << endl;

    for (auto item : ItemList)
    {
        cout << "[" << i << "] " << item.second.nameItem << "\t" << item.second.price << "\t" << item.second.category << endl;
        i++;
    }
    cout << "\n[0] Выход" << endl;
}

void Shop(Player& player) {
    int nChoice; // Переменая для выбора пользователя
    bool isConsumables = false;

    while (true) {

        ShowShopMenu(); // Вызов отоброжения меню магазина 

        // Считывание выбора пользователя
        if (!(cin >> nChoice)) {
            nChoice = -1;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "-------------------------------------------" << endl;


        if (nChoice == 0) 
            break;
        else if (nChoice > 0 && nChoice < ItemList.size() + 1) {
            // Нахождения нужного товара из списка ттоваров
            auto it = ItemList.begin();
            advance(it, nChoice - 1);
            auto item = it->second;

            // Совершении покупки
            if (player.goold > item.price) {
                player.goold -= item.price; // снятие денег у игрока

                // Распределение статуств или бонусов 
                if (item.category == "Атака") player.damage += item.stats;
                else if (item.category == "Защита") player.armor += item.stats;
                else if (item.category == "Здоровье") player.playerhp += item.stats;
                else {
                    isConsumables = true;
                    player.bonus.find(item.nameItem)->second += 1;
                }

                // Удаление одноразывых пакупак
                if (!isConsumables) {
                    ItemList.erase(it->first);
                }

                cout << "Спасибо за покупку" << endl;
                isConsumables = false;
            }
            else cout << "У вас не хвотает денег" << endl;
        }
        else cout << "Неправильный выбор, попробуйти занова" << endl;

        cout << "-------------------------------------------" << endl;
    }
}