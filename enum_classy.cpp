#include "enum_classy.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

int readChoice(int min_value, int max_value) {
    int choice;

    while (true) {
        std::cout << "Vyber moznost (" << min_value << "-" << max_value << "): ";
        if (std::cin >> choice && choice >= min_value && choice <= max_value) {
            return choice;
        }

        std::cout << "Neplatna volba. Zkus to znovu." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int randomInt(int min_value, int max_value) {
    return min_value + (std::rand() % (max_value - min_value + 1));
}

void clampPlayer(Player& player) {
    player.hp = std::clamp(player.hp, 0, player.max_hp);
    player.resource = std::clamp(player.resource, 0, player.max_resource);
    player.gold = std::max(player.gold, 0);
    player.experience = std::max(player.experience, 0);
}

void clampEnemy(Enemy& enemy) {
    enemy.hp = std::clamp(enemy.hp, 0, enemy.max_hp);
}

bool isAlive(const Enemy& enemy) {
    return enemy.hp > 0;
}

bool allEnemiesDefeated(const std::vector<Enemy>& enemies) {
    for (const Enemy& enemy : enemies) {
        if (enemy.hp > 0) {
            return false;
        }
    }
    return true;
}

void showPlayerStatus(const Player& player) {
    std::cout << "Class: " << player.class_name << std::endl;
    std::cout << "HP: " << player.hp << "/" << player.max_hp << std::endl;
    std::cout << player.resource_name << ": " << player.resource << "/" << player.max_resource << std::endl;
    std::cout << "Utok: " << player.attack << std::endl;
    std::cout << "Zlato: " << player.gold << std::endl;
    std::cout << "Level: " << player.level << std::endl;
    std::cout << "XP: " << player.experience << std::endl;
}

void showEnemies(const std::vector<Enemy>& enemies) {
    for (std::size_t i = 0; i < enemies.size(); ++i) {
        std::cout << i + 1 << ". " << enemies[i].name
                  << " HP " << enemies[i].hp << "/" << enemies[i].max_hp;
        if (!isAlive(enemies[i])) {
            std::cout << " (porazen)";
        }
        std::cout << std::endl;
    }
}

int chooseEnemyTarget(const std::vector<Enemy>& enemies) {
    int alive_count = 0;
    int last_alive_index = -1;

    for (std::size_t i = 0; i < enemies.size(); ++i) {
        if (isAlive(enemies[i])) {
            alive_count++;
            last_alive_index = static_cast<int>(i);
        }
    }

    if (alive_count == 1) {
        std::cout << "Cil je automaticky: " << enemies[last_alive_index].name << std::endl;
        return last_alive_index;
    }

    while (true) {
        std::cout << "Vyber cil utoku:" << std::endl;
        showEnemies(enemies);
        int choice = readChoice(1, static_cast<int>(enemies.size()));
        if (isAlive(enemies[choice - 1])) {
            return choice - 1;
        }
        std::cout << "Na porazene monstrum utocit nemuzes." << std::endl;
    }
}

void awardExperience(Player& player, int amount) {
    player.experience += amount;
    std::cout << "Ziskal jsi " << amount << " XP." << std::endl;

    while (player.experience >= player.level * 20) {
        player.experience -= player.level * 20;
        player.level++;
        player.max_hp += 5;
        player.max_resource += 3;
        player.attack += 1;
        player.hp = player.max_hp;
        player.resource = player.max_resource;

        std::cout << "Novy level postavy. Ziskavas:" << std::endl;
        std::cout << "Max zivot +5 => " << player.max_hp << std::endl;
        std::cout << "Max " << player.resource_name << " +3 => " << player.max_resource << std::endl;
        std::cout << "Utok +1 => " << player.attack << std::endl;
        std::cout << "Zivoty i " << player.resource_name << " byly doplneny." << std::endl;
    }
}

std::vector<ClassDefinition> createClasses() {
    return {
        {
            "Paladin",
            28,
            10,
            5,
            "Mana",
            {
                {"Uder svetlem", "Zpusobi 3 poskozeni vsem nepritelum", 2, 3, AbilityKind::area_damage},
                {"Posveceni", "Vyleci te o 6 zivotu", 2, 6, AbilityKind::heal_self}
            }
        },
        {
            "Lovec",
            24,
            12,
            6,
            "Energie",
            {
                {"Dvojity vystrel", "Zpusobi 9 poskozeni jednomu cily", 3, 9, AbilityKind::single_damage},
                {"Sipovy dest", "Zpusobi 4 poskozeni vsem nepritelum", 4, 4, AbilityKind::area_damage}
            }
        },
        {
            "Mag",
            22,
            16,
            4,
            "Mana",
            {
                {"Ohniva koule", "Zpusobi 10 poskozeni jednomu cily", 4, 10, AbilityKind::single_damage},
                {"Bleskovy puls", "Zpusobi 5 poskozeni vsem nepritelum", 5, 5, AbilityKind::area_damage}
            }
        },
        {
            "Warlock",
            25,
            14,
            5,
            "Mana",
            {
                {"Stinovy siphon", "Zpusobi 7 poskozeni a tebe vyleci o 3", 3, 7, AbilityKind::drain_damage},
                {"Prokleti", "Zpusobi 4 poskozeni vsem nepritelum", 4, 4, AbilityKind::area_damage}
            }
        }
    };
}

Player chooseClass() {
    const std::vector<ClassDefinition> classes = createClasses();

    while (true) {
        std::cout << "Vyber si classu:" << std::endl;
        for (std::size_t i = 0; i < classes.size(); ++i) {
            std::cout << i + 1 << ". " << classes[i].name << std::endl;
        }

        const ClassDefinition& selected = classes[readChoice(1, static_cast<int>(classes.size())) - 1];

        std::cout << std::endl;
        std::cout << "Class: " << selected.name << std::endl;
        std::cout << "Statistiky:" << std::endl;
        std::cout << "Zivot - " << selected.max_hp << "/" << selected.max_hp << std::endl;
        std::cout << "Utok - " << selected.attack << std::endl;
        std::cout << selected.resource_name << " - " << selected.max_resource << "/" << selected.max_resource << std::endl;
        std::cout << "Schopnosti:" << std::endl;
        std::cout << "Utok - Zakladni utok za " << selected.attack << " poskozeni" << std::endl;
        for (const Ability& ability : selected.abilities) {
            std::cout << ability.name << " - " << ability.description
                      << " (stoji " << ability.cost << " " << selected.resource_name << ")" << std::endl;
        }

        std::cout << "1. Potvrdit classu" << std::endl;
        std::cout << "2. Vybrat jinou classu" << std::endl;
        int confirmation = readChoice(1, 2);
        if (confirmation == 1) {
            return {
                selected.name,
                selected.resource_name,
                selected.max_hp,
                selected.max_hp,
                selected.max_resource,
                selected.max_resource,
                20,
                1,
                0,
                selected.attack,
                selected.abilities
            };
        }
    }
}

void healPlayer(Player& player, int amount) {
    player.hp = std::min(player.max_hp, player.hp + amount);
}

void villageMenu(Player& player, const std::string& village_name) {
    while (true) {
        std::cout << std::endl;
        std::cout << "Dorazil jsi do vesnice: " << village_name << std::endl;
        showPlayerStatus(player);
        std::cout << "1. Doplneni zivotu na maximum (10 zlata)" << std::endl;
        std::cout << "2. Vylepsit max zivoty +5 (25 zlata)" << std::endl;
        std::cout << "3. Vylepsit max mana/energie +3 (20 zlata)" << std::endl;
        std::cout << "4. Vylepsit utok +1 (30 zlata)" << std::endl;
        std::cout << "5. Odejit z vesnice" << std::endl;

        int choice = readChoice(1, 5);
        if (choice == 1) {
            if (player.gold < 10) {
                std::cout << "Nemas dost zlata." << std::endl;
                continue;
            }
            player.gold -= 10;
            player.hp = player.max_hp;
            std::cout << "Zivoty byly doplneny." << std::endl;
        } else if (choice == 2) {
            if (player.gold < 25) {
                std::cout << "Nemas dost zlata." << std::endl;
                continue;
            }
            player.gold -= 25;
            player.max_hp += 5;
            player.hp = player.max_hp;
            std::cout << "Max zivoty byly zvyseny na " << player.max_hp << "." << std::endl;
        } else if (choice == 3) {
            if (player.gold < 20) {
                std::cout << "Nemas dost zlata." << std::endl;
                continue;
            }
            player.gold -= 20;
            player.max_resource += 3;
            player.resource = player.max_resource;
            std::cout << "Max " << player.resource_name << " bylo zvyseno na "
                      << player.max_resource << "." << std::endl;
        } else if (choice == 4) {
            if (player.gold < 30) {
                std::cout << "Nemas dost zlata." << std::endl;
                continue;
            }
            player.gold -= 30;
            player.attack += 1;
            std::cout << "Utok byl zvysen na " << player.attack << "." << std::endl;
        } else {
            std::cout << "Opoustis vesnici." << std::endl;
            break;
        }
    }
}

bool playerTurn(Player& player, std::vector<Enemy>& enemies) {
    while (true) {
        std::cout << std::endl;
        showPlayerStatus(player);
        showEnemies(enemies);
        std::cout << "1. Zakladni utok" << std::endl;
        std::cout << "2. " << player.abilities[0].name << std::endl;
        std::cout << "3. " << player.abilities[1].name << std::endl;
        std::cout << "4. Zobrazit stav znovu" << std::endl;

        int choice = readChoice(1, 4);
        if (choice == 4) {
            continue;
        }

        if (choice == 1) {
            int target = chooseEnemyTarget(enemies);
            enemies[target].hp -= player.attack;
            clampEnemy(enemies[target]);
            std::cout << "Zasahl jsi " << enemies[target].name << " za " << player.attack << " poskozeni." << std::endl;
            return true;
        }

        Ability ability = player.abilities[choice - 2];
        if (player.resource < ability.cost) {
            std::cout << "Nemas dost " << player.resource_name << "." << std::endl;
            continue;
        }

        player.resource -= ability.cost;
        if (ability.kind == AbilityKind::single_damage) {
            int target = chooseEnemyTarget(enemies);
            enemies[target].hp -= ability.power;
            clampEnemy(enemies[target]);
            std::cout << "Pouzil jsi " << ability.name << " na " << enemies[target].name
                      << " za " << ability.power << " poskozeni." << std::endl;
        } else if (ability.kind == AbilityKind::area_damage) {
            for (Enemy& enemy : enemies) {
                if (isAlive(enemy)) {
                    enemy.hp -= ability.power;
                    clampEnemy(enemy);
                }
            }
            std::cout << "Pouzil jsi " << ability.name << " na vsechny nepritele." << std::endl;
        } else if (ability.kind == AbilityKind::heal_self) {
            healPlayer(player, ability.power);
            std::cout << "Pouzil jsi " << ability.name << " a vylecil se o "
                      << ability.power << " zivotu." << std::endl;
        } else if (ability.kind == AbilityKind::drain_damage) {
            int target = chooseEnemyTarget(enemies);
            enemies[target].hp -= ability.power;
            clampEnemy(enemies[target]);
            healPlayer(player, 3);
            std::cout << "Pouzil jsi " << ability.name << " na " << enemies[target].name
                      << " a vysal z nej silu." << std::endl;
        }

        clampPlayer(player);
        return true;
    }
}

void enemiesTurn(Player& player, std::vector<Enemy>& enemies) {
    for (Enemy& enemy : enemies) {
        if (!isAlive(enemy) || player.hp <= 0) {
            continue;
        }

        player.hp -= enemy.attack;
        clampPlayer(player);
        std::cout << enemy.name << " utoci za " << enemy.attack
                  << " poskozeni. Tve HP: " << player.hp << "/" << player.max_hp << std::endl;
    }
}

void grantEncounterRewards(Player& player, const std::vector<Enemy>& enemies, bool always_gold) {
    int total_xp = 0;
    int total_gold = 0;

    for (const Enemy& enemy : enemies) {
        total_xp += enemy.experience_reward;
        if (always_gold) {
            total_gold += enemy.gold_reward;
        } else if (randomInt(0, 1) == 1) {
            total_gold += enemy.gold_reward;
            std::cout << enemy.name << " mel u sebe " << enemy.gold_reward << " zlata." << std::endl;
        } else {
            std::cout << enemy.name << " u sebe nemel zadne zlato." << std::endl;
        }
    }

    awardExperience(player, total_xp);
    player.gold += total_gold;
    std::cout << "Ziskal jsi celkem " << total_gold << " zlata." << std::endl;
}

bool fightEncounter(Player& player, std::vector<Enemy> enemies, const std::string& title, bool enemies_start, bool always_gold) {
    std::cout << std::endl;
    std::cout << "Souboj: " << title << std::endl;
    std::cout << "Narazil jsi na " << enemies.size() << " nepritele." << std::endl;

    bool players_turn_now = !enemies_start;
    while (player.hp > 0 && !allEnemiesDefeated(enemies)) {
        if (players_turn_now) {
            playerTurn(player, enemies);
        } else {
            enemiesTurn(player, enemies);
        }

        clampPlayer(player);
        for (Enemy& enemy : enemies) {
            clampEnemy(enemy);
        }

        if (player.hp <= 0 || allEnemiesDefeated(enemies)) {
            break;
        }
        players_turn_now = !players_turn_now;
    }

    if (player.hp <= 0) {
        std::cout << "Padl jsi v boji. Hra konci." << std::endl;
        return false;
    }

    std::cout << "Zvitezil jsi v souboji." << std::endl;
    grantEncounterRewards(player, enemies, always_gold);
    return true;
}

bool fightDualBosses(Player& player, const BossData& bosses) {
    Enemy magnetron{"Magnetron", bosses.hp_magnetron, bosses.hp_magnetron, 0, 30, 0};
    Enemy polarisurge{"Polarisurge", bosses.hp_polarisurge, bosses.hp_polarisurge, 0, 30, 0};

    auto applyDuoRevives = [&]() {
        if (magnetron.hp > 0 &&
            magnetron.hp < magnetron.max_hp / 2 &&
            polarisurge.hp > (polarisurge.max_hp * 80) / 100) {
            magnetron.hp = magnetron.max_hp;
            std::cout << "Magnetron se obnovil na max HP." << std::endl;
        }

        if (polarisurge.hp > 0 &&
            polarisurge.hp < polarisurge.max_hp / 5 &&
            magnetron.hp >= magnetron.max_hp / 2) {
            polarisurge.hp = polarisurge.max_hp;
            std::cout << "Polarisurge se obnovil na max HP." << std::endl;
        }
    };

    std::cout << std::endl;
    std::cout << "Hlavni boss: Duo boss Magnetron a Polarisurge" << std::endl;
    std::cout << "Bossove zacinaji jako prvni." << std::endl;

    bool bosses_turn = true;
    while (player.hp > 0 && (magnetron.hp > 0 || polarisurge.hp > 0)) {
        if (bosses_turn) {
            applyDuoRevives();

            int magnetron_damage = 0;
            int polarisurge_damage = 0;

            if (magnetron.hp > 0) {
                magnetron_damage = (polarisurge.max_hp - polarisurge.hp) / 2;
            }
            if (polarisurge.hp > 0) {
                polarisurge_damage = (magnetron.max_hp - magnetron.hp) * 2;
            }

            player.hp -= magnetron_damage + polarisurge_damage;
            clampPlayer(player);

            std::cout << "Magnetron zpusobil " << magnetron_damage << " poskozeni." << std::endl;
            std::cout << "Polarisurge zpusobil " << polarisurge_damage << " poskozeni." << std::endl;
            std::cout << "Tve HP: " << player.hp << "/" << player.max_hp << std::endl;
        } else {
            std::cout << std::endl;
            std::cout << "Duo boss status:" << std::endl;
            std::cout << "1. Magnetron HP " << magnetron.hp << "/" << magnetron.max_hp << std::endl;
            std::cout << "2. Polarisurge HP " << polarisurge.hp << "/" << polarisurge.max_hp << std::endl;
            std::cout << "Vyber akci:" << std::endl;
            std::cout << "1. Zakladni utok" << std::endl;
            std::cout << "2. " << player.abilities[0].name << std::endl;
            std::cout << "3. " << player.abilities[1].name << std::endl;
            std::cout << "4. Stav postavy" << std::endl;

            while (true) {
                int action = readChoice(1, 4);
                if (action == 4) {
                    showPlayerStatus(player);
                    continue;
                }

                if (action == 1) {
                    std::cout << "1. Magnetron" << std::endl;
                    std::cout << "2. Polarisurge" << std::endl;
                    int target = readChoice(1, 2);
                    Enemy* chosen = (target == 1) ? &magnetron : &polarisurge;
                    if (!isAlive(*chosen)) {
                        std::cout << "Tento boss uz je porazen." << std::endl;
                        continue;
                    }
                    chosen->hp -= player.attack;
                    clampEnemy(*chosen);
                    std::cout << "Utocis na " << chosen->name << " za " << player.attack << " poskozeni." << std::endl;
                    break;
                }

                Ability ability = player.abilities[action - 2];
                if (player.resource < ability.cost) {
                    std::cout << "Nemas dost " << player.resource_name << "." << std::endl;
                    continue;
                }

                player.resource -= ability.cost;
                if (ability.kind == AbilityKind::heal_self) {
                    healPlayer(player, ability.power);
                    std::cout << "Vylecil ses o " << ability.power << " zivotu." << std::endl;
                } else if (ability.kind == AbilityKind::area_damage) {
                    if (magnetron.hp > 0) {
                        magnetron.hp -= ability.power;
                        clampEnemy(magnetron);
                    }
                    if (polarisurge.hp > 0) {
                        polarisurge.hp -= ability.power;
                        clampEnemy(polarisurge);
                    }
                    std::cout << "Zasahl jsi oba bossy schopnosti " << ability.name << "." << std::endl;
                } else if (ability.kind == AbilityKind::drain_damage || ability.kind == AbilityKind::single_damage) {
                    std::cout << "1. Magnetron" << std::endl;
                    std::cout << "2. Polarisurge" << std::endl;
                    int target = readChoice(1, 2);
                    Enemy* chosen = (target == 1) ? &magnetron : &polarisurge;
                    if (!isAlive(*chosen)) {
                        std::cout << "Tento boss uz je porazen." << std::endl;
                        player.resource += ability.cost;
                        continue;
                    }
                    chosen->hp -= ability.power;
                    clampEnemy(*chosen);
                    std::cout << "Pouzil jsi " << ability.name << " na " << chosen->name << "." << std::endl;
                    if (ability.kind == AbilityKind::drain_damage) {
                        healPlayer(player, 3);
                    }
                }

                clampPlayer(player);
                applyDuoRevives();
                break;
            }
        }

        if (player.hp <= 0 || (magnetron.hp <= 0 && polarisurge.hp <= 0)) {
            break;
        }
        bosses_turn = !bosses_turn;
    }

    if (player.hp <= 0) {
        std::cout << "Duo boss te porazil. Hra konci." << std::endl;
        return false;
    }

    player.gold += bosses.coins_earn_duo;
    awardExperience(player, 60);
    std::cout << "Porazil jsi hlavniho bosse a ziskal " << bosses.coins_earn_duo << " zlata." << std::endl;
    std::cout << "Vyhral jsi celou hru!" << std::endl;
    return true;
}

std::vector<Encounter> createAdventurePath() {
    return {
        {EncounterType::village, "Startovni vesnice Briza", {}},
        {EncounterType::monsters, "Lesni stezka", {{"Goblin", 10, 10, 3, 8, 6}}},
        {EncounterType::monsters, "Rozbite pole", {{"Divoky vlk", 11, 11, 4, 8, 6}}},
        {EncounterType::monsters, "Zapomenuty brod", {{"Kostlivec", 10, 10, 3, 8, 7}, {"Pavouk", 9, 9, 3, 8, 5}}},
        {EncounterType::miniboss, "Mini-boss: Troll nacelnik", {{"Troll nacelnik", 26, 26, 6, 18, 20}}},
        {EncounterType::village, "Dubova ves", {}},
        {EncounterType::monsters, "Loviste", {{"Bandita", 12, 12, 4, 8, 7}}},
        {EncounterType::monsters, "Skalni prusmyk", {{"Ghul", 12, 12, 4, 8, 7}, {"Harpyje", 11, 11, 4, 8, 7}}},
        {EncounterType::monsters, "Studena jeskyne", {{"Ledovy vlk", 13, 13, 5, 8, 8}, {"Kultista", 12, 12, 4, 8, 8}}},
        {EncounterType::miniboss, "Mini-boss: Kamenny obr", {{"Kamenny obr", 30, 30, 7, 20, 24}}},
        {EncounterType::village, "Ricni pristav", {}},
        {EncounterType::monsters, "Mlha nad mokradem", {{"Bazinni sliz", 13, 13, 4, 8, 8}, {"Netopyr", 9, 9, 3, 8, 5}}},
        {EncounterType::monsters, "Spaleny haj", {{"Ohnivy imp", 11, 11, 5, 8, 8}, {"Divocak", 14, 14, 4, 8, 7}}},
        {EncounterType::monsters, "Temna plan", {{"Krysar", 12, 12, 4, 8, 7}, {"Zlobr", 16, 16, 5, 8, 9}, {"Stin", 10, 10, 5, 8, 9}}},
        {EncounterType::village, "Posledni tabor", {}},
        {EncounterType::final_boss, "Hlavni boss: Magnetron a Polarisurge", {}}
    };
}
