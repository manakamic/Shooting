// 基本は自身のヘッダーをインクルードする
// 後は実装(＊)に応じて他のヘッダーをインクルードする
// ＊class 等の定義をプログラムで使用する場合
#include "Game.h"
#include "Utility.h"
#include "DxLib.h"

// ヘッダーの namespace と合わせる
namespace shooting {

    // class の実装の基本ルールは "クラス名::" と必ず関数の実装の先頭に付ける
    // この場合 "Game::" となる
    // ＋ コンストラクタは 戻り値無しのクラス名と同名の関数なので Game()
    // つまり Game::Game() となる
    Game::Game(const int screenWidth, const int screenHeight) {
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;
        bgHandle = -1;
        input = nullptr;
        player = nullptr;
        bulletManager = nullptr;
        enemyManager = nullptr;
        effectManager = nullptr;
    }

    // virtual はヘッダーの定義にしか記述しなくて良い
    Game::~Game() {
        if (bgHandle != -1) {
            DeleteGraph(bgHandle);
            bgHandle = -1;
        }

        if (player != nullptr) {
            delete player;
            player = nullptr;
        }

        if (input != nullptr) {
            delete input;
            input = nullptr;
        }

        if (bulletManager != nullptr) {
            delete bulletManager;
            bulletManager = nullptr;
        }

        if (enemyManager != nullptr) {
            delete enemyManager;
            enemyManager = nullptr;
        }

        if (effectManager != nullptr) {
            delete effectManager;
            effectManager = nullptr;
        }
    }

    bool Game::Initialize() {
        if (bgHandle == -1) {
            bgHandle = LoadGraph(_T("res/bg_space.png"));
        }

        if (input == nullptr) {
            input = new Input();
        }

        bool resultPlayer = InitializePlayer();

        if (bulletManager == nullptr) {
            bulletManager = new BulletManager(screenWidth, screenHeight, player);
        }

        if (player != nullptr) {
            player->SetBulletManager(bulletManager);
        }

        if (enemyManager == nullptr) {
            enemyManager = new EnemyManager(screenWidth, screenHeight, player);
        }

        if (effectManager == nullptr) {
            effectManager = new EffectManager(screenWidth, screenHeight);
        }

        return CheckInitialize();
    }

    bool Game::InitializePlayer() {
        if (player == nullptr) {
            player = new Player(input, screenWidth, screenHeight);

            if (player != nullptr) {
                return player->Initialize();
            }
        }

        return false;
    }

    bool Game::CheckInitialize() const {
        return (bgHandle != -1) &&
               (input != nullptr) &&
               (player != nullptr) &&
               (bulletManager != nullptr) &&
               (enemyManager != nullptr) &&
               (effectManager != nullptr);
    }

    bool Game::Process() {
        if (input != nullptr) {
            input->Process();
        }

        if (player != nullptr) {
            player->Process();
        }

        if (bulletManager != nullptr) {
            bulletManager->Process();
        }

        if (enemyManager != nullptr) {
            enemyManager->Process();
        }

        if (effectManager != nullptr) {
            effectManager->Process();
        }

        ProcessCollision();

        return CheckInitialize();
    }

    void Game::ProcessCollision() {
        if (!CheckInitialize()) {
            return;
        }

        auto bulletList = bulletManager->GetManagedList();
        auto enemyList = enemyManager->GetManagedList();
        auto playerRect = player->GetRect();

        for (auto& enemy : enemyList) {
            if (enemy == nullptr || !enemy->IsValid()) {
                continue;
            }

            for (auto& bullet : bulletList) {
                if (bullet == nullptr || !bullet->IsValid()) {
                    continue;
                }

                auto enemyRect = enemy->GetRect();

                if (Utility::Collision(enemyRect, bullet->GetRect())) {
                    enemy->End();
                    bullet->End();

                    effectManager->SpawnEffect(enemyRect.x, enemyRect.y);
                }
            }

            if (enemy->IsValid()) {
                if (Utility::Collision(enemy->GetRect(), playerRect)) {
                    enemy->End();
                    //player->End();
                }
            }
        }
    }

    bool Game::Render() const {
        if (bgHandle != -1) {
            DrawGraph(0, 0, bgHandle, FALSE);
        }

        if (player != nullptr) {
            player->Render();
        }

        if (bulletManager != nullptr) {
            bulletManager->Render();
        }

        if (enemyManager != nullptr) {
            enemyManager->Render();
        }

        if (effectManager != nullptr) {
            effectManager->Render();
        }

        return CheckInitialize();
    }
}
