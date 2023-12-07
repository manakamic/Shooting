// ��{�͎��g�̃w�b�_�[���C���N���[�h����
// ��͎���(��)�ɉ����đ��̃w�b�_�[���C���N���[�h����
// ��class ���̒�`���v���O�����Ŏg�p����ꍇ
#include "Game.h"
#include "Utility.h"
#include "DxLib.h"

// �w�b�_�[�� namespace �ƍ��킹��
namespace shooting {

    // class �̎����̊�{���[���� "�N���X��::" �ƕK���֐��̎����̐擪�ɕt����
    // ���̏ꍇ "Game::" �ƂȂ�
    // �{ �R���X�g���N�^�� �߂�l�����̃N���X���Ɠ����̊֐��Ȃ̂� Game()
    // �܂� Game::Game() �ƂȂ�
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

    // virtual �̓w�b�_�[�̒�`�ɂ����L�q���Ȃ��ėǂ�
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
