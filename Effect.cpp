#include "DxLib.h"
#include "Effect.h"

namespace shooting {

    Effect::Effect(int screenWidth, int screenHeight) : ObjectBase(screenWidth, screenHeight) {
        interval = 0;
        intervalCounter = 0;
        handleIndex = 0;
        loopNumber = 0;
        loopCounter = 0;
    }

    bool Effect::Load(const TCHAR* fileNameBase, const TCHAR* fileNameExtension, int fileNumber) {
        if (fileName.empty()) {
            fileName = std::string(fileNameBase);
            this->fileNameExtension = std::string(fileNameExtension);
        }

        if (handleCache.count(GetFileName(0)) == 0) {
            for (auto i = 0; i < fileNumber; ++i) {
                auto loadFileName = GetFileName(i);
                auto loadHandle = LoadGraph(loadFileName.c_str());

                if (loadHandle == -1) {
                    return false;
                }

                // 画像サイズは最初の画像のみ取得(全て同じ大きさ前提)
                if (sizeX == 0 && sizeY == 0) {
                    GetGraphSize(loadHandle, &sizeX, &sizeY);
                }

                handleList.push_back(loadHandle);
                handleCache[loadFileName] = std::make_tuple(loadHandle, sizeX, sizeY);
            }
        }
        else {
            for (auto i = 0; i < fileNumber; ++i) {
                auto loadFileName = GetFileName(i);
                auto cache = handleCache[loadFileName];

                handleList.push_back(std::get<0>(cache));

                if (sizeX == 0 && sizeY == 0) {
                    sizeX = std::get<1>(cache);
                    sizeY = std::get<2>(cache);
                }
            }
        }

        return true;
    }

    std::string Effect::GetFileName(int number) {
        // ちょっとやっつけ 2 桁までしか対応しない
        auto loadFileName = fileName;

        if (number < 10) {
            loadFileName += std::string(_T("0"));
        }

        loadFileName += std::to_string(number);
        loadFileName += fileNameExtension;

        return loadFileName;
    }

    bool Effect::Start(const int x, const int y, const int interval, const int loopNumber) {
        this->x = x;
        this->y = y;
        this->interval = interval;
        this->loopNumber = loopNumber;

        intervalCounter = 0;
        loopCounter = 0;
        handleIndex = 0;

        if (handleList.size() > 0) {
            handle = handleList[0];
        }

        valid = true;

        return true;
    }

    bool Effect::Initialize() {
        return Load(_T("res/bomb_a"), _T(".png"), 16);
    }

    void Effect::Process() {
        auto handleNum = handleList.size();

        if (handleNum == 0) {
            return;
        }

        intervalCounter++;

        if (intervalCounter > interval) {
            intervalCounter = 0;

            handleIndex++;

            if (handleIndex >= handleNum) {
                loopCounter++;

                if (loopCounter > loopNumber) {
                    valid = false;
                    return; // 終わり
                }

                handleIndex = 0;
            }

            handle = handleList[handleIndex];
        }
    }
}