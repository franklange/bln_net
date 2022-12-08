#include <bln_net/udp_endpoint.hpp>

#include <boost/functional/hash.hpp>

namespace bln_net::udp {

auto endpoint::to_string() const -> std::string
{
    return addr + ":" + std::to_string(port);
}

auto ep_hash::operator()(const endpoint& e) const -> std::size_t
{
    std::size_t h{0};
    boost::hash_combine(h, e.addr);
    boost::hash_combine(h, e.port);

    return h;
}

} // namespace bln_net::udp
