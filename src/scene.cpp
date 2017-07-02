//
// Created by fatih on 3.07.2017.
//

#include <malt_basic/scene.hpp>
#include <yaml-cpp/yaml.h>
#include <malt/engine.hpp>
#include <malt/entity.hpp>
#include <malt/serialization.hpp>
#include <iostream>

namespace malt
{
    void load_scene(const YAML::Node& scene_node)
    {
        std::map<std::string, entity> entities;

        for (auto entity : scene_node["entities"])
        {
            auto e = malt::create_entity(entity["name"].as<std::string>());
            for (auto comp : entity["components"])
            {
                auto name = comp.first.as<std::string>();
                malt::add_component(name.c_str(), e);
            }
            entities.emplace(e.get_name(), e);
        }

        for (auto entity : scene_node["entities"])
        {
            auto e = entities[entity["name"].as<std::string>()];
            for (auto comp : entity["components"])
            {
                auto name = comp.first.as<std::string>();
                YAML::Node val = comp.second;

                auto c = malt::get_component(name.c_str(), e);

                auto&& refl = dynamic_reflect(c);
                refl->get_deserialize_function()(std::move(val), c);
            }
        }

        for (auto e : entities)
        {
            YAML::Node n;
            malt::serialize(n, e.second);
            std::cout << n << '\n';
        }
    }
}