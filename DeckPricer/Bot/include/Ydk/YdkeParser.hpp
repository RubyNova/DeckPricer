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
#include <base64.h>

namespace DeckPricer::Bot::Ydk
{
    struct SlicedDeckData
    {
        std::vector<uint32_t> main;
        std::vector<uint32_t> extra;
        std::vector<uint32_t> side;
    };

    class YdkeParser
    {
    private:
        [[nodiscard]] static inline std::vector<uint32_t> ByteToIdArray(const std::string& inputData) noexcept
        {
            const char* array = inputData.c_str();
            const size_t length = inputData.size();
            std::vector<uint32_t> decoded(length / sizeof(uint32_t));
            std::memcpy(decoded.data(), array, length);
            return decoded;
        }

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

            while (std::getline(dataStream, segment, '!'))
            {
                output.emplace_back(segment);
            }

            if (output.size() != 3)
            {
                return std::nullopt;
            }

            auto main = base64_decode(output[0], false);
            auto extra = base64_decode(output[1], false);
            auto side = base64_decode(output[2], false);

            SlicedDeckData deckData;

            deckData.main = ByteToIdArray(main);
            deckData.extra = ByteToIdArray(extra);
            deckData.side = ByteToIdArray(side);

            return deckData;
        }
    };
}

#endif

// TEST URL:       ydke://o6lXBZyFNAI=!viOnAg==!7ydRAA==!
// Expected output:
/*
{
  main: Uint32Array(2) [ 89631139, 36996508 ],
  extra: Uint32Array(1) [ 44508094 ],
  side: Uint32Array(1) [ 5318639 ]
}
*/
