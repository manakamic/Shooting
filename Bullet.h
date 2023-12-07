#pragma once
#include "ObjectBase.h"

namespace shooting {

    class Bullet : public ObjectBase {
    public:
        Bullet(const int screenWidth, const int screenHeight);

        bool Initialize() override;
        void Process() override;

        bool Start(const int x, const int y);
    };
}
