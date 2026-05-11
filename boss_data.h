#ifndef UNTITLED1_BOSS_DATA_H
#define UNTITLED1_BOSS_DATA_H

struct BossData {
    int hp_mini_boss;
    int hp_dual_boss;
    int hp_dual_boss2;

    int boss_damage_mini;
    int boss_damage_dual;

    int coins_earn_mini;
    int coins_earn_dual;
};

BossData createBossData();

#endif
