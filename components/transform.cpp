//
// Created by fatih on 4/28/17.
//

#include "transform.hpp"
#include <malt/component_mgr.cpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace malt {
    void malt::transform::translate(const glm::vec3& dis, malt::space s)
    {
        switch (s) {
        case space::self:
            pos += rot * dis;
            break;
        case space::world:
            pos += dis;
            break;
        }
    }

    void transform::rotate(const glm::quat& q)
    {
        rot = q * rot;
        rot = glm::normalize(rot);
    }

    void transform::rotate(const glm::vec3& euler)
    {
        auto around_x = glm::angleAxis(glm::radians(euler.x), glm::vec3(1, 0, 0));
        auto around_y = glm::angleAxis(glm::radians(euler.y), glm::vec3(0, 1, 0));
        auto around_z = glm::angleAxis(glm::radians(euler.z), glm::vec3(0, 0, 1));
        rotate(around_x * around_y * around_z);
    }

    glm::mat4 transform::get_mat4() const
    {
        auto s = glm::scale(scale);
        auto r = glm::toMat4(rot);
        auto t = glm::translate(pos);
        return t * r * s;
    }

    void transform::set_scale(const glm::vec3& s)
    {
        scale = s;
    }
}

MALT_IMPLEMENT_COMP(malt::transform)


