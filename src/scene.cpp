//
// Created by fatih on 3.07.2017.
//

#include <malt_basic/scene.hpp>
#include <yaml-cpp/yaml.h>
#include <malt/engine.hpp>
#include <malt/entity.hpp>
#include <malt/serialization.hpp>
#include <iostream>
#include <malt/error.hpp>

namespace malt
{
    void load_scene(const YAML::Node& scene_node)
    {
        std::map<std::string, entity> entities;

        /*
         * Two pass deserialization:
         * First pass creates all of the components, but does not deserialize them yet
         * second pass does not create any new component but merely deserializes them.
         * This allows pointers between components to be loaded without too much hassle.
         */

        for (auto entity : scene_node["entities"])
        {
            auto e = malt::create_entity(entity["name"].as<std::string>());
            for (auto comp : entity["components"])
            {
                auto name = comp.first.as<std::string>();
                try{
                    malt::add_component(name.c_str(), e);
                }
                catch (malt::undefined_component& err)
                {
                    std::cerr << "component " << name << " does not exist!\n";
                    throw;
                }
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
    }
}