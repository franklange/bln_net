#include <bln_net/local_socket_asio.hpp>
#include <bln_net/utils.hpp>

#include <iostream>
#include <string>

auto main() -> int
{
    bln_net::local::socket_asio s{"/tmp/client_1"};

    std::string line;
    while (std::getline(std::cin, line))
    {
        s.put({"/tmp/srv.socket", bln_net::to_bytes(line)});
        std::cout << bln_net::to_string(s.wait().data) << std::endl;
    }

    return 0;
}
