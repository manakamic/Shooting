#pragma once
#include "ObjectBase.h"

namespace shooting {

    class Enemy : public ObjectBase {
    public:
        Enemy(const int screenWidth, const int screenHeight);

        bool Initialize() override;
        void Process() override;

        bool Start();

    private:
        enum class Type {
            Straight = 0,
            Zigzag,
            CosineCurve
        };

        void SetType();
        void ProcessStraight();
        void ProcessZigzag();
        void ProcessSineCurve();

        Type type;

        int baseX;
        int baseY;
        bool zigzag;
    };
}
