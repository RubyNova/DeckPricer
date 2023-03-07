// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#ifndef DECKPRICER_YDK_YDKEPARSER_HPP
#define DECKPRICER_YDK_YDKEPARSER_HPP

#include <optional>
#include <regex>
#include <string>
#include <sstream>
#include <vector>
#include "../Utilities/StringHelpers.hpp"
#include <iostream>

namespace DeckPricer::Bot::Ydk
{
    struct SlicedDeckData
    {
        std::string main;
        std::string extra;
        std::string side;
    };

    class YdkeParser
    {
    public:
        [[nodiscard]] static inline std::optional<SlicedDeckData> TryGetDeckSections(const std::string& inputData) noexcept
        {
            static std::regex ydkeRegex("ydke://[A-Za-z0-9+/=]*?![A-Za-z0-9+/=]*?![A-Za-z0-9+/=]*?!", std::regex_constants::ECMAScript);

            std::smatch m;
            std::regex_search(inputData, m, ydkeRegex);

            if (m.size() != 1)
            {
                return std::nullopt;
            }

            auto substringData = Utilities::StringHelpers::RemoveSubstring(inputData, "ydke://");

            std::stringstream dataStream(substringData);
            std::string segment;
            std::vector<std::string> output{};

            while(std::getline(dataStream, segment, '!'))
            {
                output.emplace_back(segment);
            }
            
            if (output.size() != 3)
            {
                return std::nullopt;
            }
            
            return SlicedDeckData { output[0], output[1], output [2] };
        }
    };
}

#endif