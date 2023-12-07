#include "DxLib.h"
#include "BulletManager.h"
#include "Player.h"

namespace {
    // ��荇�����ړ����x�͌Œ�
    // �ړ����x�̓����o�[�ϐ��ɂ��ĉςɂ��Ă��ǂ�����
    // EX) �A�C�e�������ƃX�s�[�h�A�b�v���铙
    constexpr auto SPEED = 10;
}

namespace shooting {

    // �h���N���X�̃R���X�g���N�^�� : �ő����Ċ��N���X�̃R���X�g���N�^���Ăׂ�
    Player::Player(Input* input, const int screenWidth, const int screenHeight) : ObjectBase(screenWidth, screenHeight) {
        // Game class ����n���ꂽ Input �N���X��ێ����邾��
        this->input = input;
        bulletManager = nullptr;
    }

    Player::~Player() {
        ObjectBase::~ObjectBase();

        if (input != nullptr) {
            // Game class ����n���ꂽ Input �N���X��ێ����Ă��������Ȃ̂� nullptr ����̂�
            input = nullptr;
        }
    }

    bool Player::Initialize() {
        // ���(ObjectBase)�N���X �� Load �֐��������ă��[�h����
        int result = Load(_T("res/player00.png"));

        // ��ʂ̒������ɏo��������
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