#include "EffectManager.h"
#include "Effect.h"

namespace {
    // 取り合えず弾の最大数と同じ
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
            // アッパーキャストになるので注意
            auto effect = dynamic_cast<Effect*>(instance);

            return effect->Start(x, y, 2, 0);
        };

        return Spawn(MAX_NUM, generator, starter);
    }
}
