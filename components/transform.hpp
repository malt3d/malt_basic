//
// Created by fatih on 4/28/17.
//

#pragma once

#include <malt/component.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace malt
{
    class transform : public malt::component
    {
        glm::vec3 pos;
        glm::vec3 scale;
        glm::quat rot;
    public:

        void translate(const glm::vec3& dis);
        void translate(float dx, float dy, float dz);
    };
}


