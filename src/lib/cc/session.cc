// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#include "config.h"

#include <stdint.h>

#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>

#ifdef HAVE_BOOSTLIB
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>
#endif

#include <exceptions/exceptions.h>

#include "data.h"
#include "session.h"

using namespace std;
using namespace isc::cc;
using namespace isc::data;

#ifdef HAVE_BOOSTLIB
// some of the boost::asio names conflict with socket API system calls
// (e.g. write(2)) so we don't import the entire boost::asio namespace.
using boost::asio::io_service;
using boost::asio::ip::tcp;
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace isc {
namespace cc {

class SessionImpl {
public:
    SessionImpl() : sequence_(-1) {}
    virtual ~SessionImpl() {}
    virtual void establish() = 0; 
    virtual int getSocket() = 0;
    virtual void disconnect() = 0;
    virtual void writeData(const void* data, size_t datalen) = 0;
    virtual size_t readDataLength() = 0;
    virtual void readData(void* data, size_t datalen) = 0;
    virtual void startRead(boost::function<void()> user_handler) = 0;

    int sequence_; // the next sequence number to use
    std::string lname_;
};

#ifdef HAVE_BOOSTLIB
class ASIOSession : public SessionImpl {
public:
    ASIOSession(io_service& io_service) :
        io_service_(io_service), socket_(io_service_), data_length_(0)
    {}
    virtual void establish();
    virtual void disconnect();
    virtual int getSocket() { return (socket_.native()); }
    virtual void writeData(const void* data, size_t datalen);
    virtual size_t readDataLength();
    virtual void readData(void* data, size_t datalen);
    virtual void startRead(boost::function<void()> user_handler);
private:
    void internalRead(const boost::system::error_code& error,
                      size_t bytes_transferred);

private:
    io_service& io_service_;
    tcp::socket socket_;
    uint32_t data_length_;
    boost::function<void()> user_handler_;
    boost::system::error_code error_;
};

void
ASIOSession::establish() {
    socket_.connect(tcp::endpoint(boost::asio::ip::address_v4::loopback(),
                                  9912), error_);
    if (error_) {
        isc_throw(SessionError, "Unable to connect to message queue");
    }
}

void
ASIOSession::disconnect() {
    socket_.close();
    data_length_ = 0;
}

void
ASIOSession::writeData(const void* data, size_t datalen) {
    try {
        boost::asio::write(socket_, boost::asio::buffer(data, datalen));
    } catch (const boost::system::system_error& boost_ex) {
        isc_throw(SessionError, "ASIO write failed: " << boost_ex.what());
    }
}

size_t
ASIOSession::readDataLength() {
    size_t ret_len = data_length_;
    
    if (ret_len == 0) {
        readData(&data_length_, sizeof(data_length_));
        if (data_length_ == 0) {
            isc_throw(SessionError, "ASIO read: data length is not ready");
        }
        ret_len = ntohl(data_length_);
    }

    data_length_ = 0;
    return (ret_len);
}

void
ASIOSession::readData(void* data, size_t datalen) {
    try {
        boost::asio::read(socket_, boost::asio::buffer(data, datalen));
    } catch (const boost::system::system_error& boost_ex) {
        // to hide boost specific exceptions, we catch them explicitly
        // and convert it to SessionError.
        isc_throw(SessionError, "ASIO read failed: " << boost_ex.what());
    }
}

void
ASIOSession::startRead(boost::function<void()> user_handler) {
    data_length_ = 0;
    user_handler_ = user_handler;
    async_read(socket_, boost::asio::buffer(&data_length_,
                                            sizeof(data_length_)),
               boost::bind(&ASIOSession::internalRead, this,
                           boost::asio::placeholders::error,
                           boost::asio::placeholders::bytes_transferred));
}

void
ASIOSession::internalRead(const boost::system::error_code& error,
                          size_t bytes_transferred)
{
    if (!error) {
        assert(bytes_transferred == sizeof(data_length_));
        data_length_ = ntohl(data_length_);
        if (data_length_ == 0) {
            isc_throw(SessionError, "Invalid message length (0)");
        }
        user_handler_();
    } else {
        isc_throw(SessionError, "asynchronous read failed");
    }
}
#endif

class SocketSession : public SessionImpl {
public:
    SocketSession() : sock_(-1) {}
    virtual ~SocketSession() { disconnect(); }
    virtual int getSocket() { return (sock_); }
    void establish();
    virtual void disconnect()
    {
        if (sock_ >= 0) {
            close(sock_);
        }
        sock_ = -1;
    }
    virtual void writeData(const void* data, size_t datalen);
    virtual void readData(void* data, size_t datalen);
    virtual size_t readDataLength();
    virtual void startRead(boost::function<void()> user_handler UNUSED_PARAM)
    {} // nothing to do for this class
private:
    int sock_;
};

namespace {                     // maybe unnecessary.
// This is a helper class to make the establish() method (below) exception-safe
// with the RAII approach.
class SessionHolder {
public:
    SessionHolder(SessionImpl* obj) : impl_obj_(obj) {}
    ~SessionHolder()
    {
        if (impl_obj_ != NULL) {
            impl_obj_->disconnect();
        }
    }
    void clear() { impl_obj_ = NULL; }
    SessionImpl* impl_obj_;
};
}

void
SocketSession::establish() {
    int s;
    struct sockaddr_in sin;

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s < 0) {
        isc_throw(SessionError, "socket() failed");
    }
    
    int port = atoi(getenv("ISC_MSGQ_PORT"));
    if (port == 0) {
        port = 9912;
    }

    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;

#ifdef HAVE_SIN_LEN
    sin.sin_len = sizeof(struct sockaddr_in);
#endif

    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        close(s);
        isc_throw(SessionError, "Unable to connect to message queue");
    }

    sock_ = s;
}

