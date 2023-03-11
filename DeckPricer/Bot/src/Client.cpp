// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <Client.hpp>
#include <dpp/nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <Commands/PingCommand.hpp>
#include <Commands/PriceCommand.hpp>
#include <Commands/SearchCommand.hpp>

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
    }

    void Client::RegisterCommand(Commands::CommandInfo commandInfo)
    {
        auto it = std::find_if(_commandsToRegister.begin(), _commandsToRegister.end(), [&](auto obj) { return commandInfo.name == obj.name; });

        if (it != _commandsToRegister.end())
        {
            throw std::runtime_error("Command with duplicate name detected. Unique names only.");
        }

        _commandsToRegister.emplace_back(commandInfo);
    }

    void Client::RegisterCommand(const std::string &name, const std::string description, std::vector<dpp::command_option> options, std::function<void(const dpp::slashcommand_t &)> fnPtr)
    {
        RegisterCommand(Commands::CommandInfo{name, description, options, fnPtr});
    }

    void Client::RegisterDefaultCommands()
    {
        RegisterCommandType<Commands::PingCommand>();
        RegisterCommandType<Commands::PriceCommand>(_bot);
        RegisterCommandType<Commands::SearchCommand>(_bot);
    }

    void Client::Start()
    {
        _bot.on_log([](dpp::log_t log) { std::cerr << log.message << std::endl; });
        _bot.on_slashcommand([&](auto event) {
            _slashCommands.at(event.command.get_command_name())(event);
        });
 
        _bot.on_ready([&](auto event) {
            if (dpp::run_once<struct register_bot_commands>()) {

                for (auto&& info : _commandsToRegister)
                {
                    dpp::slashcommand command(info.name, info.description, _bot.me.id);
                    auto& options = info.commandOptions;
                    
                    for(auto&& option : options)
                    {
                        command.add_option(option);
                    }

                    _bot.global_command_create(command);
                    _slashCommands.emplace(info.name, info.fnPtr);
                }

/*
                auto bla = _bot.global_commands_get_sync();

                for (auto [key, value] : bla)
                { 
                    _bot.global_command_delete_sync(key);
                }

                */
            }
        });
 
        _bot.start(dpp::st_wait);
    }
}