#include <bln_net/local_socket_asio.hpp>
#include <bln_net/utils.hpp>

#include <iostream>

auto main() -> int
{
    bln_net::local::socket_asio s{"/tmp/server"};

    while (true)
    {
        auto p = s.wait();
        std::cout << "[rx] " << p.to_string() << std::endl;
        s.put(std::move(p));
    }

    return 0;
}
