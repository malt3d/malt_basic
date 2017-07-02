#pragma once
//
// Created by fatih on 3.07.2017.
//

namespace YAML
{
    class Node;
}

namespace malt
{
    void load_scene(const YAML::Node& scene_node);
}