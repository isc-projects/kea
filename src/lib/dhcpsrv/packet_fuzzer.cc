// Copyright (C) 2016-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#ifdef FUZZING

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcpsrv/packet_fuzzer.h>
#include <dhcpsrv/fuzz_log.h>

#include <boost/lexical_cast.hpp>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace std;

// Constants defined in the PacketFuzzer class definition.
constexpr size_t        PacketFuzzer::BUFFER_SIZE;
constexpr size_t        PacketFuzzer::MAX_SEND_SIZE;
constexpr long          PacketFuzzer::MAX_LOOP_COUNT;

// Constructor
PacketFuzzer::PacketFuzzer(uint16_t const port,
                           string const interface,
                           string const address)
    : loop_max_(MAX_LOOP_COUNT), sockaddr_len_(0), sockaddr_ptr_(nullptr), sockfd_(-1) {

    try {
        stringstream reason;    // Used to construct exception messages

        // Number of Kea packet-read loops before Kea exits and AFL starts a
        // new instance.  This is optional: the default is set by the constant
        // MAX_LOOP_COUNT.
        const char *loop_max_ptr(nullptr);
#ifdef HAVE_AFL
        loop_max_ptr = getenv("KEA_AFL_LOOP_MAX");
#endif
        if (loop_max_ptr) {
            try {
                loop_max_ = boost::lexical_cast<long>(loop_max_ptr);
            } catch (const boost::bad_lexical_cast&) {
                isc_throw(FuzzInitFail,
                          "cannot convert loop count " << loop_max_ptr << " to an integer");
            }

            if (loop_max_ <= 0) {
                isc_throw(FuzzInitFail, "KEA_AFL_LOOP_MAX is "
                                            << loop_max_ << ". "
                                            << "It must be an integer greater than zero.");
            }
        }

        IOAddress io_address(address);

        // Set up address structures used to route the packets from AFL to Kea.
        createAddressStructures(port, interface, io_address);

        // Create the socket through which packets read from stdin will be sent
        // to the port on which Kea is listening.  This is closed in the
        // destructor.
        sockfd_ = socket(io_address.isV4() ? AF_INET : AF_INET6, SOCK_DGRAM, 0);
        if (sockfd_ < 0) {
            LOG_FATAL(fuzz_logger, FUZZ_SOCKET_CREATE_FAIL)
                      .arg(strerror(errno));
            return;
        }

        LOG_INFO(fuzz_logger, FUZZ_INIT_COMPLETE).arg(interface).arg(address)
                 .arg(port).arg(loop_max_);

    } catch (const FuzzInitFail& e) {
        // AFL tends to make it difficult to find out what exactly has failed:
        // make sure that the error is logged.
        LOG_FATAL(fuzz_logger, FUZZ_INIT_FAIL).arg(e.what());
        throw;
    }
}

// Destructor
PacketFuzzer::~PacketFuzzer() {
    static_cast<void>(close(sockfd_));
}

// Set up address structures.
void
PacketFuzzer::createAddressStructures(uint16_t const port,
                                      string const& interface,
                                      IOAddress const& io_address) {
    string const address(io_address.toText());

    // Set up the appropriate data structure depending on the address given.
    if (io_address.isV6()) {
        // Expecting IPv6 and the address contains a colon, so assume it is an
        // an IPv6 address.
        memset(&servaddr6_, 0, sizeof (servaddr6_));

        servaddr6_.sin6_family = AF_INET6;
        if (inet_pton(AF_INET6, address.c_str(), &servaddr6_.sin6_addr) != 1) {
            isc_throw(FuzzInitFail,
                      "inet_pton() failed: can't convert " << address << " to an IPv6 address");
        }
        servaddr6_.sin6_port = htons(port);

        // Interface ID is needed for IPv6 address structures.
        servaddr6_.sin6_scope_id = if_nametoindex(interface.c_str());
        if (servaddr6_.sin6_scope_id == 0) {
            isc_throw(FuzzInitFail,
                      "error retrieving interface ID for " << interface << ": " << strerror(errno));
        }

        sockaddr_ptr_ = reinterpret_cast<sockaddr*>(&servaddr6_);
        sockaddr_len_ = sizeof(servaddr6_);

    } else if (io_address.isV4()) {
        // Expecting an IPv4 address and it contains a dot, so assume it is.
        // This check is done after the IPv6 check, as it is possible for an
        // IPv4 address to be embedded in an IPv6 one.
        memset(&servaddr4_, 0, sizeof(servaddr4_));

        servaddr4_.sin_family = AF_INET;
        if (inet_pton(AF_INET, address.c_str(), &servaddr4_.sin_addr) != 1) {
            isc_throw(FuzzInitFail,
                      "inet_pton() failed: can't convert " << address << " to an IPv4 address");
        }
        servaddr4_.sin_port = htons(port);

        sockaddr_ptr_ = reinterpret_cast<sockaddr*>(&servaddr4_);
        sockaddr_len_ = sizeof(servaddr4_);

    } else {
        // Should never happen.
        isc_throw(FuzzInitFail, "unknown IOAddress IP version");
    }
}

void
PacketFuzzer::transfer() const {
    // Read from stdin.  Just return if nothing is read (or there is an error)
    // and hope that this does not cause a hang.
    uint8_t buf[BUFFER_SIZE];
    ssize_t const length(read(0, buf, sizeof(buf)));

    transfer(&buf[0], length);
}

// This is the main fuzzing function. It receives data from fuzzing engine over
// stdin and then sends it to the configured UDP socket.
void
PacketFuzzer::transfer(uint8_t const* data, size_t size) const {
    char buf[BUFFER_SIZE];
    ssize_t const length(size);

    if (data) {
        memcpy(&buf[0], data, min(BUFFER_SIZE, size));
    }

    // Save the errno in case there was an error because if debugging is
    // enabled, the following LOG_DEBUG call may destroy its value.
    int errnum = errno;
    LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE_DETAIL, FUZZ_DATA_READ).arg(length);

    if (length > 0) {
        // Now send the data to the UDP port on which Kea is listening.
        // Send the data to the main Kea thread.  Limit the size of the
        // packets that can be sent.
        size_t send_len = (size < MAX_SEND_SIZE) ? size : MAX_SEND_SIZE;
        ssize_t sent = sendto(sockfd_, buf, send_len, 0, sockaddr_ptr_,
                              sockaddr_len_);
        if (sent < 0) {
            LOG_ERROR(fuzz_logger, FUZZ_SEND_ERROR).arg(strerror(errno));
        } else if (sent != length) {
            LOG_WARN(fuzz_logger, FUZZ_SHORT_SEND).arg(length).arg(sent);
        } else {
            LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE_DETAIL, FUZZ_SEND).arg(sent);
        }
    } else {
        // Read did not get any bytes.  A zero-length read (EOF) may have been
        // generated by AFL, so don't log that.  But otherwise log an error.
        if (length != 0) {
            LOG_ERROR(fuzz_logger, FUZZ_READ_FAIL).arg(strerror(errnum));
        }
    }
}

#endif  // FUZZING