void
SocketSession::writeData(const void* data, const size_t datalen) {
    int cc = write(sock_, data, datalen);
    if (cc != datalen) {
        isc_throw(SessionError, "Write failed: expect " << datalen <<
                  ", actual " << cc);
    }
}

size_t
SocketSession::readDataLength() {
    uint32_t length;
    readData(&length, sizeof(length));
    return (ntohl(length));
}

void
SocketSession::readData(void* data, const size_t datalen) {
    int cc = read(sock_, data, datalen);
    if (cc != datalen) {
        isc_throw(SessionError, "Read failed: expect " << datalen <<
                  ", actual " << cc);
    }
}

Session::Session() : impl_(new SocketSession)
{}

#ifdef HAVE_BOOSTLIB
Session::Session(io_service& io_service) : impl_(new ASIOSession(io_service))
{}
#endif

Session::~Session() {
    delete impl_;
}

void
Session::disconnect() {
    impl_->disconnect();
}

int
Session::getSocket() const {
    return (impl_->getSocket());
}

void
Session::startRead(boost::function<void()> read_callback) {
    impl_->startRead(read_callback);
}

void
Session::establish() {
    impl_->establish();

    // once established, encapsulate the implementation object so that we
    // can safely release the internal resource when exception happens
    // below.
    SessionHolder session_holder(impl_);

    //
    // send a request for our local name, and wait for a response
    //
    ElementPtr get_lname_msg =
        Element::createFromString("{ \"type\": \"getlname\" }");
    sendmsg(get_lname_msg);

    ElementPtr routing, msg;
    recvmsg(routing, msg, false);

    impl_->lname_ = msg->get("lname")->stringValue();
    cout << "My local name is:  " << impl_->lname_ << endl;

    // At this point there's no risk of resource leak.
    session_holder.clear();
}

//
// Convert to wire format and send this on the TCP stream with its length prefix
//
void
Session::sendmsg(ElementPtr& msg) {
    std::string header_wire = msg->toWire();
    unsigned int length = 2 + header_wire.length();
    unsigned int length_net = htonl(length);
    unsigned short header_length = header_wire.length();
    unsigned short header_length_net = htons(header_length);

    impl_->writeData(&length_net, sizeof(length_net));
    impl_->writeData(&header_length_net, sizeof(header_length_net));
    impl_->writeData(header_wire.data(), header_length);
}

void
Session::sendmsg(ElementPtr& env, ElementPtr& msg) {
    std::string header_wire = env->toWire();
    std::string body_wire = msg->toWire();
    unsigned int length = 2 + header_wire.length() + body_wire.length();
    unsigned int length_net = htonl(length);
    unsigned short header_length = header_wire.length();
    unsigned short header_length_net = htons(header_length);

    impl_->writeData(&length_net, sizeof(length_net));
    impl_->writeData(&header_length_net, sizeof(header_length_net));
    impl_->writeData(header_wire.data(), header_length);
    impl_->writeData(body_wire.data(), body_wire.length());
}

