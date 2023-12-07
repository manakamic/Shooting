// Visual Studio の追加のインクルードパスで設定した dxlib ディレクトリ内の DX ライブラリのヘッダー
#include "DxLib.h"
// Game class を使いたいのでインクルードする
#include "Game.h"

// 無名の namespace はローカルでの static 的な使い方と同義
// 今後は static int(auto) より こちらを使用する
namespace {
    // constexpr を付けると定数になる
    // 今後は const より こちらを使用する
    // auto は型推論
    // (コンパイラが使用している値から型を自動で割り当ててくれる)
    constexpr auto SCREEN_WIDTH = 1280;
    constexpr auto SCREEN_HEIGHT = 720;
    constexpr auto SCREEN_DEPTH = 32;
}

// プログラムのエントリーポイント
// これは Windows OS のプリケーション用
// (暗記 / コピー＆ペーストで良い)
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    auto window_mode = FALSE;

    // _DEBUG 定数は Visual Studio を Debug にしていると自動で設定される
#ifdef _DEBUG
    window_mode = TRUE;
#endif

    // DxLib_Init より先に呼ぶ関数群
    // window モードかフルスクリーンかを設定
    ChangeWindowMode(window_mode);
    // 画面の解像度を設定
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH);

    // DX ライブラリの初期化
    if (DxLib_Init() == -1) {
        return -1;
    }

    // Game クラスが全ての処理を行う設計
    // 基本的にクラスを使用する場合は、ポインタ型に対して new をしてインスタンスを生成する
    // この new をした時に自動でそのクラスのコンストラクタが呼ばれる
    // 設計としては この Game クラスが全てを持つ様にする予定なので、以降 WinMain.cpp には何も追加などしない想定
    shooting::Game* pGame = new shooting::Game(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Game クラスに必要な初期化をメインループ前に行う
    // (メインループは毎 Frame 処理されてしまうが初期化は一回で良いはずなので)
    // 各処理には DX ライブラリの機能を使用したものもあるはずなので DxLib_Init より後の方が良い場合が多い
    if (!pGame->Initialize()) {
        DxLib_End(); // 一応 DxLib_Init の後なので終了させておく
        return -1;
    }

    //
    // この while がメインループ
    // ProcessMessage を呼ぶ事により 1/60 FPS の Frame レートになる
    //
    while (ProcessMessage() != -1) {
        // ESC キーが押されたらループを終了させる
        // (プログラムが終わらない状況を回避する)
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
            break;
        }

        // ここで描画用やその他の処理を呼ぶ様にする
        // この Game クラスの Process 内でゲームに必要な処理を行う設計
        pGame->Process();

        // この ClearDrawScreen と ScreenFlip の間で DrawXXXXX を呼ぶ
        // 描画の処理では描画の処理だけを呼ぶのがセオリー
        ClearDrawScreen();
        // この Game クラスの Render 内でゲームに必要な描画を行う設計
        pGame->Render();
        ScreenFlip();
    }

    // new したものは必ず delete する
    // この delete をした時に自動でそのクラスのデストラクタが呼ばれる
    delete pGame;
    pGame = nullptr; // delete 後は念のため nullptr にしておくと良い

    // DX ライブラリの終了
    DxLib_End();

    return 0;
}
