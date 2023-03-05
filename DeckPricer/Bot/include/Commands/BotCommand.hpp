// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#ifndef DECKPRICER_BOT_COMMANDS_BOTCOMMAND_HPP
#define DECKPRICER_BOT_COMMANDS_BOTCOMMAND_HPP

#include <dpp/dpp.h>
#include "CommandInfo.hpp"

namespace DeckPricer::Bot::Commands
{
    class BotCommand
    {
        public:
        [[nodiscard]] virtual std::string GetCommandName() const noexcept = 0;
        [[nodiscard]] virtual std::string GetCommandDescription() const noexcept = 0;
        virtual void Execute(const dpp::slashcommand_t& commandInfo) = 0;

        inline operator CommandInfo() const noexcept
        {
            return CommandInfo{GetCommandName(), GetCommandDescription(), [this](auto commandInfo) { const_cast<BotCommand*>(this)->Execute(commandInfo); }};
        }
    };
}


#endif