#include "DxLib.h"
#include "Input.h"

namespace shooting {

    Input::Input() {
        onKey = 0;
        triggerKey = 0;
        releaseKey = 0;
    }

    Input::~Input() {
    }

    void Input::Process() {
        // �O�̃t���[���̃L�[����ۑ�
        int oldOnKey = onKey;

        // ���̃t���[���̃L�[���
        onKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);

        // ^ : �r���I�_���a
        // �������� bit �P�ʂŔ�r���āA�l���قȂ鎞�� 1�A�l���������� 0 �ɂȂ鏈��
        int xOR = onKey ^ oldOnKey;

        triggerKey = xOR & onKey;  // �L�[���͂� & : AND ���Z���s���Ɖ����ꂽ�u�Ԃ̃t���[����������
        releaseKey = xOR & ~onKey; // ~ : bit ���]�������L�[���� == ������Ă��Ȃ��� & : AND ���Z���s���Ɨ����ꂽ�u�Ԃ̃t���[����������
    }
}