// visual studio �������ő}�����Ă���
// �w�b�_�[�ɂ͕K���L�q����
#pragma once
#include "Input.h"
#include "Player.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "EffectManager.h"

// ��{�I�� namespace �͂����������ǂ�
// (�����Ƃ���薳����Ζ����Ɏg�p���Ȃ��Ƃ��ǂ�)
namespace shooting {

    // �N���X�̊�{�̓R���X�g���N�^�ƃf�X�g���N�^
    class Game {
    public: // �A�N�Z�X�C���q
        // �N���X���Ɠ����̖߂�l�Ȃ��̊֐����R���X�g���N�^�ƂȂ�
        // �����L��ŕ����̃R���X�g���N�^��p�ӂ��Ă��ǂ�
        Game(const int screenWidth, const int screenHeight);
        // �N���X���Ɠ����̖߂�l�Ȃ��̊֐��Ő擪�� ~ ���t���Ă���̂��f�X�g���N�^
        // �p��������ꍇ�l�� virtual ��t����
        // (�܂��̓f�X�g���N�^�� virtual ~XXXX() �ƌ����`�ɂ��܂��ėǂ�)
        virtual ~Game();

        // Game �N���X�̏������֐��Ƃ��Đ݌v
        // ���O�� Init() �ł����ł��ǂ����������Ă��鑼�̃N���X�Ȃǂ̖��̂Ƒ�����Ɨǂ�
        bool Initialize();

        // ���C�����[�v�ŕ`��ȊO�̏���(�̑S��)���ĂԊ֐��Ƃ��Đ݌v
        // ���O�� Update() �ł����ł��ǂ����������Ă��鑼�̃N���X�Ȃǂ̖��̂Ƒ�����Ɨǂ�
        bool Process();

        // ���C�����[�v�ŕ`��̏���(�̑S��)���ĂԊ֐��Ƃ��Đ݌v
        // ���O�� Draw() �ł����ł��ǂ����������Ă��鑼�̃N���X�Ȃǂ̖��̂Ƒ�����Ɨǂ�
        bool Render() const;

    private:
        bool InitializePlayer();
        bool CheckInitialize() const;

        void ProcessCollision();

        int screenWidth;
        int screenHeight;

        int bgHandle;

        Input* input;
        Player* player;
        BulletManager* bulletManager;
        EnemyManager* enemyManager;
        EffectManager* effectManager;
    };
}
