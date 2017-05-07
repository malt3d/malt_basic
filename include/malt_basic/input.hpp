//
// Created by Mehmet Fatih BAKIR on 30/04/2017.
//

#pragma once

#include <malt/engine_impl.hpp>

namespace malt
{
    namespace input
    {
        bool get_key_up(int key_code) MALT_WEAK_SYMBOL;
        bool get_key(int key_code) MALT_WEAK_SYMBOL;
        bool get_key_down(int key_code) MALT_WEAK_SYMBOL;

        glm::vec2 get_cursor() MALT_WEAK_SYMBOL;
    }
}
