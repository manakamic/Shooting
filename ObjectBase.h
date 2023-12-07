#pragma once
// ObjectBase クラスの定義(Load 関数)で TCHAR 型を宣言(使用)しているのでインクルード
#include <tchar.h>
#include <unordered_map>
#include <tuple>
#include <string>
#include "Utility.h"

// Game クラスと合わせる
// つまりこのゲーム(アプリケーション)の処理は shooting と言うネームスーペースに属すると言う考え
namespace shooting {

    // シューティングゲームにおける、自機と敵のクラスを定義＆実装するにあたり
    // ・画面に描画される
    // ・画面内を動く
    // ・当たり判定がある
    // 等々の共通の処理が多そうなのでオブジェクト指向で定義＆実装していく
    class ObjectBase {
    public:
        ObjectBase(const int screenWidth, const int screenHeight);
        virtual ~ObjectBase();

        // キャッシュしているハンドルを解放する
        virtual bool DeleteLoadType();

        // 自機も敵も画像の読み込みはあるはずなので共通の処理として実装
        int Load(const TCHAR* fileName);

        // virtual を付けると仮想関数となる
        // これを自機と敵のクラス側で override して、それぞれクラス専用の関数書き換えたりする
        virtual bool Initialize();
        virtual void Process();
        virtual void Render();

        virtual void End() { valid = false; }

        // ゲッター
        int GetX() const { return x; }
        int GetY() const { return y; }
        int GetSizeX() const { return sizeX; }
        int GetSizeY() const { return sizeY; }
        bool IsValid() const { return valid; }
        Utility::Rect GetRect() const { return { x, y, sizeX, sizeY }; }

    protected:
        // 取り合えず描画に必要な最低限の変数
        // (DrawGraph が必要としている)
        int x;
        int y;
        int handle;

        // オブジェクトがゲームで共通に必要な情報を追加していく
        int sizeX;
        int sizeY;

        int screenWidth;
        int screenHeight;

        bool valid;

        std::string fileName;

        static std::unordered_map<std::string, std::tuple<int, int, int>> handleCache;
    };
}
