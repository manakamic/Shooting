#pragma once

namespace shooting {

    class Input {
    public:
        Input();
        virtual ~Input();

        void Process();

        bool OnKey(unsigned int key) const {
            return onKey & key;
        }

        bool TriggerKey(unsigned int key) const {
            return triggerKey & key;
        }

        bool ReleaseKey(unsigned int key) const {
            return releaseKey & key;
        }

    private:
        int onKey;      // キーが押されているか
        int triggerKey; // キーが押されたフレーム
        int releaseKey; // キーが離されたフレーム
    };
}
