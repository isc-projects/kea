// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cryptolink/crypto_rng.h>
#include <util/multi_threading_mgr.h>
#include <client_server.h>
#include <radius_log.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <cerrno>
#include <chrono>
#include <limits>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::util;
using namespace std;
using namespace std::chrono;
namespace ph = std::placeholders;

/// @brief RAII wrapper over struct addrinfo.
struct AddrInfo {
    AddrInfo(string const& hostname) : addrinfo_(0) {
        int const err(getaddrinfo(hostname.c_str(), 0, 0, &addrinfo_));
        if (err != 0) {
            string const errmsg(gai_strerror(err));
            isc_throw(BadValue, "failed to resolve '" << hostname << "': " << errmsg);
        }
        if (!addrinfo_ || !addrinfo_->ai_addr) {
            isc_throw(BadValue, "getaddrinfo('" << hostname << ") returned null");
        }
    }
    ~AddrInfo() {
        freeaddrinfo(addrinfo_);
    }
    struct addrinfo *addrinfo_;
};


namespace isc {
namespace radius {

IOAddress
Server::getAddress(const string& name) {
    AddrInfo res(name);
    short family = res.addrinfo_->ai_family;
    if (family == AF_INET) {
        struct sockaddr_in* sin4 =
            reinterpret_cast<struct sockaddr_in*>(res.addrinfo_->ai_addr);
        vector<uint8_t> in4(4);
        memmove(&in4[0], &sin4->sin_addr, 4);
        return (IOAddress::fromBytes(AF_INET, &in4[0]));
    } else if (family == AF_INET6) {
        struct sockaddr_in6* sin6 =
            reinterpret_cast<struct sockaddr_in6*>(res.addrinfo_->ai_addr);
        vector<uint8_t> in6(16);
        memmove(&in6[0], &sin6->sin6_addr, 16);
        return (IOAddress::fromBytes(AF_INET6, &in6[0]));
    }
    isc_throw(BadValue, "getaddrinfo('" << name << ") returned unknown family "
              << family);
}

IOAddress
Server::getSrcAddress(const IOAddress& dest) {
    vector<uint8_t> bindest = dest.toBytes();
    vector<uint8_t> binsrc(bindest.size());
    if (bindest.size() == 4) {
        struct sockaddr_in dest4;
        socklen_t len = sizeof(dest4);
        memset(&dest4, 0, len);
        dest4.sin_family = AF_INET;
#ifdef HAVE_SA_LEN
        dest4.sin_len = len;
#endif
        memmove(&dest4.sin_addr, &bindest[0], 4);
        dest4.sin_port = htons(11812);
        int fd = socket(PF_INET, SOCK_DGRAM, 0);
        if (fd < 0) {
            isc_throw(Unexpected, "socket() failed: " << strerror(errno));
        }
        int err = connect(fd, reinterpret_cast<const struct sockaddr*>(&dest4),
                          len);
        if (err < 0) {
            static_cast<void>(close(fd));
            isc_throw(Unexpected, "connect() failed: " << strerror(errno));
        }
        struct sockaddr_in src4;
        memset(&src4, 0, len);
        err = getsockname(fd, reinterpret_cast<struct sockaddr*>(&src4), &len);
        static_cast<void>(close(fd));
        if ((err < 0) || (len != sizeof(src4))) {
            isc_throw(Unexpected, "getsockname() failed: " << strerror(errno));
        }
        memmove(&binsrc[0], &src4.sin_addr, 4);
        return (IOAddress::fromBytes(AF_INET, &binsrc[0]));
    } else if (bindest.size() == 16) {
        struct sockaddr_in6 dest6;
        socklen_t len = sizeof(dest6);
        memset(&dest6, 0, len);
        dest6.sin6_family = AF_INET6;
#ifdef HAVE_SA_LEN
        dest6.sin6_len = len;
#endif
        memmove(&dest6.sin6_addr, &bindest[0], 16);
        dest6.sin6_port = htons(11812);
        int fd = socket(PF_INET6, SOCK_DGRAM, 0);
        if (fd < 0) {
            isc_throw(Unexpected, "socket() failed: " << strerror(errno));
        }
        int err = connect(fd, reinterpret_cast<const struct sockaddr*>(&dest6),
                          len);
        if (err < 0) {
            static_cast<void>(close(fd));
            isc_throw(Unexpected, "connect() failed: " << strerror(errno));
        }
        struct sockaddr_in6 src6;
        memset(&src6, 0, len);
        err = getsockname(fd, reinterpret_cast<struct sockaddr*>(&src6), &len);
        static_cast<void>(close(fd));
        if ((err < 0) || (len != sizeof(src6))) {
            isc_throw(Unexpected, "getsockname() failed: " << strerror(errno));
        }
        memmove(&binsrc[0], &src6.sin6_addr, 16);
        return (IOAddress::fromBytes(AF_INET6, &binsrc[0]));
    } else {
        isc_throw(Unexpected, "address length is not 4 nor 16: "
                  << bindest.size());
    }
}

Server::~Server() {
    if (!secret_.empty()) {
        memset(&secret_[0], 0, secret_.size());
    }
    secret_.clear();
}


void
Server::setLocalAddress(const IOAddress& local_addr) {
    if (peer_addr_.getFamily() != local_addr.getFamily()) {
        isc_throw(BadValue, "address family mismatch: peer "
                  << peer_addr_.toText() << ", local " << local_addr.toText());
    }
    local_addr_ = local_addr;
}

void
Server::setTimeout(unsigned timeout) {
    if (static_cast<uint64_t>(timeout) > numeric_limits<long>::max() / 1000) {
        isc_throw(OutOfRange, "too large timeout " << timeout
                  << " > " << std::numeric_limits<long>::max() / 1000);
    }
    timeout_ = (timeout == 0 ? 1 : timeout);
}

void
Server::setSecret(const string& secret) {
    if (secret.empty()) {
        isc_throw(BadValue, "empty secret");
    }
    secret_ = secret;
}

steady_clock::time_point
Server::getDeadtimeEnd() const {
    MultiThreadingLock lock(*mutex_);

    return (deadtime_end_);
}

void
Server::setDeadtimeEnd(const steady_clock::time_point& deadtime_end) {
    MultiThreadingLock lock(*mutex_);

    deadtime_end_ = deadtime_end;
}

ElementPtr
Server::toElement() const {
    ElementPtr result = Element::createMap();

    // Peer address.
    result->set("peer-address", Element::create(peer_addr_.toText()));

    // Port.
    result->set("peer-port", Element::create(peer_port_));

    // Local address.
    result->set("local-address", Element::create(local_addr_.toText()));

    // Secret.
    result->set("secret", Element::create(secret_));

    // Timeout.
    result->set("timeout", Element::create(static_cast<long long>(timeout_)));

    // Deadtime.
    result->set("deadtime", Element::create(static_cast<long long>(deadtime_)));

    if (deadtime_ != 0) {
        MultiThreadingLock lock(*mutex_);

        auto delta = deadtime_end_ - steady_clock().now();
        seconds secs = duration_cast<seconds>(delta);
        result->set("deadtime-end",
                    Element::create(static_cast<long long>(secs.count())));
    }
    return (result);
}

} // end of namespace isc::radius
} // end of namespace isc
