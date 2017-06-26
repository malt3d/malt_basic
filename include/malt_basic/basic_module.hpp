//
// Created by fatih on 4/28/17.
//

#ifndef MALT_BASIC_MODULE_HPP
#define MALT_BASIC_MODULE_HPP

#include <malt/module.hpp>
#include <malt/meta.hpp>

namespace malt
{
    class transform;
}

struct basic_module_def
{
    using components = malt::meta::list<class malt::transform, class rotate_comp, class fps_control>;
};

#endif //MALT_BASIC_MODULE_HPP
