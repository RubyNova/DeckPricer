// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef DECKPRICER_YDK_YDKEPARSER_HPP
#define DECKPRICER_YDK_YDKEPARSER_HPP

#include <optional>
#include <vector>
#include <string>

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
        [[nodiscard]] static std::vector<uint32_t> ByteToIdArray(const std::string& inputData) noexcept;

    public:
        [[nodiscard]] static std::optional<SlicedDeckData> TryGetDeckSections(const std::string& inputData) noexcept; 
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
