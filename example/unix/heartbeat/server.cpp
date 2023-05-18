#include <bln_net/local_socket_hb.hpp>
#include <bln_net/utils.hpp>

#include <iostream>

auto main() -> int
{
    bln_net::local::socket_hb s{"/tmp/srv.socket"};

    while (true)
    {
        const auto p = s.wait();

        if (p.data.empty())
        {
            std::cout << p.remote << "|timeout" << std::endl;
            continue;
        }

        std::cout << p.remote << "|" << bln_net::to_string(p.data) << std::endl;
        s.put({p.remote, bln_net::to_bytes("ACK")});
    }

    return 0;
}
