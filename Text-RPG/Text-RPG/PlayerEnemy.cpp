#include <iostream>
#include "PlayerEnemy.h"
#include <map>

using namespace std;

// Создание игрогово персонажа
Player::Player() {
	cout << "Как завут вашего персонажа: ";
	cin >> name;
}

// Отоброжание статуса игрового персоножа
void Player::GetStatys() {
	cout << "Имя: " << name << endl;
	cout << "Здоровье: " << hp << " / " << playerhp << endl;
	cout << "Уровень: " << level << endl;
	cout << "До следощиго уровня: " << levelUp - xp << endl;
	cout << "Атака: " << damage << endl;
	cout << "Защита: " << armor << endl;
	cout << "Золото: " << goold << endl;
    cout << "Инвентарь:" << endl;
    for (auto item : bonus) {
        cout << item.first << "\t" << item.second << endl;
    }
}

// Получение опыта и повышение уровня
void Player::SetXp(int xp) {
	this->xp += xp;
	
	while (this->xp >= levelUp) {
	    this->xp -= levelUp;
	    level++;
	    levelUp += levelUp * multipluLevelUp / 100;
		cout << "Ваш уровень повышен!!!" << endl;
	}
}

// Использование бонусов
void Player::UseBonus(string nameItem, Enemy &enemy){
    auto item = bonus.find(nameItem);

    if (item->second == 0)
        cout << "У вас закончились " << item->first << endl;
    else {
        item->second -= 1;
        cout << "Вы испльзовали " << item->first << endl;
        if (item-> first == "Зелье леченья") {
            hp += 50;
            cout << "Вы исцелили 50 здоровья" << endl;
            if (hp > playerhp) hp = playerhp;
        }
        else if (item->first == "Оглушительная бомба") {
            enemy.stats = StatsEnemyPlayer::STUNNED;
            enemy.hp -= 15;
            cout << enemy.name << " оглушон и ему нанесено 15 урона" << endl;
        }
    }
}

// Создание врога
Enemy::Enemy(string name, int level, int xp, int hp, int damage, int armor, int gold) {
    this->name = name;
    this->level = level;
    this->xp = xp;
    this->hp = hp;
    this->damage = damage;
    this->armor = armor;
    this->goold = gold;
}

// Атака врага
void Enemy::Attac(Player& player) {
    int damagePLayer = player.armor - damage;
    if (damagePLayer > 0) {
        cout << "Вам нанесено " << damagePLayer << endl;
        player.hp -= damagePLayer;
    }
    else cout << name << " нехватило урона, чтобы пробить вашу зашиту" << endl;
}

// Атака игрока
void Player::Attac(Enemy& enemy) {
    int damagePLayer = enemy.armor - damage;
    if (damagePLayer > 0) {
        cout << "Вам нанесено " << damagePLayer << endl;
        enemy.hp -= damagePLayer;
    }
    else cout << name << " нехватило урона, чтобы пробить зашиту " << enemy.name << endl;
}