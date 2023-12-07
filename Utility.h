#pragma once

namespace shooting {

    class Utility final {
    public:
        Utility() = delete;
        ~Utility() = delete;

        static int Range(const int min, const int max);

        struct Rect {
            int x;
            int y;
            int w;
            int h;
        };

        static bool Collision(Rect src, Rect dst);
    };
}
