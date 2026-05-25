#include "boss_data.h"
#include "enum_classy.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Player player = chooseClass();
    BossData bosses = createBossData();
    std::vector<Encounter> path = createAdventurePath();

    std::cout << std::endl;
    std::cout << "Tvoje dobrodruzstvi zacina." << std::endl;

    for (std::size_t day = 0; day < path.size(); ++day) {
        const Encounter& encounter = path[day];
        std::cout << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "Den " << day + 1 << std::endl;
        std::cout << "Lokace: " << encounter.name << std::endl;
        std::cout << "==============================" << std::endl;

        if (encounter.type == EncounterType::village) {
            villageMenu(player, encounter.name);
            continue;
        }

        if (encounter.type == EncounterType::monsters) {
            if (!fightEncounter(player, encounter.enemies, encounter.name, false, false)) {
                return 0;
            }
            continue;
        }

        if (encounter.type == EncounterType::miniboss) {
            if (!fightEncounter(player, encounter.enemies, encounter.name, true, true)) {
                return 0;
            }
            continue;
        }

        if (!fightDualBosses(player, bosses)) {
            return 0;
        }
        return 0;
    }

    std::cout << "Dosel jsi na konec cesty." << std::endl;
    return 0;
}
