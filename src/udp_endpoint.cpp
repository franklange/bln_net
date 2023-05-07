#include <bln_net/udp_endpoint.hpp>

#include <boost/functional/hash.hpp>

namespace bln_net::udp {

endpoint::endpoint(std::string a, uint16_t p)
    : addr{a}
    , port{p}
{}

auto endpoint::to_string() const -> std::string
{
    return addr + ":" + std::to_string(port);
}

} // namespace bln_net::udp

auto std::hash<bln_net::udp::endpoint>::operator()(const bln_net::udp::endpoint& e) const -> std::size_t
{
    std::size_t h{0};
    boost::hash_combine(h, e.addr);
    boost::hash_combine(h, e.port);

    return h;
}
