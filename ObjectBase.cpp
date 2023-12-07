// DX ���C�u�����̋@�\(LoadGraph / DrawGraph)���g�p���Ă���̂ŃC���N���[�h
#include "DxLib.h"
#include "ObjectBase.h"

namespace shooting {
    // static �ȃ����o�ϐ��͕ʓr���[�J���ɐ錾����K�v������
    std::unordered_map<std::string, std::tuple<int, int, int>> ObjectBase::handleCache;

    ObjectBase::ObjectBase(const int screenWidth, const int screenHeight) {
        // �R���X�g���N�^�ł̓N���X�̃����o�ϐ��͕K�����������Ȃ���΂Ȃ�Ȃ�
        x = 0;
        y = 0;
        handle = -1;

        sizeX = 0;
        sizeY = 0;

        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;

        valid = false;
    }

    ObjectBase::~ObjectBase() {
    }

    bool ObjectBase::DeleteLoadType() {
        if (fileName.empty()) {
            return false;
        }

        auto cache = handleCache[fileName];
        auto handle = std::get<0>(cache);

        if (handle == -1) {
            return false;
        }

        // ���� LoadGraph �����摜�� DeleteGraph �Ŕj�����Ȃ��ƃr�f�I���������������Ă��܂�
        DeleteGraph(handle);

        handleCache[this->fileName] = std::make_tuple(-1, 0, 0);
        fileName.clear();

        return true;
    }

    // ���@���G���摜�̓ǂݍ��݂͂���͂��Ȃ̂ŋ��ʂ̏����Ƃ��Ď���
    // ���@���G�̃N���X��h���N���X�ɂ��Ă��A���� Load �����ʂŎg���Ηǂ��݌v
    int ObjectBase::Load(const TCHAR* fileName) {
        if (this->fileName.empty()) {
            this->fileName = std::string(fileName);
        }

        if (handleCache.count(this->fileName) == 0) {
            handle = LoadGraph(fileName);

            if (handle != -1) {
                GetGraphSize(handle, &sizeX, &sizeY);

                handleCache[this->fileName] = std::make_tuple(handle, sizeX, sizeY);
            }
        }
        else {
            auto cache = handleCache[this->fileName];

            handle = std::get<0>(cache);
            sizeX = std::get<1>(cache);
            sizeY = std::get<2>(cache);
        }

        return handle;
    }

    bool ObjectBase::Initialize() {
        return true;
    }

    // ���z�֐��͂��̂܂܂ł͒ʏ�̊֐��ƕς�炸�g����
    // (override ������A������̊֐��ɏ����ς��)
    void ObjectBase::Process() {
        // ObjectBase �ł͓��ɉ����������Ȃ�
    }

    // ���z�֐��͂��̂܂܂ł͒ʏ�̊֐��ƕς�炸�g����
    // // (override ������A������̊֐��ɏ����ς��)
    // ���ʂ̕`��֐��Ƃ��čŒ���̕`��Ƃ��Ď���
    void ObjectBase::Render() {
        if (handle == -1) {
            return;
        }

        DrawGraph(x, y, handle, TRUE);
    }
}
