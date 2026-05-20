#ifndef UNTITLED1_RPG_GAME_H
#define UNTITLED1_RPG_GAME_H

#include <string>
#include <vector>

#include "boss_data.h"

enum class AbilityKind {
    single_damage,
    area_damage,
    heal_self,
    drain_damage
};

enum class EncounterType {
    village,
    monsters,
    miniboss,
    final_boss
};

struct Ability {
    std::string name;
    std::string description;
    int cost;
    int power;
    AbilityKind kind;
};

struct ClassDefinition {
    std::string name;
    int max_hp;
    int max_resource;
    int attack;
    std::string resource_name;
    std::vector<Ability> abilities;
};

struct Player {
    std::string class_name;
    std::string resource_name;
    int max_hp;
    int hp;
    int max_resource;
    int resource;
    int gold;
    int level;
    int experience;
    int attack;
    std::vector<Ability> abilities;
};

struct Enemy {
    std::string name;
    int max_hp;
    int hp;
    int attack;
    int experience_reward;
    int gold_reward;
};

struct Encounter {
    EncounterType type;
    std::string name;
    std::vector<Enemy> enemies;
};

int readChoice(int min_value, int max_value);
int randomInt(int min_value, int max_value);
void clampPlayer(Player& player);
void clampEnemy(Enemy& enemy);
bool isAlive(const Enemy& enemy);
bool allEnemiesDefeated(const std::vector<Enemy>& enemies);
void showPlayerStatus(const Player& player);
void showEnemies(const std::vector<Enemy>& enemies);
int chooseEnemyTarget(const std::vector<Enemy>& enemies);
void awardExperience(Player& player, int amount);
std::vector<ClassDefinition> createClasses();
Player chooseClass();
void healPlayer(Player& player, int amount);
void villageMenu(Player& player, const std::string& village_name);
bool playerTurn(Player& player, std::vector<Enemy>& enemies);
void enemiesTurn(Player& player, std::vector<Enemy>& enemies);
void grantEncounterRewards(Player& player, const std::vector<Enemy>& enemies, bool always_gold);
bool fightEncounter(Player& player, std::vector<Enemy> enemies, const std::string& title, bool enemies_start, bool always_gold);
bool fightDualBosses(Player& player, const BossData& bosses);
std::vector<Encounter> createAdventurePath();

#endif
