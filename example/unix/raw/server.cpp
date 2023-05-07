#include <bln_net/local_socket_asio.hpp>
#include <bln_net/utils.hpp>

#include <iostream>

auto main() -> int
{
    bln_net::local::socket_asio s{"/tmp/srv.socket"};

    while (true)
    {
        const auto p = s.wait();
        std::cout << p.remote << "|" << bln_net::to_string(p.data) << std::endl;

        s.put({p.remote, bln_net::to_bytes("ACK")});
    }

    return 0;
}
