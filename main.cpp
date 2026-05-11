#include <iostream>
#include "boss_data.h"
#include "game_data.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

int main() {
    GameData data = createGameData();
    BossData bosses = createBossData();

while (data.level <= 5) {
    std::cout<<"----------level: "<<data.level<<"----------"<< std::endl;
    if (data.level > 0) {
        int boss_hp, boss_damage, coins_earn;
        if (data.level == 1) {
            boss_hp = bosses.hp_mini_boss;
            boss_damage = bosses.boss_damage_mini;
            coins_earn = bosses.coins_earn_mini;
        } else {
            boss_hp = bosses.hp_dual_boss;
            boss_damage = bosses.boss_damage_dual;
            coins_earn = bosses.coins_earn_dual;
        }
        std::cout << "Fighting boss with HP: " << boss_hp << std::endl;
        while (data.hp_player > 0 && boss_hp > 0) {
            boss_hp -= data.damage_player;
            std::cout << "Player attacks! Boss HP: " << boss_hp << std::endl;
            if (boss_hp <= 0) break;
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
    }
    // village
    std::cout<<"hp_player: "<<data.hp_player<< std::endl;
    std::cout<<"damage_player: "<<data.damage_player<< std::endl;
    std::cout<<"coins: "<<data.player_coins<< std::endl;
    std::cout << "Welcome to village!" << std::endl;
    std::cout << "1. Buy knife (level " << data.knife_level + 1 << ")" << std::endl;
    std::cout << "2. Buy armor (level " << data.armor_level + 1 << ")" << std::endl;
    std::cout << "3. Continue to next level" << std::endl;
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
        } else {
            std::cout << "Max armor level reached!" << std::endl;
        }
    } else if (choice == 3) {
        // continue
    } else {
        std::cout << "Invalid choice, continuing..." << std::endl;
    }
    data.level++;
}
    return 0;
}
