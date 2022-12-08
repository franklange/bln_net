#include "server.hpp"

#include <bln_net/udp_socket_asio.hpp>

auto main() -> int
{
    bln_net::udp::socket_asio socket{8000};

    server server{socket};

    while (true)
        server.process_request();

    return 0;
}