bool
Session::recvmsg(ElementPtr& msg, bool nonblock UNUSED_PARAM) {
    size_t length = impl_->readDataLength();

    unsigned short header_length_net;
    impl_->readData(&header_length_net, sizeof(header_length_net));

    unsigned short header_length = ntohs(header_length_net);
    if (header_length != length) {
        isc_throw(SessionError, "Length parameters invalid: total=" << length
                  << ", header=" << header_length);
    }

    std::vector<char> buffer(length);
    impl_->readData(&buffer[0], length);

    std::string wire = std::string(&buffer[0], length);
    std::stringstream wire_stream;
    wire_stream << wire;

    msg = Element::fromWire(wire_stream, length);

    return (true);
    // XXXMLG handle non-block here, and return false for short reads
}

bool
Session::recvmsg(ElementPtr& env, ElementPtr& msg, bool nonblock UNUSED_PARAM) {
    size_t length = impl_->readDataLength();

    unsigned short header_length_net;
    impl_->readData(&header_length_net, sizeof(header_length_net));

    unsigned short header_length = ntohs(header_length_net);
    if (header_length > length || length < 2) {
        isc_throw(SessionError, "Length parameters invalid: total=" << length
                  << ", header=" << header_length);
    }

    // remove the header-length bytes from the total length
    length -= 2;
    std::vector<char> buffer(length);
    impl_->readData(&buffer[0], length);

    std::string header_wire = std::string(&buffer[0], header_length);
    std::string body_wire = std::string(&buffer[0] + header_length,
                                        length - header_length);
    std::stringstream header_wire_stream;
    header_wire_stream << header_wire;
    env = Element::fromWire(header_wire_stream, header_length);
    
    std::stringstream body_wire_stream;
    body_wire_stream << body_wire;
    msg = Element::fromWire(body_wire_stream, length - header_length);

    return (true);
    // XXXMLG handle non-block here, and return false for short reads
}

void
Session::subscribe(std::string group, std::string instance) {
    ElementPtr env = Element::create(std::map<std::string, ElementPtr>());

    env->set("type", Element::create("subscribe"));
    env->set("group", Element::create(group));
    env->set("instance", Element::create(instance));

    sendmsg(env);
}

void
Session::unsubscribe(std::string group, std::string instance) {
    ElementPtr env = Element::create(std::map<std::string, ElementPtr>());

    env->set("type", Element::create("unsubscribe"));
    env->set("group", Element::create(group));
    env->set("instance", Element::create(instance));

    sendmsg(env);
}

unsigned int
Session::group_sendmsg(ElementPtr msg, std::string group,
                       std::string instance, std::string to)
{
    ElementPtr env = Element::create(std::map<std::string, ElementPtr>());

    env->set("type", Element::create("send"));
    env->set("from", Element::create(impl_->lname_));
    env->set("to", Element::create(to));
    env->set("group", Element::create(group));
    env->set("instance", Element::create(instance));
    env->set("seq", Element::create(impl_->sequence_));
    //env->set("msg", Element::create(msg->toWire()));

    sendmsg(env, msg);

    return (++impl_->sequence_);
}

bool
Session::group_recvmsg(ElementPtr& envelope, ElementPtr& msg,
                       bool nonblock)
{
    return (recvmsg(envelope, msg, nonblock));
}

unsigned int
Session::reply(ElementPtr& envelope, ElementPtr& newmsg) {
    ElementPtr env = Element::create(std::map<std::string, ElementPtr>());

    env->set("type", Element::create("send"));
    env->set("from", Element::create(impl_->lname_));
    env->set("to", Element::create(envelope->get("from")->stringValue()));
    env->set("group", Element::create(envelope->get("group")->stringValue()));
    env->set("instance", Element::create(envelope->get("instance")->stringValue()));
    env->set("seq", Element::create(impl_->sequence_));
    env->set("reply", Element::create(envelope->get("seq")->intValue()));

    sendmsg(env, newmsg);

    return (++impl_->sequence_);
}
}
}
