#include <bln_net/udp_packet.hpp>

namespace bln_net::udp {

auto packet::to_string() const -> std::string
{
    std::string res;
    res.reserve(32);

    res += "[";
    res += remote.to_string();
    res += "|b'";
    res += std::to_string(data.size());
    res += "]";

    return res;
}

} // namespace bln_net::udp
