#pragma once
#include "ObjectBase.h"
#include "Input.h"

namespace shooting {
    class BulletManager;

    class Player : public ObjectBase {
    public:
        Player(Input* input, const int screenWidth, const int screenHeight);
        virtual ~Player();

        bool Initialize();
        void SetBulletManager(BulletManager* bulletManager) {
            this->bulletManager = bulletManager;
        }

        void Process() override;

    private:
        void ProcessInput();
        void CheckPosition();

        Input* input;
        BulletManager* bulletManager;
    };
}
