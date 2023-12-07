#include "DxLib.h"
#include "BulletManager.h"
#include "Player.h"

namespace {
    // 取り合えず移動速度は固定
    // 移動速度はメンバー変数にして可変にしても良いかも
    // EX) アイテムを取るとスピードアップする等
    constexpr auto SPEED = 10;
}

namespace shooting {

    // 派生クラスのコンストラクタに : で続けて基底クラスのコンストラクタを呼べる
    Player::Player(Input* input, const int screenWidth, const int screenHeight) : ObjectBase(screenWidth, screenHeight) {
        // Game class から渡された Input クラスを保持するだけ
        this->input = input;
        bulletManager = nullptr;
    }

    Player::~Player() {
        ObjectBase::~ObjectBase();

        if (input != nullptr) {
            // Game class から渡された Input クラスを保持していただけなので nullptr 代入のみ
            input = nullptr;
        }
    }

    bool Player::Initialize() {
        // 基底(ObjectBase)クラス の Load 関数をつかってロードする
        int result = Load(_T("res/player00.png"));

        // 画面の中央下に出現させる
        x = 1280 / 2;
        y = 720 - 64;

        valid = result != -1;

        return valid;
    }

    void Player::Process() {
        ProcessInput();
        CheckPosition();
    }

    void Player::ProcessInput() {
        if (input == nullptr) {
            return;
        }

        if (input->OnKey(PAD_INPUT_LEFT)) {
            x -= SPEED;
        }

        if (input->OnKey(PAD_INPUT_RIGHT)) {
            x += SPEED;
        }

        if (input->OnKey(PAD_INPUT_UP)) {
            y -= SPEED;
        }

        if (input->OnKey(PAD_INPUT_DOWN)) {
            y += SPEED;
        }

        // space key
        if (input->TriggerKey(PAD_INPUT_10)) {
            if (bulletManager != nullptr) {
                bulletManager->SpawnBullet();
            }
        }
    }

    void Player::CheckPosition() {
        if (x < 0) {
            x = 0;
        }

        if (y < 0) {
            y = 0;
        }

        int maxWidth = screenWidth - sizeX;

        if (x > maxWidth) {
            x = maxWidth;
        }

        int maxHeight = screenHeight - sizeY;

        if (y > maxHeight) {
            y = maxHeight;
        }
    }
}