#include <bln_net/udp_socket_asio.hpp>
#include <bln_net/utils.hpp>

#include <iostream>

auto main() -> int
{
    bln_net::udp::socket_asio s{8000};

    while (true)
    {
        auto p = s.wait();
        std::cout << "[rx] " << p.to_string() << std::endl;
        s.put(std::move(p));
    }

    return 0;
}
