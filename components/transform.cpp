//
// Created by fatih on 4/28/17.
//

#include "transform.hpp"
#include <malt/component_mgr.cpp>

void transform::translate(float dx, float dy, float dz)
{
    x+=dx;
    y+=dy;
    z+=dz;
}

MALT_IMPLEMENT_COMP(transform)