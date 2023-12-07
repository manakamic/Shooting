#include "DxLib.h"
#include "Input.h"

namespace shooting {

    Input::Input() {
        onKey = 0;
        triggerKey = 0;
        releaseKey = 0;
    }

    Input::~Input() {
    }

    void Input::Process() {
        // 前のフレームのキー情報を保存
        int oldOnKey = onKey;

        // 今のフレームのキー情報
        onKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);

        // ^ : 排他的論理和
        // メモリの bit 単位で比較して、値が異なる時に 1、値が同じ時に 0 になる処理
        int xOR = onKey ^ oldOnKey;

        triggerKey = xOR & onKey;  // キー入力と & : AND 演算を行うと押された瞬間のフレームが分かる
        releaseKey = xOR & ~onKey; // ~ : bit 反転をしたキー入力 == 押されていないと & : AND 演算を行うと離された瞬間のフレームが分かる
    }
}