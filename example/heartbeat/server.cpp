#include <bln_net/udp.hpp>

#include <iostream>

auto main() -> int
{
    bln_net::udp::socket_hb_srv s{8000};

    while (true)
    {
        const auto [remote, bytes] = s.wait();
        std::cout << remote.to_string();

        if (bytes.empty())
            std::cout << " [dead]" << std::endl;
        else
            std::cout << " [msg]" << std::endl;
    }

    return 0;
}
