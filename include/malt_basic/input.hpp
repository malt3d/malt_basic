//
// Created by Mehmet Fatih BAKIR on 30/04/2017.
//

#pragma once

#include <malt/engine_impl.hpp>

namespace malt
{
    namespace input
    {
        enum class key_code : uint16_t
        {
            Num0 = 48, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
            A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            LeftBracket = 91, Backslash, RightBracket,
            GraveAccent = 96
        };


        bool get_key_up(key_code) MALT_WEAK_SYMBOL;
        bool get_key_down(key_code) MALT_WEAK_SYMBOL;

        glm::vec2 get_cursor() MALT_WEAK_SYMBOL;
    }
}
