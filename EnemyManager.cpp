#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"

namespace {
    // 取り合えず敵の最大数は固定
    constexpr auto MAX_NUM = 8;
    constexpr auto SPAWN_INTERVAL = 45;
}

namespace shooting {

    EnemyManager::EnemyManager(const int screenWidth, const int screenHeight, Player* player) : ManagerBase(screenWidth, screenHeight) {
        spawnCounter = 0;
        this->player = player;
    }

    EnemyManager::~EnemyManager() {
        ManagerBase::~ManagerBase();
        player = nullptr;
    }

    void EnemyManager::Process() {
        if (player == nullptr) {
            return;
        }

        spawnCounter++;

        if (spawnCounter >= SPAWN_INTERVAL) {
            spawnCounter = 0;

            SpawnEnemy();
        }

        ManagerBase::Process();
    }

    bool EnemyManager::SpawnEnemy() {
        if (player == nullptr) {
            return false;
        }

        auto generator = [](int w, int h) -> Enemy* {
            return new Enemy(w, h);
        };

        auto starter = [](ObjectBase* instance)-> bool {
            // アッパーキャストになるので注意
            auto enemy = dynamic_cast<Enemy*>(instance);

            return enemy->Start();
        };

        return Spawn(MAX_NUM, generator, starter);
    }
}
