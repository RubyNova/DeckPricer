#include <Client.hpp>

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        DeckPricer::Bot::Client::FromJsonFile(std::filesystem::path(std::string(argv[1])));
    }

    return 0;
}