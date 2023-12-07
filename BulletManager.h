#pragma once
#include "ManagerBase.h"

namespace shooting {
    class Player;

    class BulletManager : public ManagerBase {
    public:
        BulletManager(const int screenWidth, const int screenHeight, Player* player);
        virtual ~BulletManager();

        bool SpawnBullet();

    private:
        Player* player;
    };
}
