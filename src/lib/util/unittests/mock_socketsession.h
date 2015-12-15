// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UTIL_UNITTESTS_MOCKSOCKETSESSION_H
#define UTIL_UNITTESTS_MOCKSOCKETSESSION_H 1

#include <exceptions/exceptions.h>

#include <util/io/socketsession.h>
#include <util/io/sockaddr_util.h>

#include <cassert>
#include <cstring>
#include <vector>

#include <sys/socket.h>
#include <stdint.h>

namespace isc {
namespace util {
namespace unittests {

/// \brief Mock socket session forwarder.
///
/// It emulates the behavior of SocketSessionForwarder without involving
/// network communication, and allowing the tester to customize the behavior
/// and to examine forwarded data afterwards.
class MockSocketSessionForwarder :
    public isc::util::io::BaseSocketSessionForwarder
{
public:
    MockSocketSessionForwarder() :
        is_connected_(false), connect_ok_(true), push_ok_(true),
        close_ok_(true),
        // These are not used until set, but we set them anyway here,
        // partly to silence cppcheck, and partly to be cleaner. Put some
        // invalid values in.
        pushed_sock_(-1), pushed_family_(-1), pushed_type_(-1),
        pushed_protocol_(-1)
    {}

    virtual void connectToReceiver() {
        if (!connect_ok_) {
            isc_throw(isc::util::io::SocketSessionError, "socket session "
                      "forwarding connection disabled for test");
        }
        if (is_connected_) {
            isc_throw(isc::util::io::SocketSessionError, "duplicate connect");
        }
        is_connected_ = true;
    }
    virtual void close() {
        if (!is_connected_) {
            isc_throw(isc::util::io::SocketSessionError, "duplicate close");
        }
        is_connected_ = false;
    }

    // Pushing a socket session.  It copies the given session data
    // so that the test code can check the values later via the getter
    // methods.  Complete deep copy will be created, so the caller doesn't
    // have to keep the parameters valid after the call to this method.
    virtual void push(int sock, int family, int type, int protocol,
                      const struct sockaddr& local_end,
                      const struct sockaddr& remote_end,
                      const void* data, size_t data_len)
    {
        if (!push_ok_) {
            isc_throw(isc::util::io::SocketSessionError,
                       "socket session forwarding is disabled for test");
        }
        if (!is_connected_) {
            isc_throw(isc::util::io::SocketSessionError,
                       "socket session is being pushed before connected");
        }

        // Copy parameters for later checks
        pushed_sock_ = sock;
        pushed_family_ = family;
        pushed_type_ = type;
        pushed_protocol_ = protocol;
        assert(io::internal::getSALength(local_end) <=
               sizeof(pushed_local_end_ss_));
        std::memcpy(&pushed_local_end_ss_, &local_end,
                    io::internal::getSALength(local_end));
        assert(io::internal::getSALength(remote_end) <=
               sizeof(pushed_remote_end_ss_));
        std::memcpy(&pushed_remote_end_ss_, &remote_end,
                    io::internal::getSALength(remote_end));
        pushed_data_.resize(data_len);
        std::memcpy(&pushed_data_[0], data, data_len);
    }

    // Allow the test code to check if the connection is established.
    bool isConnected() const { return (is_connected_); }

    // Allow the test code to customize the forwarder behavior wrt whether
    // a specific operation should succeed or fail.
    void disableConnect() { connect_ok_ = false; }
    void enableConnect() { connect_ok_ = true; }
    void disableClose() { close_ok_ = false; }
    void disablePush() { push_ok_ = false; }
    void enablePush() { push_ok_ = true; }

    // Read-only accessors to recorded parameters to the previous successful
    // call to push().  Return values are undefined if there has been no
    // successful call to push().
    // Note that we use convertSockAddr() to convert sockaddr_storage to
    // sockaddr.  It should be safe since we use the storage in its literal
    // sense; it was originally filled with the binary image of another
    // sockaddr structure, and we are going to return the image opaquely
    // as a sockaddr structure without touching the data.
    int getPushedSock() const { return (pushed_sock_); }
    int getPushedFamily() const { return (pushed_family_); }
    int getPushedType() const { return (pushed_type_); }
    int getPushedProtocol() const { return (pushed_protocol_); }
    const struct sockaddr& getPushedLocalend() const {
        return (*io::internal::convertSockAddr(&pushed_local_end_ss_));
    }
    const struct sockaddr& getPushedRemoteend() const {
        return (*io::internal::convertSockAddr(&pushed_remote_end_ss_));
    }
    const std::vector<uint8_t>& getPushedData() const {
        return (pushed_data_);
    }

private:
    bool is_connected_;
    bool connect_ok_;
    bool push_ok_;
    bool close_ok_;
    int pushed_sock_;
    int pushed_family_;
    int pushed_type_;
    int pushed_protocol_;
    struct sockaddr_storage pushed_local_end_ss_;
    struct sockaddr_storage pushed_remote_end_ss_;
    std::vector<uint8_t> pushed_data_;
};

} // end of unittests
} // end of util
} // end of isc
#endif  // UTIL_UNITTESTS_MOCKSOCKETSESSION_H

// Local Variables:
// mode: c++
// End:
