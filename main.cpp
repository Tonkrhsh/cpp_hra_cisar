#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

int main() {
    int hp_mini_boss, hp_dual_boss, hp_dual_boss2, knife1_damage, knife2_damage, knife3_damage, knife4_damage, knife1_cost, knife2_cost, knife3_cost, knife4_cost;
    int hp_player, damage_player, player_coins;
    int boss_damage_mini, boss_damage_dual, coins_earn_mini, coins_earn_dual;
    int armor1_hp, armor1_cost, armor2_hp, armor2_cost, armor3_hp, armor3_cost, armor4_hp, armor4_cost;
    int knife_level, armor_level;
    int level;
    hp_player = 40;
    player_coins = 0;
    damage_player = 5;
    hp_mini_boss = 20;
    hp_dual_boss = 200;
    hp_dual_boss2 = 200;
    boss_damage_mini = 5;
    boss_damage_dual = 10;
    coins_earn_mini = 10;
    coins_earn_dual = 50;
    armor1_hp = 20; armor1_cost = 50;
    armor2_hp = 50; armor2_cost = 500;
    armor3_hp = 100; armor3_cost = 5000;
    armor4_hp = 200; armor4_cost = 50000;
    knife_level = 0;
    armor_level = 0;
    knife1_damage = 10;
    knife2_damage = 20;
    knife3_damage = 50;
    knife4_damage = 100;
    knife1_cost = 10;
    knife2_cost = 100;
    knife3_cost = 1000;
    knife4_cost = 10000;
    level = 0;
while (level <= 5) {
    std::cout<<"----------level: "<<level<<"----------"<< std::endl;
    if (level > 0) {
        int boss_hp, boss_damage, coins_earn;
        if (level == 1) {
            boss_hp = hp_mini_boss;
            boss_damage = boss_damage_mini;
            coins_earn = coins_earn_mini;
        } else {
            boss_hp = hp_dual_boss;
            boss_damage = boss_damage_dual;
            coins_earn = coins_earn_dual;
        }
        std::cout << "Fighting boss with HP: " << boss_hp << std::endl;
        while (hp_player > 0 && boss_hp > 0) {
            boss_hp -= damage_player;
            std::cout << "Player attacks! Boss HP: " << boss_hp << std::endl;
            if (boss_hp <= 0) break;
            hp_player -= boss_damage;
            std::cout << "Boss attacks! Player HP: " << hp_player << std::endl;
        }
        if (hp_player > 0) {
            player_coins += coins_earn;
            std::cout << "Won! Earned " << coins_earn << " coins." << std::endl;
        } else {
            std::cout << "Lost the game!" << std::endl;
            break;
        }
    }
    // village
    std::cout<<"hp_player: "<<hp_player<< std::endl;
    std::cout<<"damage_player: "<<damage_player<< std::endl;
    std::cout<<"coins: "<<player_coins<< std::endl;
    std::cout << "Welcome to village!" << std::endl;
    std::cout << "1. Buy knife (level " << knife_level + 1 << ")" << std::endl;
    std::cout << "2. Buy armor (level " << armor_level + 1 << ")" << std::endl;
    std::cout << "3. Continue to next level" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        if (knife_level < 4) {
            int cost = (knife_level == 0) ? knife1_cost : (knife_level == 1) ? knife2_cost : (knife_level == 2) ? knife3_cost : knife4_cost;
            int dmg_add = (knife_level == 0) ? knife1_damage : (knife_level == 1) ? knife2_damage : (knife_level == 2) ? knife3_damage : knife4_damage;
            std::cout << "Knife costs: " << cost << " coins" << std::endl;
            if (player_coins >= cost) {
                player_coins -= cost;
                damage_player += dmg_add;
                knife_level++;
                std::cout << "Bought knife! Damage now " << damage_player << std::endl;
            } else {
                std::cout << "Not enough coins!" << std::endl;
            }
        } else {
            std::cout << "Max knife level reached!" << std::endl;
        }
    } else if (choice == 2) {
        if (armor_level < 4) {
            int cost = (armor_level == 0) ? armor1_cost : (armor_level == 1) ? armor2_cost : (armor_level == 2) ? armor3_cost : armor4_cost;
            int hp_add = (armor_level == 0) ? armor1_hp : (armor_level == 1) ? armor2_hp : (armor_level == 2) ? armor3_hp : armor4_hp;
            std::cout << "Armor costs: " << cost << " coins" << std::endl;
            if (player_coins >= cost) {
                player_coins -= cost;
                hp_player += hp_add;
                armor_level++;
                std::cout << "Bought armor! HP now " << hp_player << std::endl;
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
    level++;
}
    return 0;
}