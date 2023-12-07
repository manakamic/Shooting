#include <cmath>
#include "DxLib.h"
#include "Enemy.h"
#include "Utility.h"

namespace {
    constexpr auto SPEED = 3;
    constexpr auto SPEED_SIN = 2;
    constexpr auto ZIGZAG_X_RANGE = 300;
    constexpr auto SIN_RATE = 3.0;
    constexpr auto SIN_X_RANGE = 60.0;
    constexpr auto PI = 3.14159265358979;
    constexpr auto DEGREES_180 = 180.0;
}

namespace shooting {

    Enemy::Enemy(int screenWidth, int screenHeight) : ObjectBase(screenWidth, screenHeight) {
        type = Type::Straight;
        baseX = 0;
        baseY = 0;
        zigzag = false;
    }

    bool Enemy::Initialize() {
        // 基底(ObjectBase)クラス の Load 関数をつかってロードする
        int result = Load(_T("res/enemy_a00.png"));

        return result != -1;
    }

    bool Enemy::Start() {
        if (valid) {
            return false;
        }

        SetType();

        x = Utility::Range(0, screenWidth - sizeX);
        y = -sizeY;

        baseX = x;
        baseY = y;

        zigzag = Utility::Range(0, 1) == 0;

        valid = true;

        return true;
    }

    void Enemy::SetType() {
        auto random = Utility::Range(0, 2);

        type = static_cast<Type>(random);
    }

    void Enemy::Process() {
        switch (type) {
        case Type::Straight:
            ProcessStraight();
            break;

        case Type::Zigzag:
            ProcessZigzag();
            break;

        case Type::CosineCurve:
            ProcessSineCurve();
            break;

        default:
            break;
        }
    }

    void Enemy::ProcessStraight() {
        y += SPEED;

        if (y > screenHeight) {
            valid = false;
        }
    }

    void Enemy::ProcessZigzag() {
        auto pi1_4 = PI / 4.0;
        auto cosX = static_cast<double>(SPEED) * std::sin(pi1_4);
        auto sinY = static_cast<double>(SPEED) * std::cos(pi1_4);

        if (zigzag) {
            cosX *= -1.0;

            if (baseX - x >= ZIGZAG_X_RANGE) {
                zigzag = false;
            }
        }
        else {
            if (x - baseX >= ZIGZAG_X_RANGE) {
                zigzag = true;
            }
        }

        x += cosX;
        y += sinY;

        if (y > screenHeight) {
            valid = false;
        }
    }

    void Enemy::ProcessSineCurve() {
        // y 値を角度と考えて処理する
        auto radian = static_cast<double>(y - baseY) * PI / DEGREES_180;

        x = baseX + static_cast<int>(std::sin(radian * SIN_RATE) * SIN_X_RANGE);

        // 横に振幅する分遅めにする
        y += SPEED_SIN;

        if (y > screenHeight) {
            valid = false;
        }
    }
}
