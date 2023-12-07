#include "Player.h"
#include "Bullet.h"
#include "BulletManager.h"

namespace {
    // 取り合えず弾の最大数は固定
    constexpr auto MAX_NUM = 8;
}

namespace shooting {

    BulletManager::BulletManager(const int screenWidth, const int screenHeight, Player* player) : ManagerBase(screenWidth, screenHeight) {
        this->player = player;
    }

    BulletManager::~BulletManager() {
        ManagerBase::~ManagerBase();
        player = nullptr;
    }

    bool BulletManager::SpawnBullet() {
        if (player == nullptr) {
            return false;
        }

        auto generator = [](int w, int h) -> Bullet* {
            return new Bullet(w, h);
        };

        auto starter = [this/*メンバの player を使いたい*/](ObjectBase* instance)-> bool {
            // アッパーキャストになるので注意
            auto bullet = dynamic_cast<Bullet*>(instance);

            return bullet->Start(player->GetX() + (player->GetSizeX() / 2), player->GetY());
        };

        return Spawn(MAX_NUM, generator, starter);
    }
}