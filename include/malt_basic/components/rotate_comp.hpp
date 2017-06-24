//
// Created by fatih on 5/20/17.
//

#pragma once

#include <malt/component.hpp>

class rotate_comp : public malt::component
{
public:
    void Handle(malt::start);
    void Handle(malt::update);
    REFLECT(rotate_comp, NOMEM);
};


