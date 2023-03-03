// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#ifndef DECKPRICER_BOT_CLIENT_HPP
#define DECKPRICER_BOT_CLIENT_HPP

#include <dpp/dpp.h>

namespace DeckPricer::Bot
{
    class Client
    {
    private:
        dpp::cluster _bot;

    public:
        Client(const std::string& botToken) noexcept;
    };
}


#endif