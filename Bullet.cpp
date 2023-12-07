#include "Bullet.h"

namespace {
    constexpr auto SPEED = 20;
}

namespace shooting {

    Bullet::Bullet(const int screenWidth, const int screenHeight) : ObjectBase(screenWidth, screenHeight) {
    }

    bool Bullet::Initialize() {
        // 基底(ObjectBase)クラス の Load 関数をつかってロードする
        int result = Load(_T("res/player_bullet.png"));

        return result != -1;
    }

    bool Bullet::Start(const int x, const int y) {
        if (valid) {
            return false;
        }

        this->x = x;
        this->y = y;
        valid = true;

        return true;
    }

    void Bullet::Process() {
        y -= SPEED;

        if (y < 0) {
            valid = false;
        }
    }
}
