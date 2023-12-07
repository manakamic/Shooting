// visual studio が自動で挿入してくる
// ヘッダーには必ず記述する
#pragma once
#include "Input.h"
#include "Player.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "EffectManager.h"

// 基本的に namespace はあった方が良い
// (無くとも問題無ければ無理に使用しなくとも良い)
namespace shooting {

    // クラスの基本はコンストラクタとデストラクタ
    class Game {
    public: // アクセス修飾子
        // クラス名と同名の戻り値なしの関数がコンストラクタとなる
        // 引数有りで複数のコンストラクタを用意しても良い
        Game(const int screenWidth, const int screenHeight);
        // クラス名と同名の戻り値なしの関数で先頭に ~ が付いているのがデストラクタ
        // 継承をする場合様に virtual を付ける
        // (まずはデストラクタは virtual ~XXXX() と言う形にしまって良い)
        virtual ~Game();

        // Game クラスの初期化関数として設計
        // 名前は Init() でも何でも良いが導入している他のクラスなどの名称と揃えると良い
        bool Initialize();

        // メインループで描画以外の処理(の全て)を呼ぶ関数として設計
        // 名前は Update() でも何でも良いが導入している他のクラスなどの名称と揃えると良い
        bool Process();

        // メインループで描画の処理(の全て)を呼ぶ関数として設計
        // 名前は Draw() でも何でも良いが導入している他のクラスなどの名称と揃えると良い
        bool Render() const;

    private:
        bool InitializePlayer();
        bool CheckInitialize() const;

        void ProcessCollision();

        int screenWidth;
        int screenHeight;

        int bgHandle;

        Input* input;
        Player* player;
        BulletManager* bulletManager;
        EnemyManager* enemyManager;
        EffectManager* effectManager;
    };
}
