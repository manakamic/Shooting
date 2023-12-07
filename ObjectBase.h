#pragma once
// ObjectBase �N���X�̒�`(Load �֐�)�� TCHAR �^��錾(�g�p)���Ă���̂ŃC���N���[�h
#include <tchar.h>
#include <unordered_map>
#include <tuple>
#include <string>
#include "Utility.h"

// Game �N���X�ƍ��킹��
// �܂肱�̃Q�[��(�A�v���P�[�V����)�̏����� shooting �ƌ����l�[���X�[�y�[�X�ɑ�����ƌ����l��
namespace shooting {

    // �V���[�e�B���O�Q�[���ɂ�����A���@�ƓG�̃N���X���`����������ɂ�����
    // �E��ʂɕ`�悳���
    // �E��ʓ��𓮂�
    // �E�����蔻�肪����
    // ���X�̋��ʂ̏������������Ȃ̂ŃI�u�W�F�N�g�w���Œ�`���������Ă���
    class ObjectBase {
    public:
        ObjectBase(const int screenWidth, const int screenHeight);
        virtual ~ObjectBase();

        // �L���b�V�����Ă���n���h�����������
        virtual bool DeleteLoadType();

        // ���@���G���摜�̓ǂݍ��݂͂���͂��Ȃ̂ŋ��ʂ̏����Ƃ��Ď���
        int Load(const TCHAR* fileName);

        // virtual ��t����Ɖ��z�֐��ƂȂ�
        // ��������@�ƓG�̃N���X���� override ���āA���ꂼ��N���X��p�̊֐������������肷��
        virtual bool Initialize();
        virtual void Process();
        virtual void Render();

        virtual void End() { valid = false; }

        // �Q�b�^�[
        int GetX() const { return x; }
        int GetY() const { return y; }
        int GetSizeX() const { return sizeX; }
        int GetSizeY() const { return sizeY; }
        bool IsValid() const { return valid; }
        Utility::Rect GetRect() const { return { x, y, sizeX, sizeY }; }

    protected:
        // ��荇�����`��ɕK�v�ȍŒ���̕ϐ�
        // (DrawGraph ���K�v�Ƃ��Ă���)
        int x;
        int y;
        int handle;

        // �I�u�W�F�N�g���Q�[���ŋ��ʂɕK�v�ȏ���ǉ����Ă���
        int sizeX;
        int sizeY;

        int screenWidth;
        int screenHeight;

        bool valid;

        std::string fileName;

        static std::unordered_map<std::string, std::tuple<int, int, int>> handleCache;
    };
}
