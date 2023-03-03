// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <Client.hpp>

namespace DeckPricer::Bot
{
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