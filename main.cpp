#include <iostream>
#include "boss_data.h"
#include "game_data.h"

bool fightDualBosses(GameData& data, const BossData& bosses) {
    int magnetron_hp = bosses.hp_magnetron;
    int polarisurge_hp = bosses.hp_polarisurge;
    const int magnetron_max_hp = bosses.hp_magnetron;
    const int polarisurge_max_hp = bosses.hp_polarisurge;
    const int coins_earn = bosses.coins_earn_duo;

    auto applyDuoRevives = [&]() {
        if (magnetron_hp > 0 &&
            magnetron_hp < magnetron_max_hp / 2 &&
            polarisurge_hp > (polarisurge_max_hp * 80) / 100) {
            magnetron_hp = magnetron_max_hp;
            std::cout << "Magnetron se obnovil na max HP." << std::endl;
        }

        if (polarisurge_hp > 0 &&
            polarisurge_hp < polarisurge_max_hp / 5 &&
            magnetron_hp >= magnetron_max_hp / 2) {
            polarisurge_hp = polarisurge_max_hp;
            std::cout << "Polarisurge se obnovil na max HP." << std::endl;
        }
    };

    std::cout << "Duo boss: Magnetron + Polarisurge" << std::endl;
    while (data.hp_player > 0 && (magnetron_hp > 0 || polarisurge_hp > 0)) {
        if (magnetron_hp > 0) {
            magnetron_hp -= data.damage_player;
            if (magnetron_hp < 0) {
                magnetron_hp = 0;
            }
            std::cout << "Player attacks Magnetron! Magnetron HP: " << magnetron_hp << std::endl;
        } else if (polarisurge_hp > 0) {
            polarisurge_hp -= data.damage_player;
            if (polarisurge_hp < 0) {
                polarisurge_hp = 0;
            }
            std::cout << "Player attacks Polarisurge! Polarisurge HP: " << polarisurge_hp << std::endl;
        }

        applyDuoRevives();

        if (magnetron_hp <= 0 && polarisurge_hp <= 0) {
            break;
        }

        int magnetron_damage = 0;
        int polarisurge_damage = 0;

        if (magnetron_hp > 0) {
            magnetron_damage = (polarisurge_max_hp - polarisurge_hp) / 2;
        }
        if (polarisurge_hp > 0) {
            polarisurge_damage = (magnetron_max_hp - magnetron_hp) * 2;
        }

        data.hp_player -= magnetron_damage + polarisurge_damage;

        std::cout << "Magnetron deals " << magnetron_damage << " damage." << std::endl;
        std::cout << "Polarisurge deals " << polarisurge_damage << " damage." << std::endl;
        std::cout << "Player HP: " << data.hp_player << std::endl;
        std::cout << "Magnetron HP: " << magnetron_hp
                  << ", Polarisurge HP: " << polarisurge_hp << std::endl;
    }

    if (data.hp_player > 0) {
        data.player_coins += coins_earn;
        std::cout << "Won the duo boss fight! Earned " << coins_earn << " coins." << std::endl;
        return true;
    }

    std::cout << "Lost the game!" << std::endl;
    return false;
}

int main() {
    GameData data = createGameData();
    BossData bosses = createBossData();

    while (data.level <= 5) {
        std::cout << "-----------day: " << data.day << "-----------" << std::endl;
        std::cout << "----------level: " << data.level << "----------" << std::endl;

        if (data.level > 0) {
            if (data.level == 1) {
                int boss_hp = bosses.hp_mini_boss;
                int boss_damage = bosses.boss_damage_mini;
                int coins_earn = bosses.coins_earn_mini;

                std::cout << "Fighting mini boss with HP: " << boss_hp << std::endl;
                while (data.hp_player > 0 && boss_hp > 0) {
                    boss_hp -= data.damage_player;
                    std::cout << "Player attacks! Boss HP: " << boss_hp << std::endl;
                    if (boss_hp <= 0) {
                        break;
                    }

                    data.hp_player -= boss_damage;
                    std::cout << "Boss attacks! Player HP: " << data.hp_player << std::endl;
                }

                if (data.hp_player > 0) {
                    data.player_coins += coins_earn;
                    std::cout << "Won! Earned " << coins_earn << " coins." << std::endl;
                } else {
                    std::cout << "Lost the game!" << std::endl;
                    break;
                }
            } else {
                if (!fightDualBosses(data, bosses)) {
                    break;
                }
            }
        }

        std::cout << "hp_player: " << data.hp_player << std::endl;
        std::cout << "damage_player: " << data.damage_player << std::endl;
        std::cout << "coins: " << data.player_coins << std::endl;
        std::cout << "Welcome to village!" << std::endl;
        std::cout << "1. Buy knife (level " << data.knife_level + 1 << ")" << std::endl;
        std::cout << "2. Buy armor (level " << data.armor_level + 1 << ")" << std::endl;
        std::cout << "3. Continue to next level" << std::endl;
        std::cout << "4. Stay in village" << std::endl;

        int choice;
        std::cin >> choice;
        if (choice == 1) {
            if (data.knife_level < 4) {
                int cost = (data.knife_level == 0) ? data.knife1_cost : (data.knife_level == 1) ? data.knife2_cost : (data.knife_level == 2) ? data.knife3_cost : data.knife4_cost;
                int dmg_add = (data.knife_level == 0) ? data.knife1_damage : (data.knife_level == 1) ? data.knife2_damage : (data.knife_level == 2) ? data.knife3_damage : data.knife4_damage;
                std::cout << "Knife costs: " << cost << " coins" << std::endl;
                if (data.player_coins >= cost) {
                    data.player_coins -= cost;
                    data.damage_player += dmg_add;
                    data.knife_level++;
                    std::cout << "Bought knife! Damage now " << data.damage_player << std::endl;
                } else {
                    std::cout << "Not enough coins!" << std::endl;
                }
            } else {
                std::cout << "Max knife level reached!" << std::endl;
            }
        } else if (choice == 2) {
            if (data.armor_level < 4) {
                int cost = (data.armor_level == 0) ? data.armor1_cost : (data.armor_level == 1) ? data.armor2_cost : (data.armor_level == 2) ? data.armor3_cost : data.armor4_cost;
                int hp_add = (data.armor_level == 0) ? data.armor1_hp : (data.armor_level == 1) ? data.armor2_hp : (data.armor_level == 2) ? data.armor3_hp : data.armor4_hp;
                std::cout << "Armor costs: " << cost << " coins" << std::endl;
                if (data.player_coins >= cost) {
                    data.player_coins -= cost;
                    data.hp_player += hp_add;
                    data.armor_level++;
                    std::cout << "Bought armor! HP now " << data.hp_player << std::endl;
                } else {
                    std::cout << "Not enough coins!" << std::endl;
                }
            }
            else {
                std::cout << "Max armor level reached!" << std::endl;
            }
        } else if (choice == 3) {
            data.level++;
            std::cout << "Continuing to next level..." << std::endl;
        } else if (choice == 4) {
            data.hp_player += 10;
            std::cout << "Stayed in village, HP increased by 10! HP now " << data.hp_player << std::endl;
        } else {
            std::cout << "Invalid choice, continuing..." << std::endl;
        }

        data.day++;
    }
    return 0;
}
