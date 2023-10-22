#pragma once
#include <iostream>
#include <map>
#include "PlayerEnemy.h"

using namespace std;

extern map<string, Enemy> EnemyList;

void PlayerFight(Player& player);

void Fighting(Player& player, Enemy& enemy);

void ShowFightingMenu();

void FightingMenu(Player& player);