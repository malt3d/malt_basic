//
// Created by fatih on 5/20/17.
//

#include <malt_basic/components/rotate_comp.hpp>
#include <malt/detail/component_mgr_impl.hpp>
#include <malt_basic/components/transform.hpp>

void rotate_comp::Handle(malt::update)
{
    auto t = get_component<malt::transform>();
    t->rotate(glm::vec3{0, 30, 0} * malt::time::get_delta_time(), malt::space::world);
}

void rotate_comp::Handle(malt::start)
{
    auto t = get_component<malt::transform>();
    t->rotate(glm::vec3{0, 0, 45}, malt::space::self);
    t->translate({0, -2.5f, 5});
}

MALT_IMPLEMENT_COMP(rotate_comp)