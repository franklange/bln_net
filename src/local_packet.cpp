#include <bln_net/local_packet.hpp>

namespace bln_net::local {

auto packet::to_string() const -> std::string
{
    return "[" + remote + " | " + std::to_string(data.size()) + " bytes]";
}

} // namespace bln_net::local
