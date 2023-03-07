// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#ifndef DECKPRICER_BOT_CLIENT_HPP
#define DECKPRICER_BOT_CLIENT_HPP

#include <dpp/dpp.h>
#include <filesystem>
#include <unordered_map>
#include "Commands/CommandInfo.hpp"
#include "Commands/BotCommand.hpp"
#include <memory>

namespace DeckPricer::Bot
{
    class Client
    {
    private:
        dpp::cluster _bot;
        std::unordered_map<std::string, std::function<void(const dpp::slashcommand_t&)>> _slashCommands;
        std::vector<Commands::CommandInfo> _commandsToRegister;
        std::vector<std::unique_ptr<Commands::BotCommand>> _commandObjectCache;

    public:
        static Client FromJson(const std::string& jsonString);
        static Client FromJsonFile(const std::filesystem::path& fileLocation);

        Client(const std::string& botToken) noexcept;
        void RegisterCommand(Commands::CommandInfo commandInfo);
        void RegisterCommand(const std::string& name, const std::string description, std::vector<dpp::command_option> options, std::function<void(const dpp::slashcommand_t&)> fnPtr);
        
        template<typename TCommand, typename... Args>
        void RegisterCommandType(Args&&... args)
        {
            static_assert(std::is_base_of_v<Commands::BotCommand, TCommand>, "TCommand must be of type Commands::BotCommand");

            auto command = std::make_unique<TCommand>(std::forward(args)...);
            _commandObjectCache.emplace_back(std::move(command));
            RegisterCommand(*_commandObjectCache.back());
        }

        void RegisterDefaultCommands();
        void Start();
    };
}


#endif