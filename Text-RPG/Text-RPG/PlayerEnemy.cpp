#include <iostream>
#include "PlayerEnemy.h"
#include <map>

using namespace std;

// �������� �������� ���������
Player::Player() {
	cout << "��� ����� ������ ���������: ";
	cin >> name;
}

// ����������� ������� �������� ���������
void Player::GetStatys() {
	cout << "���: " << name << endl;
	cout << "��������: " << hp << " / " << playerhp << endl;
	cout << "�������: " << level << endl;
	cout << "�� ��������� ������: " << levelUp - xp << endl;
	cout << "�����: " << damage << endl;
	cout << "������: " << armor << endl;
	cout << "������: " << goold << endl;
    cout << "���������:" << endl;
    for (auto item : bonus) {
        cout << item.first << "\t" << item.second << endl;
    }
}

// ��������� ����� � ��������� ������
void Player::SetXp(int xp) {
	this->xp += xp;
	
	while (this->xp >= levelUp) {
	    this->xp -= levelUp;
	    level++;
	    levelUp += levelUp * multipluLevelUp / 100;
		cout << "��� ������� �������!!!" << endl;
	}
}

// ������������� �������
void Player::UseBonus(string nameItem, Enemy &enemy){
    auto item = bonus.find(nameItem);

    if (item->second == 0)
        cout << "� ��� ����������� " << item->first << endl;
    else {
        item->second -= 1;
        cout << "�� ����������� " << item->first << endl;
        if (item-> first == "����� �������") {
            hp += 50;
            cout << "�� �������� 50 ��������" << endl;
            if (hp > playerhp) hp = playerhp;
        }
        else if (item->first == "������������� �����") {
            enemy.stats = StatsEnemyPlayer::STUNNED;
            enemy.hp -= 15;
            cout << enemy.name << " ������� � ��� �������� 15 �����" << endl;
        }
    }
}

// �������� �����
Enemy::Enemy(string name, int level, int xp, int hp, int damage, int armor, int gold) {
    this->name = name;
    this->level = level;
    this->xp = xp;
    this->hp = hp;
    this->damage = damage;
    this->armor = armor;
    this->goold = gold;
}

// ����� �����
void Enemy::Attac(Player& player) {
    int damagePLayer = player.armor - damage;
    if (damagePLayer > 0) {
        cout << "��� �������� " << damagePLayer << endl;
        player.hp -= damagePLayer;
    }
    else cout << name << " ��������� �����, ����� ������� ���� ������" << endl;
}

// ����� ������
void Player::Attac(Enemy& enemy) {
    int damagePLayer = enemy.armor - damage;
    if (damagePLayer > 0) {
        cout << "��� �������� " << damagePLayer << endl;
        enemy.hp -= damagePLayer;
    }
    else cout << name << " ��������� �����, ����� ������� ������ " << enemy.name << endl;
}