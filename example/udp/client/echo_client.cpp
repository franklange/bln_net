#include "client.hpp"

#include <bln_net/udp.hpp>
#include <bln_net/utils.hpp>

auto main() -> int
{
    bln_net::udp::socket_asio socket{9000};

    client c{socket};
    c.echo("");

    return 0;
}
