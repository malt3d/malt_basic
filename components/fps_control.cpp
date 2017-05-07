//
// Created by Mehmet Fatih BAKIR on 01/05/2017.
//

#include <malt_basic/components/fps_control.hpp>
#include <malt_basic/components/transform.hpp>
#include <malt/component_mgr_impl.hpp>
#include <malt/engine.hpp>
#include <malt_basic/input.hpp>

MALT_IMPLEMENT_COMP(fps_control)

void fps_control::Handle(malt::update)
{
    auto trans = get_component<malt::transform>();
    glm::vec3 displacement;
    if (malt::input::get_key_down(malt::input::key_code::S))
    {
        displacement += glm::vec3{0, 0, -1};
    }
    if (malt::input::get_key_down(malt::input::key_code::W))
    {
        displacement += glm::vec3{0, 0, 1};
    }
    if (malt::input::get_key_down(malt::input::key_code::A))
    {
        displacement += glm::vec3{1, 0, 0};
    }
    if (malt::input::get_key_down(malt::input::key_code::D))
    {
        displacement += glm::vec3{-1, 0, 0};
    }

    if (glm::length(displacement))
    {
        trans->translate(glm::normalize(displacement) * speed * malt::time::get_delta_time());
    }

    auto diff = (malt::input::get_cursor() - prev) / 20.f;
    prev = malt::input::get_cursor();

    trans->rotate(glm::vec3(diff.y, 0, 0));
    trans->rotate(glm::vec3(0, -diff.x, 0), malt::space::world);
}

void fps_control::Handle(malt::start)
{
    prev = malt::input::get_cursor();
}

void fps_control::set_speed(float s)
{
    speed = s;
}
