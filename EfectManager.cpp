#include "EffectManager.h"
#include "Effect.h"

namespace {
    // ��荇�����e�̍ő吔�Ɠ���
    constexpr auto MAX_NUM = 8;
}

namespace shooting {

    EffectManager::EffectManager(const int screenWidth, const int screenHeight) : ManagerBase(screenWidth, screenHeight) {
    }

    bool EffectManager::SpawnEffect(const int x, const int y) {
        auto generator = [](int w, int h) -> Effect* {
            return new Effect(w, h);
        };

        auto starter = [x, y](ObjectBase* instance)-> bool {
            // �A�b�p�[�L���X�g�ɂȂ�̂Œ���
            auto effect = dynamic_cast<Effect*>(instance);

            return effect->Start(x, y, 2, 0);
        };

        return Spawn(MAX_NUM, generator, starter);
    }
}
