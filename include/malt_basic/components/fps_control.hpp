//
// Created by Mehmet Fatih BAKIR on 01/05/2017.
//

#ifndef MALT_FPS_CONTROL_HPP
#define MALT_FPS_CONTROL_HPP

#include <glm/glm.hpp>
#include <malt/component.hpp>

class fps_control : public malt::component
{
    glm::vec2 prev;
    float speed = 2;
public:

    void set_speed(float s);
    void Handle(malt::start);
    void Handle(malt::update);
};

#endif //MALT_FPS_CONTROL_HPP
