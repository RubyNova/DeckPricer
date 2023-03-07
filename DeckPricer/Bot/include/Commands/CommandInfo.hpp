// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#ifndef DECKPRICER_BOT_COMMANDS_COMMANDINFO_HPP
#define DECKPRICER_BOT_COMMANDS_COMMANDINFO_HPP

#include <string>
#include <functional>
#include <dpp/dpp.h>

namespace DeckPricer::Bot::Commands
{
    struct CommandInfo
    {
        std::string name;
        std::string description;
        std::vector<dpp::command_option> commandOptions;
        std::function<void(const dpp::slashcommand_t&)> fnPtr;
    };
}

#endif