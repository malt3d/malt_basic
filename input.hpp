//
// Created by Mehmet Fatih BAKIR on 30/04/2017.
//

#ifndef MALT_INPUT_HPP
#define MALT_INPUT_HPP

namespace malt
{
    namespace input
    {
        bool get_key_up(int key_code);
        bool get_key(int key_code);
        bool get_key_down(int key_code);

        glm::vec2 get_cursor();
    }
}

#endif //MALT_INPUT_HPP
