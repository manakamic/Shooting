#pragma once
#include "ManagerBase.h"

namespace shooting {
    class Player;

    class EnemyManager : public ManagerBase {
    public:
        EnemyManager(const int screenWidth, const int screenHeight, Player* player);
        virtual ~EnemyManager();

        void Process() override;

    private:
        bool SpawnEnemy();

        int spawnCounter;
        Player* player;
    };
}
