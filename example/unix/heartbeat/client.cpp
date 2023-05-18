#include <bln_net/local_socket_hb.hpp>
#include <bln_net/utils.hpp>

#include <iostream>
#include <string>
#include <thread>

using Socket = bln_net::local::socket_hb;

void cmdline(Socket& s)
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line == "q")
            break;

        std::cout << ">> " << line << std::endl;

        s.put({"/tmp/srv.socket", bln_net::to_bytes(line)});
    }
}

auto main() -> int
{
    bln_net::local::socket_hb s{"/tmp/client_1"};

    std::thread cliRunner{cmdline, std::ref(s)};

    while (true)
    {
        const auto p = s.wait();
        if (p.data.empty())
        {
            std::cout << "server timeout" << std::endl;
            break;
        }

        std::cout << bln_net::to_string(p.data) << std::endl;
    }

    std::cout << "done" << std::endl;

    cliRunner.join();

    return 0;
}
