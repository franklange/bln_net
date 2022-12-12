#include <bln_net/udp_socket_asio.hpp>
#include <bln_net/utils.hpp>

#include <iostream>

auto main() -> int
{
    bln_net::udp::socket_asio s{9000};

    const std::string msg{"hi"};

    s.put({{"127.0.0.1", 8000}, bln_net::to_bytes(msg)});
    std::cout << "tx: " << msg << std::endl;

    const auto p = s.wait();
    std::cout << "rx: " << p.to_string() << std::endl;

    return 0;
}
