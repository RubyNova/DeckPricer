// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef DECKPRICER_BOT_COMMANDS_PRICECOMMAND_HPP
#define DECKPRICER_BOT_COMMANDS_PRICECOMMAND_HPP

#include "BotCommand.hpp"
#include "Ydk/YdkeParser.hpp"

namespace DeckPricer::Bot::Commands
{
    class PriceCommand final: public BotCommand
    {
    private:
        dpp::cluster& _bot;
        
    public:
        explicit PriceCommand(dpp::cluster& bot) : BotCommand(), _bot(bot){}
    
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
            return std::vector<dpp::command_option>{
                dpp::command_option(dpp::co_string, "ydke", "The YDK Export string", true)};
        }

        inline virtual void Execute(const dpp::slashcommand_t& commandInfo) final
        {
            commandInfo.thinking();

            auto ydkeString = std::get<std::string>(commandInfo.get_parameter("ydke"));
            auto optionalObject = Ydk::YdkeParser::TryGetDeckSections(ydkeString);

            if (optionalObject.has_value())
            {
                std::string mainIds;

                for(auto&& value : optionalObject.value().main)
                {
                    if(!mainIds.empty())
                    {
                        mainIds += ",";
                    }
                    mainIds += std::to_string(value);
                }

                _bot.request("https://db.ygoprodeck.com/api/v7/cardinfo.php?id=" + mainIds, dpp::m_get, [commandInfoCopy = commandInfo](const dpp::http_request_completion_t& response) mutable {
                    auto j = json::parse(response.body);
                    auto& arr = j["data"];
                    double finalPrice = 0;
                    
                    for(auto&& val : arr)
                    {
                        finalPrice += std::stod(val["card_prices"][0].value<std::string>("cardmarket_price", std::string()));
                    }

                   // auto id = obj.value<uint64_t>("id", 0);
                   // auto name = obj.value<std::string>("name", std::string());
                   // auto type = obj.value<std::string>("type", std::string());

                    std::string returnObj = "Lowest Cardmarket Price: " + std::to_string(finalPrice) + " EUR";

                    commandInfoCopy.edit_response(returnObj);
                });
            }
            else
            {
                commandInfo.reply("YDKE Data is invalid! Please double check that you are passing in a valid YDKE URI.");
            }
        }
    };
}

#endif