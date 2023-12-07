// Visual Studio �̒ǉ��̃C���N���[�h�p�X�Őݒ肵�� dxlib �f�B���N�g������ DX ���C�u�����̃w�b�_�[
#include "DxLib.h"
// Game class ���g�������̂ŃC���N���[�h����
#include "Game.h"

// ������ namespace �̓��[�J���ł� static �I�Ȏg�����Ɠ��`
// ����� static int(auto) ��� ��������g�p����
namespace {
    // constexpr ��t����ƒ萔�ɂȂ�
    // ����� const ��� ��������g�p����
    // auto �͌^���_
    // (�R���p�C�����g�p���Ă���l����^�������Ŋ��蓖�ĂĂ����)
    constexpr auto SCREEN_WIDTH = 1280;
    constexpr auto SCREEN_HEIGHT = 720;
    constexpr auto SCREEN_DEPTH = 32;
}

// �v���O�����̃G���g���[�|�C���g
// ����� Windows OS �̃v���P�[�V�����p
// (�ËL / �R�s�[���y�[�X�g�ŗǂ�)
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    auto window_mode = FALSE;

    // _DEBUG �萔�� Visual Studio �� Debug �ɂ��Ă���Ǝ����Őݒ肳���
#ifdef _DEBUG
    window_mode = TRUE;
#endif

    // DxLib_Init ����ɌĂԊ֐��Q
    // window ���[�h���t���X�N���[������ݒ�
    ChangeWindowMode(window_mode);
    // ��ʂ̉𑜓x��ݒ�
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH);

    // DX ���C�u�����̏�����
    if (DxLib_Init() == -1) {
        return -1;
    }

    // Game �N���X���S�Ă̏������s���݌v
    // ��{�I�ɃN���X���g�p����ꍇ�́A�|�C���^�^�ɑ΂��� new �����ăC���X�^���X�𐶐�����
    // ���� new ���������Ɏ����ł��̃N���X�̃R���X�g���N�^���Ă΂��
    // �݌v�Ƃ��Ă� ���� Game �N���X���S�Ă����l�ɂ���\��Ȃ̂ŁA�ȍ~ WinMain.cpp �ɂ͉����ǉ��Ȃǂ��Ȃ��z��
    shooting::Game* pGame = new shooting::Game(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Game �N���X�ɕK�v�ȏ����������C�����[�v�O�ɍs��
    // (���C�����[�v�͖� Frame ��������Ă��܂����������͈��ŗǂ��͂��Ȃ̂�)
    // �e�����ɂ� DX ���C�u�����̋@�\���g�p�������̂�����͂��Ȃ̂� DxLib_Init ����̕����ǂ��ꍇ������
    if (!pGame->Initialize()) {
        DxLib_End(); // �ꉞ DxLib_Init �̌�Ȃ̂ŏI�������Ă���
        return -1;
    }

    //
    // ���� while �����C�����[�v
    // ProcessMessage ���ĂԎ��ɂ�� 1/60 FPS �� Frame ���[�g�ɂȂ�
    //
    while (ProcessMessage() != -1) {
        // ESC �L�[�������ꂽ�烋�[�v���I��������
        // (�v���O�������I���Ȃ��󋵂��������)
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
            break;
        }

        // �����ŕ`��p�₻�̑��̏������Ăԗl�ɂ���
        // ���� Game �N���X�� Process ���ŃQ�[���ɕK�v�ȏ������s���݌v
        pGame->Process();

        // ���� ClearDrawScreen �� ScreenFlip �̊Ԃ� DrawXXXXX ���Ă�
        // �`��̏����ł͕`��̏����������ĂԂ̂��Z�I���[
        ClearDrawScreen();
        // ���� Game �N���X�� Render ���ŃQ�[���ɕK�v�ȕ`����s���݌v
        pGame->Render();
        ScreenFlip();
    }

    // new �������͕̂K�� delete ����
    // ���� delete ���������Ɏ����ł��̃N���X�̃f�X�g���N�^���Ă΂��
    delete pGame;
    pGame = nullptr; // delete ��͔O�̂��� nullptr �ɂ��Ă����Ɨǂ�

    // DX ���C�u�����̏I��
    DxLib_End();

    return 0;
}
