#pragma once
#include <iostream>
#include <map>
#include "PlayerEnemy.h"

using namespace std;

class ItemShop {
public:
    ItemShop(string nameItem, int price, string category, int stats);

    int price;
    int stats;

    string category;
    string nameItem;
};

extern map<string, ItemShop> ItemList;

void ShowShopMenu();

void Shop(Player& player);

