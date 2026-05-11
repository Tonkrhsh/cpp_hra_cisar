#include "game_data.h"

GameData createGameData() {
    GameData data{};

    data.hp_player = 40;
    data.player_coins = 0;
    data.damage_player = 5;

    data.armor1_hp = 20;
    data.armor1_cost = 50;
    data.armor2_hp = 50;
    data.armor2_cost = 500;
    data.armor3_hp = 100;
    data.armor3_cost = 5000;
    data.armor4_hp = 200;
    data.armor4_cost = 50000;

    data.knife_level = 0;
    data.armor_level = 0;

    data.knife1_damage = 10;
    data.knife2_damage = 20;
    data.knife3_damage = 50;
    data.knife4_damage = 100;
    data.knife5_damage = 200;

    data.knife1_cost = 10;
    data.knife2_cost = 20;
    data.knife3_cost = 30;
    data.knife4_cost = 40;
    data.knife5_cost = 50;


    data.level = 0;
    data.day = 1;

    return data;
}
