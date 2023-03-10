// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#ifndef  DECKPRICER_BOT_COMMANDS_SEARCHCOMMAND_HPP
#define  DECKPRICER_BOT_COMMANDS_SEARCHCOMMAND_HPP

#include "BotCommand.hpp"
#include <dpp/nlohmann/json.hpp>

namespace DeckPricer::Bot::Commands
{
    class SearchCommand final : public BotCommand
    {
    private:
        static inline const std::string AllSources = "price_info_source_all";
        static inline const std::string Cardmarket = "price_info_source_cardmarket";
        static inline const std::string TCGPlayer = "price_info_source_tcgplayer";
        static inline const std::string EbayUS = "price_info_source_ebay_us";
        static inline const std::string AmazonUS = "price_info_source_amazon_us";
        static inline const std::string CoolStuffInc = "price_info_source_coolstuffinc";

        dpp::cluster& _bot;

    public:
        explicit SearchCommand(dpp::cluster& bot) noexcept : BotCommand(), _bot(bot) {}

        [[nodiscard]] virtual inline std::string GetCommandName() const noexcept final
        {
            return "search";
        }

        [[nodiscard]] virtual inline std::string GetCommandDescription() const noexcept final
        {
            return "Search for a specific card";
        }

        [[nodiscard]] inline virtual std::vector<dpp::command_option> GetCommandOptions() const noexcept final
        {
            return std::vector<dpp::command_option> 
            {
                dpp::command_option(dpp::co_string, "card_name", "The name of the card.", true),
                dpp::command_option(dpp::co_string, "price_info_source", "The price source to display for current market information. Cached and updated hourly.", false)
                    .add_choice(dpp::command_option_choice("All", AllSources))
                    .add_choice(dpp::command_option_choice("Cardmarket", Cardmarket))
                    .add_choice(dpp::command_option_choice("TCGPlayer", TCGPlayer))
                    .add_choice(dpp::command_option_choice("Ebay-US", EbayUS))
                    .add_choice(dpp::command_option_choice("Amazon-US", AmazonUS))
                    .add_choice(dpp::command_option_choice("CoolStuffInc", CoolStuffInc))
            };
        }

        inline virtual void Execute(const dpp::slashcommand_t& commandInfo) final
        {
            auto cardName = std::get<std::string>(commandInfo.get_parameter("card_name"));
            auto priceInfoSource = commandInfo.get_parameter("price_info_source");
            std::string priceInfoSourceOutput = "price_info_source_all";

            std::visit([&priceInfoSourceOutput](auto&& parameter){
                using TMember = std::decay_t<decltype(parameter)>;
                if constexpr (std::is_same_v<TMember, std::string>)
                {
                    priceInfoSourceOutput = parameter;
                }
            }, priceInfoSource);

            commandInfo.thinking();

            _bot.request("https://db.ygoprodeck.com/api/v7/cardinfo.php?name=" + cardName, dpp::m_get, [commandInfoCopy = commandInfo](const dpp::http_request_completion_t& response) mutable {
                auto j = json::parse(response.body);
                auto& obj = j["data"][0];
                auto id = obj.value<uint64_t>("id", 0);
                auto name = obj.value<std::string>("name", std::string());
                auto type = obj.value<std::string>("type", std::string());

                std::string returnObj = "Card ID: " + std::to_string(id) + ", " + "Name: " + name + ", " + "Type: " + type;

                commandInfoCopy.edit_response(returnObj);
            });
        }
    };
}

#endif