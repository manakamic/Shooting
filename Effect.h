#pragma once
#include <vector>
#include "ObjectBase.h"

namespace shooting {

    class Effect : public ObjectBase {
    public:
        Effect(const int screenWidth, const int screenHeight);

        bool Load(const TCHAR* fileNameBase, const TCHAR* fileNameExtension, int fileNumber);
        bool Start(const int x, const int y, const int interval, const int loopNumber);

        bool Initialize() override;
        void Process() override;

    private:
        std::string GetFileName(int number);

        int interval;
        int intervalCounter;
        int handleIndex;
        int loopNumber;
        int loopCounter;

        std::vector<int> handleList;
        std::string fileNameExtension;
    };
}
