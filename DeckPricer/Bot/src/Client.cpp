// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <Client.hpp>
#include <dpp/nlohmann/json.hpp>
#include <iostream>
#include <fstream>

namespace DeckPricer::Bot
{
    Client Client::FromJson(const std::string& jsonString)
    {
        auto j = json::parse(jsonString);
        return Client(j.value<std::string>("token", std::string()));
    }

    Client Client::FromJsonFile(const std::filesystem::path& fileLocation)
    {
        if (!std::filesystem::exists(fileLocation) || std::filesystem::is_directory(fileLocation))
        {
            throw std::runtime_error("File not found.");
        }

        std::ifstream file(fileLocation);

        std::string str(std::istreambuf_iterator<char>{file}, {});

        return FromJson(str);
    }

    Client::Client(const std::string& botToken) noexcept : _bot(botToken)
    {
        _bot.on_slashcommand([](auto event) {
            if (event.command.get_command_name() == "ping") {
                event.reply("Pong!");
            }
        });
 
        _bot.on_ready([&](auto event) {
            if (dpp::run_once<struct register_bot_commands>()) {
                _bot.global_command_create(
                    dpp::slashcommand("ping", "Ping pong!", _bot.me.id)
                );
            }
        });
 
        _bot.start(dpp::st_wait);
    }
}