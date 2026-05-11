#include "boss_data.h"

BossData createBossData() {
    BossData data{};

    data.hp_mini_boss = 20;
    data.hp_dual_boss = 200;
    data.hp_dual_boss2 = 200;

    data.boss_damage_mini = 5;
    data.boss_damage_dual = 10;

    data.coins_earn_mini = 10;
    data.coins_earn_dual = 50;

    return data;
}
