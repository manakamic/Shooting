// DX ライブラリの機能(LoadGraph / DrawGraph)を使用しているのでインクルード
#include "DxLib.h"
#include "ObjectBase.h"

namespace shooting {
    // static なメンバ変数は別途ローカルに宣言する必要がある
    std::unordered_map<std::string, std::tuple<int, int, int>> ObjectBase::handleCache;

    ObjectBase::ObjectBase(const int screenWidth, const int screenHeight) {
        // コンストラクタではクラスのメンバ変数は必ず初期化しなければならない
        x = 0;
        y = 0;
        handle = -1;

        sizeX = 0;
        sizeY = 0;

        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;

        valid = false;
    }

    ObjectBase::~ObjectBase() {
    }

    bool ObjectBase::DeleteLoadType() {
        if (fileName.empty()) {
            return false;
        }

        auto cache = handleCache[fileName];
        auto handle = std::get<0>(cache);

        if (handle == -1) {
            return false;
        }

        // 実は LoadGraph した画像は DeleteGraph で破棄しないとビデオメモリを圧迫してしまう
        DeleteGraph(handle);

        handleCache[this->fileName] = std::make_tuple(-1, 0, 0);
        fileName.clear();

        return true;
    }

    // 自機も敵も画像の読み込みはあるはずなので共通の処理として実装
    // 自機も敵のクラスを派生クラスにしても、この Load を共通で使えば良い設計
    int ObjectBase::Load(const TCHAR* fileName) {
        if (this->fileName.empty()) {
            this->fileName = std::string(fileName);
        }

        if (handleCache.count(this->fileName) == 0) {
            handle = LoadGraph(fileName);

            if (handle != -1) {
                GetGraphSize(handle, &sizeX, &sizeY);

                handleCache[this->fileName] = std::make_tuple(handle, sizeX, sizeY);
            }
        }
        else {
            auto cache = handleCache[this->fileName];

            handle = std::get<0>(cache);
            sizeX = std::get<1>(cache);
            sizeY = std::get<2>(cache);
        }

        return handle;
    }

    bool ObjectBase::Initialize() {
        return true;
    }

    // 仮想関数はそのままでは通常の関数と変わらず使える
    // (override したら、そちらの関数に書き変わる)
    void ObjectBase::Process() {
        // ObjectBase では特に何も処理しない
    }

    // 仮想関数はそのままでは通常の関数と変わらず使える
    // // (override したら、そちらの関数に書き変わる)
    // 共通の描画関数として最低限の描画として実装
    void ObjectBase::Render() {
        if (handle == -1) {
            return;
        }

        DrawGraph(x, y, handle, TRUE);
    }
}
