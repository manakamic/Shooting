#include "ManagerBase.h"

namespace shooting {

    ManagerBase::ManagerBase(const int screenWidth, const int screenHeight) {
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;
    }

    ManagerBase::~ManagerBase() {
        // 範囲 for
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

            // ポリモーフィズム
            // 型は ObjectBase だが generator では派生クラスを返す様にする
            auto spawn = generator(screenWidth, screenHeight);

            // ポリモーフィズム
            // Initialize は派生クラスの override したものが呼ばれる
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
