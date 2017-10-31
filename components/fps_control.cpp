//
// Created by Mehmet Fatih BAKIR on 01/05/2017.
//

#include <malt_basic/components/fps_control.hpp>
#include <malt_basic/components/transform.hpp>
#include <malt/detail/component_mgr_impl.hpp>
#include <malt/engine.hpp>
#include <malt_basic/input.hpp>

MALT_IMPLEMENT_COMP(fps_control)

void fps_control::Handle(malt::update)
{
    auto trans = get_component<malt::transform>();
    glm::vec3 displacement {0, 0, 0};
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

    malt::entity small_tp = malt::find_entity("small teapot");

    auto tp_trans = small_tp.get_component<malt::transform>();
    auto tp_pos = glm::vec3(tp_trans->get_world_mat4() * glm::vec4{0, 0, 0, 1});
    if (malt::time::get_current_frame() == 0)
    {
        return;
    }

    if (malt::input::get_key_down(malt::input::key_code::L))
        trans->look_at(tp_pos);
}

void fps_control::Handle(malt::start)
{
    prev = malt::input::get_cursor();
}

void fps_control::set_speed(float s)
{
    speed = s;
}
