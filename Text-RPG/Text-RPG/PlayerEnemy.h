#pragma once
#include <iostream>
#include <map>

using namespace std;

enum StatsEnemyPlayer {
    NONE,
    STUNNED,
    POISONING
};

class Stats {
public:
    string name;

    StatsEnemyPlayer stats = StatsEnemyPlayer::NONE;

    int hp = 100;
    int damage = 10;
    int armor = 0;
    int level = 1;
    int xp = 0;
    int goold = 100;
};

class Enemy;

class Player : public Stats {
public:
    int playerhp = hp;

    Player();

    void GetStatys();

    void Attac(Enemy& enemy);

    void SetXp(int xp);

    map<string, int> bonus{
    {"Зелье леченья", 1},
    {"Оглушительная бомба" , 0}
    };

    void UseBonus(string, Enemy &enemy);

private:
    int levelUp = 100;
    int multipluLevelUp = 10;
};

class Enemy : public Stats {
public:
    Enemy(string name, int level, int xp, int hp, int damage, int armor, int gold);

    void Attac(Player& player);

    friend void Player::Attac(Enemy& enemy);
    friend void Player::UseBonus(string, Enemy& enemy);
};
