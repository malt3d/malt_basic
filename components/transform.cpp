//
// Created by fatih on 4/28/17.
//

#include <malt_basic/components/transform.hpp>
#include <malt/component_mgr_impl.hpp>
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
        set_local_dirty();
    }

    void transform::rotate(const glm::quat& q, space s)
    {
        if (s == space::world)
        {
            rot = q * rot;
        }
        else
        {
            rot *= q;
        }

        rot = glm::normalize(rot);
        set_local_dirty();
    }

    void transform::rotate(const glm::vec3& euler, space s)
    {
        auto around_x = glm::angleAxis(glm::radians(euler.x), glm::vec3(1, 0, 0));
        auto around_y = glm::angleAxis(glm::radians(euler.y), glm::vec3(0, 1, 0));
        auto around_z = glm::angleAxis(glm::radians(euler.z), glm::vec3(0, 0, 1));
        rotate(around_x * around_y * around_z, s);
    }

    glm::mat4 transform::get_local_mat4() const
    {
        if (m_local_mat_dirty)
        {
            auto s = glm::scale(scale);
            auto r = glm::toMat4(rot);
            auto t = glm::translate(pos);
            m_local_mat = t * r * s;
            m_local_mat_dirty = false;
        }
        return m_local_mat;
    }

    glm::mat4 transform::get_world_mat4() const
    {
        if (m_parent == nullptr)
        {
            return get_local_mat4();
        }

        if (m_world_mat_dirty)
        {
            m_world_mat = get_local_mat4() * m_parent->get_world_mat4();
            m_world_mat_dirty = false;
        }

        return m_world_mat;
    }

    void transform::set_parent(transform* t)
    {
        m_parent = t;
        set_world_dirty();
    }

    void transform::set_world_dirty()
    {
        m_world_mat_dirty = true;
    }

    void transform::set_scale(const glm::vec3& s)
    {
        scale = s;
        set_local_dirty();
    }

    glm::vec3 transform::get_up() const
    {
        return rot * glm::vec3(0, 1, 0);
    }

    glm::vec3 transform::get_forward() const
    {
        return rot * glm::vec3(0, 0, 1);
    }

    glm::vec3 transform::get_right() const
    {
        return rot * glm::vec3(1, 0, 0);
    }
}

MALT_IMPLEMENT_COMP(malt::transform)


