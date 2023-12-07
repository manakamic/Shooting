#pragma once
#include "ManagerBase.h"

namespace shooting {
    class EffectManager : public ManagerBase {
    public:
        EffectManager(const int screenWidth, const int screenHeight);

        bool SpawnEffect(const int x, const int y);
    };
}
