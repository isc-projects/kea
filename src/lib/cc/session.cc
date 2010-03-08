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

#include "data.h"
#include "session.h"

#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;
using namespace isc::cc;
using namespace isc::data;

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace isc {
namespace cc {

class SessionImpl {
public:
    SessionImpl() : sock_(-1), sequence_(-1) {}
    int sock_;
    int sequence_; // the next sequence number to use
    std::string lname_;
};

Session::Session() : impl_(new SessionImpl)
{}

Session::~Session() {
    delete impl_;
}

void
Session::disconnect() {
    close(impl_->sock_);
    impl_->sock_ = -1;
}

int
Session::getSocket() const {
     return (impl_->sock_);
}

namespace {
// This is a helper class to make the establish() method (below) exception-safe
// with the RAII approach.
class SocketHolder {
public:
    SocketHolder(SessionImpl* obj, int fd) : impl_obj_(obj), fd_(fd)
    {
        impl_obj_->sock_ = fd;
    }
    ~SocketHolder()
    {
        if (fd_ >= 0) {
            close(fd_);
            impl_obj_->sock_ = -1;
        }
    }
    void clear() { fd_ = -1; }
    SessionImpl* impl_obj_;
    int fd_;
};
}

void
Session::establish() {
    int s, ret;
    struct sockaddr_in sin;

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s < 0) {
        throw SessionError("socket() failed");
    }

    SocketHolder socket_holder(impl_, s);

    sin.sin_family = AF_INET;
    sin.sin_port = htons(9912);
    sin.sin_addr.s_addr = INADDR_ANY;

#ifdef HAVE_SIN_LEN
    sin.sin_len = sizeof(struct sockaddr_in);
#endif

    ret = connect(s, (struct sockaddr *)&sin, sizeof(sin));
    if (ret < 0) {
        throw SessionError("Unable to connect to message queue");
    }

    //
    // send a request for our local name, and wait for a response
    //
    std::string get_lname_str = "{ \"type\": \"getlname\" }";
    std::stringstream get_lname_stream;
    get_lname_stream.str(get_lname_str);
    ElementPtr get_lname_msg = Element::createFromString(get_lname_stream);
    sendmsg(get_lname_msg);

    ElementPtr routing, msg;
    recvmsg(routing, msg, false);

    impl_->lname_ = msg->get("lname")->stringValue();
    cout << "My local name is:  " << impl_->lname_ << endl;

    socket_holder.clear();
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
    unsigned int ret;

    assert(impl_->sock_ != -1);

    ret = write(impl_->sock_, &length_net, 4);
    if (ret != 4)
        throw SessionError("Short write");

    ret = write(impl_->sock_, &header_length_net, 2);
    if (ret != 2)
        throw SessionError("Short write");

    ret = write(impl_->sock_, header_wire.c_str(), header_length);
    if (ret != header_length) {
        throw SessionError("Short write");
    }
}

void
Session::sendmsg(ElementPtr& env, ElementPtr& msg)
{
    std::string header_wire = env->toWire();
    std::string body_wire = msg->toWire();
    unsigned int length = 2 + header_wire.length() + body_wire.length();
    unsigned int length_net = htonl(length);
    unsigned short header_length = header_wire.length();
    unsigned short header_length_net = htons(header_length);
    unsigned int ret;

    ret = write(impl_->sock_, &length_net, 4);
    if (ret != 4)
        throw SessionError("Short write");

    ret = write(impl_->sock_, &header_length_net, 2);
    if (ret != 2)
        throw SessionError("Short write");

    ret = write(impl_->sock_, header_wire.c_str(), header_length);
    if (ret != header_length) {
        throw SessionError("Short write");
    }
    ret = write(impl_->sock_, body_wire.c_str(), body_wire.length());
    if (ret != body_wire.length()) {
        throw SessionError("Short write");
    }
}

bool
Session::recvmsg(ElementPtr& msg, bool nonblock)
{
    unsigned int length_net;
    unsigned short header_length_net;
    unsigned int ret;

    ret = read(impl_->sock_, &length_net, 4);
    if (ret != 4)
        throw SessionError("Short read");

    ret = read(impl_->sock_, &header_length_net, 2);
    if (ret != 2)
        throw SessionError("Short read");

    unsigned int length = ntohl(length_net) - 2;
    unsigned short header_length = ntohs(header_length_net);
    if (header_length != length) {
        throw SessionError("Received non-empty body where only a header expected");
    }

    std::vector<char> buffer(length);
    ret = read(impl_->sock_, &buffer[0], length);
    if (ret != length) {
        throw SessionError("Short read");
    }

    std::string wire = std::string(&buffer[0], length);

    std::stringstream wire_stream;
    wire_stream << wire;

    msg = Element::fromWire(wire_stream, length);

    return (true);
    // XXXMLG handle non-block here, and return false for short reads
}

bool
Session::recvmsg(ElementPtr& env, ElementPtr& msg, bool nonblock)
{
    unsigned int length_net;
    unsigned short header_length_net;
    unsigned int ret;

    ret = read(impl_->sock_, &length_net, 4);
    if (ret != 4)
        throw SessionError("Short read");

    ret = read(impl_->sock_, &header_length_net, 2);
    if (ret != 2)
        throw SessionError("Short read");

    unsigned int length = ntohl(length_net);
    unsigned short header_length = ntohs(header_length_net);
    if (header_length > length)
        throw SessionError("Bad header length");

    // remove the header-length bytes from the total length
    length -= 2;
    std::vector<char> buffer(length);
    ret = read(impl_->sock_, &buffer[0], length);
    if (ret != length) {
        throw SessionError("Short read");
    }

    std::string header_wire = std::string(&buffer[0], header_length);
    std::string body_wire = std::string(&buffer[0] + header_length, length - header_length);

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
Session::subscribe(std::string group, std::string instance)
{
    ElementPtr env = Element::create(std::map<std::string, ElementPtr>());

    env->set("type", Element::create("subscribe"));
    env->set("group", Element::create(group));
    env->set("instance", Element::create(instance));

    sendmsg(env);
}

void
Session::unsubscribe(std::string group, std::string instance)
{
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

    return (impl_->sequence_++);
}

bool
Session::group_recvmsg(ElementPtr& envelope, ElementPtr& msg, bool nonblock)
{
    bool got_message = recvmsg(envelope, msg, nonblock);
    if (!got_message) {
        return false;
    }

    return (true);
}

unsigned int
Session::reply(ElementPtr& envelope, ElementPtr& newmsg)
{
    ElementPtr env = Element::create(std::map<std::string, ElementPtr>());

    env->set("type", Element::create("send"));
    env->set("from", Element::create(impl_->lname_));
    env->set("to", Element::create(envelope->get("from")->stringValue()));
    env->set("group", Element::create(envelope->get("group")->stringValue()));
    env->set("instance", Element::create(envelope->get("instance")->stringValue()));
    env->set("seq", Element::create(impl_->sequence_));
    env->set("reply", Element::create(envelope->get("seq")->intValue()));

    sendmsg(env, newmsg);

    return (impl_->sequence_++);
}
}
}
