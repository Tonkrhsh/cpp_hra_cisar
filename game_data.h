#ifndef UNTITLED1_GAME_DATA_H
#define UNTITLED1_GAME_DATA_H

struct GameData {
    int knife1_damage;
    int knife2_damage;
    int knife3_damage;
    int knife4_damage;
    int knife5_damage;

    int knife1_cost;
    int knife2_cost;
    int knife3_cost;
    int knife4_cost;
    int knife5_cost;

    int hp_player;
    int damage_player;
    int player_coins;

    int armor1_hp;
    int armor2_hp;
    int armor3_hp;
    int armor4_hp;

     int armor1_cost;
    int armor2_cost;
    int armor3_cost;
    int armor4_cost;

    int knife_level;
    int armor_level;
    int level;
    int day;
};

GameData createGameData();

#endif
