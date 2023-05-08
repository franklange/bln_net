#include <bln_net/local_socket_hb.hpp>
#include <bln_net/utils.hpp>

#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using Socket = bln_net::local::socket_hb;
using namespace std::chrono_literals;

std::atomic_bool g_running{true};

void rx(Socket& s)
{
    while (g_running)
    {
        const auto p = s.wait(500ms);
        if (!p)
            continue;

        if (p->data.empty())
        {
            std::cout << "server timeout" << std::endl;
            break;
        }

        std::cout << bln_net::to_string(p->data) << std::endl;
    }
}

auto main() -> int
{
    const std::string server{"/tmp/srv.socket"};

    Socket s{"/tmp/client_1"};
    std::thread receiver{&rx, std::ref(s)};

    s.put({server, bln_net::to_bytes("connect")});

    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line == "q")
            break;

        s.put({server, bln_net::to_bytes(line)});
    }

    g_running = false;
    receiver.join();

    return 0;
}
