#include <random>
#include "Utility.h"

namespace {
    std::random_device seed_gen;
    std::mt19937_64 random(seed_gen());
}

namespace shooting {

    // min ~ max ‚Ì”ÍˆÍ
    int Utility::Range(const int min, const int max) {
        std::uniform_int_distribution<int>  distr(min, max);

        return distr(random);
    }

    bool Utility::Collision(Rect src, Rect dst) {
        if (src.x > dst.x + dst.w) {
            return false;
        }

        if (src.x + src.w < dst.x) {
            return false;
        }

        if (src.y > dst.y + dst.h) {
            return false;
        }

        if (src.y + src.h < dst.y) {
            return false;
        }

        return true;
    }
}
