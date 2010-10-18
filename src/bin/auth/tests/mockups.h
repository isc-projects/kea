// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <config.h>

#include <cc/data.h>
#include <cc/session.h>

#include <xfr/xfrout_client.h>

// A minimal mock configuration session.  Most the methods are
// stubbed out, except for a very basic group_sendmsg() and
// group_recvmsg().  hasQueuedMessages() always returns false.
class MockSession : public isc::cc::AbstractSession {
public:
    MockSession() :
        // by default we return a simple "success" message.
        msg_(Element::fromJSON("{\"result\": [0, \"SUCCESS\"]}")),
        send_ok_(true), receive_ok_(true)
    {}


    virtual void establish(const char* socket_file UNUSED_PARAM) {}
    virtual void disconnect() {}

    virtual int group_sendmsg(isc::data::ConstElementPtr msg, std::string group,
                              std::string instance UNUSED_PARAM,
                              std::string to UNUSED_PARAM)
    {
        if (!send_ok_) {
            isc_throw(isc::cc::SessionError,
                      "mock session send is disabled for test");
        }

        sent_msg = msg;
        msg_destination = group;
        return (0);
    }

    virtual bool group_recvmsg(isc::data::ConstElementPtr& env UNUSED_PARAM,
                               isc::data::ConstElementPtr& msg UNUSED_PARAM,
                               bool nonblock UNUSED_PARAM,
                               int seq UNUSED_PARAM)
    {
        if (!receive_ok_) {
            isc_throw(isc::cc::SessionError,
                      "mock session receive is disabled for test");
        }

        msg = msg_;
        return (true);
    }

    virtual void subscribe(std::string group UNUSED_PARAM,
                           std::string instance UNUSED_PARAM) {}
    virtual void unsubscribe(std::string group UNUSED_PARAM,
                             std::string instance UNUSED_PARAM) {}

    virtual void startRead(boost::function<void()> callback UNUSED_PARAM) {}

    virtual int reply(isc::data::ConstElementPtr envelope UNUSED_PARAM,
                      isc::data::ConstElementPtr newmsg UNUSED_PARAM) {
        return (-1);
    }

    virtual bool hasQueuedMsgs() const {
        return (false);
    }

    virtual void setTimeout(size_t timeout UNUSED_PARAM) {};
    virtual size_t getTimeout() const { return 0; };

    void setMessage(isc::data::ConstElementPtr msg) { msg_ = msg; }
    void disableSend() { send_ok_ = false; }
    void disableReceive() { receive_ok_ = false; }

    isc::data::ConstElementPtr sent_msg;
    std::string msg_destination;
private:
    isc::data::ConstElementPtr msg_;
    bool send_ok_;
    bool receive_ok_;
};

// A nonoperative DNSServer object to be used in calls to processMessage().
class MockServer : public asiolink::DNSServer {
public:
    MockServer() : done_(false) {}
    void operator()(asio::error_code ec UNUSED_PARAM,
                    size_t length UNUSED_PARAM)
    {}
    virtual void resume(const bool done) { done_ = done; }
    virtual bool hasAnswer() { return (done_); }
    virtual int value() { return (0); }
private:
    bool done_;
};

// Mock Xfrout client
class MockXfroutClient : public isc::xfr::AbstractXfroutClient {
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

    virtual int sendXfroutRequestInfo(int tcp_sock UNUSED_PARAM,
                                      const void* msg_data UNUSED_PARAM,
                                      uint16_t msg_len UNUSED_PARAM)
    {
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
};

