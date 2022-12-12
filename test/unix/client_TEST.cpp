#include <bln_net/local_socket_asio.hpp>
#include <bln_net/utils.hpp>

#include <iostream>

auto main() -> int
{
    bln_net::local::socket_asio s{"/tmp/client"};

    const std::string msg{"hi"};

    s.put({"/tmp/server", bln_net::to_bytes(msg)});
    std::cout << "tx: " << msg << std::endl;

    const auto p = s.wait();
    std::cout << "rx: " << p.to_string() << std::endl;

    return 0;
}
