#include "ManagerBase.h"

namespace shooting {

    ManagerBase::ManagerBase(const int screenWidth, const int screenHeight) {
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;
    }

    ManagerBase::~ManagerBase() {
        // �͈� for
        for (auto& target : managedList) {
            if (target != nullptr) {
                target->DeleteLoadType();
                delete target;
            }
        }

        managedList.clear();
    }

    ObjectBase* ManagerBase::GetInvalid() const {
        for (auto& target : managedList) {
            if (target == nullptr || target->IsValid()) {
                continue;
            }

            return target;
        }

        return nullptr;
    }

    bool ManagerBase::Spawn(int maxNumber,
                            std::function<ObjectBase* (int, int)> generator,
                            std::function<bool(ObjectBase*)> starter) {
        auto poolObect = GetInvalid();

        if (poolObect == nullptr) {
            auto size = managedList.size();

            if (size >= maxNumber) {
                return false;
            }

            // �|�����[�t�B�Y��
            // �^�� ObjectBase ���� generator �ł͔h���N���X��Ԃ��l�ɂ���
            auto spawn = generator(screenWidth, screenHeight);

            // �|�����[�t�B�Y��
            // Initialize �͔h���N���X�� override �������̂��Ă΂��
            if (spawn != nullptr && spawn->Initialize()) {
                managedList.push_back(spawn);
            }

            poolObect = spawn;
        }

        return starter(poolObect);
    }

    void ManagerBase::Process() {
        for (auto& target : managedList) {
            if (target == nullptr || !target->IsValid()) {
                continue;
            }

            target->Process();
        }
    }

    void ManagerBase::Render() {
        for (auto& target : managedList) {
            if (target == nullptr || !target->IsValid()) {
                continue;
            }

            target->Render();
        }
    }
}
