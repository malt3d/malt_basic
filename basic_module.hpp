//
// Created by fatih on 4/28/17.
//

#ifndef MALT_BASIC_MODULE_HPP
#define MALT_BASIC_MODULE_HPP

#include <malt/module.hpp>
#include <malt/list.hpp>

struct basic_module_def
{
    using components = malt::mp::list<class transform>;
};

#endif //MALT_BASIC_MODULE_HPP
