#include <Client.hpp>

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        auto client = DeckPricer::Bot::Client::FromJsonFile(std::filesystem::path(std::string(argv[1])));
        client.RegisterDefaultCommands();
        client.Start();
    }

    return 0;
}