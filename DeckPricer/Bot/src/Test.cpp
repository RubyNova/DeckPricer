#include <dpp/dpp.h>

// compiles.
/*
void DoThing()
{
        dpp::cluster bot("aaaaaaa");
 
    bot.on_slashcommand([](auto event) {
         if (event.command.get_command_name() == "ping") {
             event.reply("Pong!");
         }
    });
 
    bot.on_ready([&bot](auto event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(
                dpp::slashcommand("ping", "Ping pong!", bot.me.id)
            );
        }
    });
 
    bot.start(dpp::st_wait);
}
*/