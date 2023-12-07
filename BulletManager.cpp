#include "Player.h"
#include "Bullet.h"
#include "BulletManager.h"

namespace {
    // ��荇�����e�̍ő吔�͌Œ�
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

        auto starter = [this/*�����o�� player ���g������*/](ObjectBase* instance)-> bool {
            // �A�b�p�[�L���X�g�ɂȂ�̂Œ���
            auto bullet = dynamic_cast<Bullet*>(instance);

            return bullet->Start(player->GetX() + (player->GetSizeX() / 2), player->GetY());
        };

        return Spawn(MAX_NUM, generator, starter);
    }
}