// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#ifndef DECKPRICER_BOT_UTILITIES_STRINGHELPERS_HPP 
#define DECKPRICER_BOT_UTILITIES_STRINGHELPERS_HPP

#include <string>

namespace DeckPricer::Bot::Utilities
{
    class StringHelpers
    {
    public:
        [[nodiscard]] inline static std::string RemoveSubstring(const std::string& source, const std::string& target) noexcept
        {
            size_t index = source.find(target);

            if (index == std::string::npos)
            {
                return source;
            }

            auto copy = source;
            copy.erase(index, target.size());

            return copy;
        }
    };
};


#endif