// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef ISC_TESTUTILS_MOCKUPS_H
#define ISC_TESTUTILS_MOCKUPS_H 1

#include <exceptions/exceptions.h>

#include <cc/data.h>

#include <asiodns/asiodns.h>

#include <utility>
#include <vector>

namespace isc {
namespace testutils {

// This mock object does nothing except for recording passed parameters
// to addServerXXX methods so the test code subsequently checks the parameters.
class MockDNSService : public isc::asiodns::DNSServiceBase {
public:
    MockDNSService() : tcp_recv_timeout_(0) {}

    // A helper tuple of parameters passed to addServerUDPFromFD().
    struct UDPFdParams {
        int fd;
        int af;
        ServerFlag options;
    };

    virtual void addServerTCPFromFD(int fd, int af) {
        tcp_fd_params_.push_back(std::pair<int, int>(fd, af));
    }
    virtual void addServerUDPFromFD(int fd, int af, ServerFlag options) {
        UDPFdParams params = { fd, af, options };
        udp_fd_params_.push_back(params);
    }
    virtual void clearServers() {}

    virtual asiolink::IOService& getIOService() {
        isc_throw(isc::Unexpected,
                  "MockDNSService::getIOService() shouldn't be called");
    }

    // These two allow the tests to check how the servers have been created
    // through this object.
    const std::vector<std::pair<int, int> >& getTCPFdParams() const {
        return (tcp_fd_params_);
    }
    const std::vector<UDPFdParams>& getUDPFdParams() const {
        return (udp_fd_params_);
    }

    virtual void setTCPRecvTimeout(size_t timeout) {
        tcp_recv_timeout_ = timeout;
    }

    size_t getTCPRecvTimeout() {
        return tcp_recv_timeout_;
    }

private:
    std::vector<std::pair<int, int> > tcp_fd_params_;
    std::vector<UDPFdParams> udp_fd_params_;
    size_t tcp_recv_timeout_;
};

// A nonoperative DNSServer object to be used in calls to processMessage().
class MockServer : public isc::asiodns::DNSServer {
public:
    MockServer() : done_(false) {}
    void operator()(asio::error_code, size_t) {}
    virtual void resume(const bool done) { done_ = done; }
    virtual bool hasAnswer() { return (done_); }
    virtual int value() { return (0); }
private:
    bool done_;
};

// Commenting out this class as it is not used anyware. The removal of this class
// allows for removal of the lib/xfr.

// Mock Xfrout client
/*class MockXfroutClient : public isc::xfr::AbstractXfroutClient {
public:
    MockXfroutClient() :
        is_connected_(false), connect_ok_(true), send_ok_(true),
        disconnect_ok_(true)
    {}

    virtual void connect() {
        if (!connect_ok_) {
            isc_throw(isc::xfr::XfroutError,
                      "xfrout connection disabled for test");
        }
        is_connected_ = true;
    }

    virtual void disconnect() {
        if (!disconnect_ok_) {
            isc_throw(isc::xfr::XfroutError,
                      "closing xfrout connection is disabled for test");
        }
        is_connected_ = false;
    }

    virtual int sendXfroutRequestInfo(int, const void*, uint16_t) {
        if (!send_ok_) {
            isc_throw(isc::xfr::XfroutError,
                       "xfrout connection send is disabled for test");
        }
        return (0);
    }

    bool isConnected() const { return (is_connected_); }
    void disableConnect() { connect_ok_ = false; }
    void disableDisconnect() { disconnect_ok_ = false; }
    void enableDisconnect() { disconnect_ok_ = true; }
    void disableSend() { send_ok_ = false; }
private:
    bool is_connected_;
    bool connect_ok_;
    bool send_ok_;
    bool disconnect_ok_;
    }; */

} // end of testutils
} // end of isc
#endif  // ISC_TESTUTILS_MOCKUPS_H

// Local Variables:
// mode: c++
// End:
