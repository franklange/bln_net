#include <bln_net/udp_socket_hb_cli.hpp>
#include <bln_net/utils.hpp>

#include <cstdint>
#include <string>

auto main(int, char** argv) -> int
{

    bln_net::udp::socket_hb_cli s{static_cast<std::uint16_t>(std::stoi(argv[1]))};

    std::string in;

    while (std::getline(std::cin, in))
        s.put({{"127.0.0.1", 8000}, bln_net::to_bytes(in)});

    return 0;
}
