//
// Created by fatih on 4/28/17.
//

#pragma once

#include <malt/component.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace malt
{
    enum class space
    {
        self,
        world
    };

    class transform : public malt::component
    {
        std::vector<track_ptr<transform>> m_children;
        track_ptr<transform> m_parent;

        glm::vec3 pos;
        glm::vec3 scale = {1, 1, 1};
        glm::quat rot;

        mutable bool m_local_mat_dirty;
        mutable glm::mat4 m_local_mat;

        mutable bool m_world_mat_dirty;
        mutable glm::mat4 m_world_mat;

        void set_local_dirty()
        {
            m_local_mat_dirty = true;
            set_world_dirty();
        }
    public:

        void translate(const glm::vec3& dis, space s = space::self);

        void rotate(const glm::quat& q, space s = space::self);
        void rotate(const glm::vec3& euler, space s = space::self);

        void set_scale(const glm::vec3& s);

        glm::mat4 get_world_mat4() const;
        glm::mat4 get_local_mat4() const;

        glm::vec3 get_up() const;
        glm::vec3 get_forward() const;
        glm::vec3 get_right() const;

        const glm::vec3& get_pos() const { return pos; }

        void set_parent(transform* t);
        void set_world_dirty();

        REFLECT(malt::transform,
                MEM(pos),
                MEM(rot),
                MEM(scale));
    };
}


