// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#ifndef DECKPRICER_BOT_COMMANDS_PRICECOMMAND_HPP
#define DECKPRICER_BOT_COMMANDS_PRICECOMMAND_HPP

#include "BotCommand.hpp"
#include "../Ydk/YdkeParser.hpp"

namespace DeckPricer::Bot::Commands
{
    class PriceCommand final : public BotCommand
    {
    public:
        [[nodiscard]] virtual inline std::string GetCommandName() const noexcept final
        {
            return "price";
        }

        [[nodiscard]] virtual inline std::string GetCommandDescription() const noexcept final
        {
            return "Gets the price of a deck";
        }

        [[nodiscard]] inline virtual std::vector<dpp::command_option> GetCommandOptions() const noexcept final
        {
            return std::vector<dpp::command_option> 
            {
                dpp::command_option(dpp::co_string, "ydke", "The YDK Export string", true)
            };
        }

        inline virtual void Execute(const dpp::slashcommand_t& commandInfo) final
        {
            auto ydkeString = std::get<std::string>(commandInfo.get_parameter("ydke"));
            auto optionalObject = Ydk::YdkeParser::TryGetDeckSections(ydkeString);

            if (optionalObject.has_value())
            {
                commandInfo.reply("I can't actually use the YDKE data in a meaningful way yet, but I can tell you its a valid URI!");
            }
            else
            {
                commandInfo.reply("YDKE Data is invalid! Please double check that you are passing in a valid YDKE URI.");
            }
        }
    };
}

#endif