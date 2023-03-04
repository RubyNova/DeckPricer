// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#ifndef DECKPRICER_BOT_CLIENT_HPP
#define DECKPRICER_BOT_CLIENT_HPP

#include <dpp/dpp.h>
#include <filesystem>

namespace DeckPricer::Bot
{
    class Client
    {
    private:
        dpp::cluster _bot;

    public:
        static Client FromJson(const std::string& jsonString);
        static Client FromJsonFile(const std::filesystem::path& fileLocation);

        Client(const std::string& botToken) noexcept;
    };
}


#endif