#pragma once

#include <boost/fiber/mutex.hpp>
#include <boost/system/error_code.hpp>

#include <chrono>
#include <cstdint>
#include <vector>

namespace bln_net {

using namespace std::chrono_literals;

using byte = std::uint8_t;
using bytes = std::vector<byte>;

using error = boost::system::error_code;

using mutex = boost::fibers::mutex;
using spinlock = std::lock_guard<mutex>;

using timeout = std::chrono::microseconds;

} // namespace bln_net
