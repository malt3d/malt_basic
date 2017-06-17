//
// Created by Mehmet Fatih BAKIR on 30/04/2017.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <malt_basic/components/transform.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/epsilon.hpp>

bool equal(const glm::vec3& a, const glm::vec3& b)
{
    auto r = glm::epsilonEqual(a, b, 0.0001f);
    return r[0] && r[1] && r[2];
}

TEST_CASE("malt::transform defaults", "[malt::transform]")
{
    malt::transform t;
    REQUIRE(t.get_pos() == glm::vec3());
    REQUIRE(t.get_up() == glm::vec3(0, 1, 0));
    REQUIRE(t.get_right() == glm::vec3(1, 0, 0));
    REQUIRE(t.get_forward() == glm::vec3(0, 0, 1));
}

TEST_CASE("malt::transform translation", "[malt::transform]")
{
    malt::transform t;
    t.translate({0, 0, 1});
    REQUIRE(t.get_pos() == glm::vec3(0, 0, 1));
    t.translate({0, 1, 0});
    REQUIRE(t.get_pos() == glm::vec3(0, 1, 1));
}

TEST_CASE("malt::transform rotation", "[malt::transform]")
{
    malt::transform t;
    t.rotate(glm::vec3(0, 90, 0));

    REQUIRE(equal(t.get_forward(), glm::vec3{1, 0, 0}));
    REQUIRE(equal(t.get_up(), glm::vec3{0, 1, 0}));
    REQUIRE(equal(t.get_right(), glm::vec3{0, 0, -1}));
}

TEST_CASE("malt::transform rotation + translation", "[malt::transform]")
{
    malt::transform t;
    t.rotate(glm::vec3{0, 90, 0});
    t.translate(glm::vec3{0, 0, 1}); // move forward

    REQUIRE(equal(t.get_pos(), glm::vec3{1, 0, 0}));
}

TEST_CASE("malt::transform local mat4", "[malt::transform]")
{
    malt::transform t;
    t.rotate(glm::vec3{0, 90, 0});

    auto mat = t.get_local_mat4();
    auto fwd = glm::vec3(mat * glm::vec4(0, 0, 1, 0));

    REQUIRE(equal(fwd, glm::vec3{1, 0, 0}));

    t.set_scale({2, 2, 2});

    mat = t.get_local_mat4();
    auto point = glm::vec3(mat * glm::vec4(0, 0, 1, 1));
    REQUIRE(equal(point, glm::vec3{2, 0, 0}));
}

TEST_CASE("malt::transform world mat4", "[malt::transform]")
{
    malt::transform parent;
    malt::transform child;

    parent.translate({0, 0, 3});

    child.set_parent(&parent);

    REQUIRE(equal(parent.get_pos(), {0, 0, 3}));
    REQUIRE(equal(glm::vec3(child.get_world_mat4() * glm::vec4(0, 0, 0, 1)), {0, 0, 3}));

    parent.rotate({0, 90, 0});
    child.set_world_dirty();

    REQUIRE(equal(parent.get_forward(), {1, 0, 0}));
    REQUIRE(equal(glm::vec3(child.get_world_mat4() * glm::vec4(0, 0, 1, 0)), {1, 0, 0}));

    child.rotate({0, -90, 0});
    REQUIRE(equal(glm::vec3(child.get_world_mat4() * glm::vec4(0, 0, 1, 0)), {0, 0, 1}));
}


TEST_CASE("malt::transform look_at", "[malt::transform]")
{
    malt::transform t;

    t.look_at({5, 0, 5});

    REQUIRE(equal(t.get_forward(), glm::normalize(glm::vec3{1, 0, 1})));
}