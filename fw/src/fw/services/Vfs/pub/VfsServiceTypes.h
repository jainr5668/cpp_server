#pragma once
#include "customDataType.h"
#include <string>
#include <nlohmann/json.hpp>

namespace services
{
    class VfsCommand
    {
    public:
        CustomDataType<std::string> command;

        VfsCommand() = default;
        VfsCommand(std::string command_)
        {
            command.value = command_;
        }
        friend void to_json(nlohmann::json &j, const VfsCommand &p)
        {
            j = nlohmann::json{
                {"command", p.command.value}};
        }
        friend void from_json(const nlohmann::json &j, VfsCommand &p)
        {
            j.at("command").get_to(p.command.value);
        }
    };
} // namespace services