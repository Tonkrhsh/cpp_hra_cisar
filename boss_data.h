#ifndef UNTITLED1_BOSS_DATA_H
#define UNTITLED1_BOSS_DATA_H

struct BossData {
    int hp_mini_boss;
    int hp_magnetron;
    int hp_polarisurge;

    int boss_damage_mini;

    int coins_earn_mini;
    int coins_earn_duo;
};

BossData createBossData();

#endif
