#include "boss_data.h"

BossData createBossData() {
    BossData data{};

    data.hp_mini_boss = 20;
    data.hp_magnetron = 50;
    data.hp_polarisurge = 50;

    data.boss_damage_mini = 5;

    data.coins_earn_mini = 10;
    data.coins_earn_duo = 50;

    return data;
}
