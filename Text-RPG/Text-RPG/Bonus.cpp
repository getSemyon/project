#include "bonus.h"


void Heal(Player& player, Enemy& enemy, int poverHeal) {
    player.hp += 50;
    cout << "Вы исцелили 50 здоровья" << endl;
    if (player.hp > player.playerhp) player.hp = player.playerhp;
}

void Stuned(Player& player, Enemy& enemy, int poverStuned) {
    enemy.stats = StatsEnemyPlayer::STUNNED;
    enemy.hp -= 10;
    cout << enemy.name << " оглушон и ему нанесено 10 урона" << endl;
}