// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#ifndef DECKPRICER_BOT_COMMANDS_PINGCOMMAND_HPP
#define DECKPRICER_BOT_COMMANDS_PINGCOMMAND_HPP

#include "BotCommand.hpp"

namespace DeckPricer::Bot::Commands
{
    class PingCommand final : public BotCommand
    {
    public:
        [[nodiscard]] virtual inline std::string GetCommandName() const noexcept final
        {
            return "ping";
        }

        [[nodiscard]] virtual inline std::string GetCommandDescription() const noexcept final
        {
            return "Ping pong!";
        }

        inline virtual void Execute(const dpp::slashcommand_t& commandInfo) final
        {
            commandInfo.reply("Pong!");
        }
    };
}

#endif