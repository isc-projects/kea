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

#include <config.h>
#include <cc/session_config.h>

#include <stdint.h>

// XXX: there seems to be a strange dependency between ASIO and std library
// definitions.  On some platforms if we include std headers before ASIO
// headers unexpected behaviors will happen.
// A middle term solution is to generalize our local wrapper interface
// (currently only available for the auth server), where all such portability
// issues are hidden, and to have other modules use the wrapper.
#include <unistd.h>             // for some IPC/network system calls
#include <asio.hpp>
#include <asio/error_code.hpp>
#include <asio/deadline_timer.hpp>
#include <asio/system_error.hpp>

#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>

#include <sys/un.h>

#include <boost/bind.hpp>
#include <boost/optional.hpp>
#include <boost/function.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <exceptions/exceptions.h>

#include <cc/data.h>
#include <cc/session.h>

using namespace std;
using namespace isc::cc;
using namespace isc::data;

// some of the asio names conflict with socket API system calls
// (e.g. write(2)) so we don't import the entire asio namespace.
using asio::io_service;

namespace {
/// \brief Sets the given Optional 'result' to the given error code
/// Used as a callback for emulating sync reads with async calls
/// \param result Pointer to the optional to set
/// \param err The error code to set it to
void
setResult(boost::optional<asio::error_code>* result,
          const asio::error_code& err)
{
    result->reset(err);
}
}

namespace isc {
namespace cc {

class SessionImpl {
public:
    SessionImpl(io_service& io_service) :
        sequence_(-1), queue_(Element::createList()),
        io_service_(io_service), socket_(io_service_), data_length_(0),
        timeout_(MSGQ_DEFAULT_TIMEOUT)
    {}
    void establish(const char& socket_file);
    void disconnect();
    void writeData(const void* data, size_t datalen);
    size_t readDataLength();
    // Blocking read. Will throw a SessionTimeout if the timeout value
    // (in seconds) is thrown. If timeout is 0 it will block forever
    void readData(void* data, size_t datalen);
    void startRead(boost::function<void()> user_handler);
    void setTimeout(size_t seconds) { timeout_ = seconds; };
    size_t getTimeout() const { return timeout_; };

    long int sequence_; // the next sequence number to use
    std::string lname_;
    ElementPtr queue_;

private:
    void internalRead(const asio::error_code& error,
                      size_t bytes_transferred);

private:
    io_service& io_service_;
    asio::local::stream_protocol::socket socket_;
    uint32_t data_length_;
    boost::function<void()> user_handler_;
    asio::error_code error_;
    size_t timeout_;

    // By default, unless changed or disabled, blocking reads on
    // the msgq channel will time out after 4 seconds in this
    // implementation.
    // This number is chosen to be low enough so that whatever
    // component is blocking does not seem to be hanging, but
    // still gives enough time for other modules to respond if they
    // are busy. If this choice turns out to be a bad one, we can
    // change it later.
    static const size_t MSGQ_DEFAULT_TIMEOUT = 4000;
};

void
SessionImpl::establish(const char& socket_file) {
    try {
        socket_.connect(asio::local::stream_protocol::endpoint(&socket_file),
                        error_);
    } catch(const asio::system_error& se) {
        isc_throw(SessionError, se.what());
    }
    if (error_) {
        isc_throw(SessionError, "Unable to connect to message queue: " <<
                  error_.message());
    }
}

void
SessionImpl::disconnect() {
    socket_.close();
    data_length_ = 0;
}

void
SessionImpl::writeData(const void* data, size_t datalen) {
    try {
        asio::write(socket_, asio::buffer(data, datalen));
    } catch (const asio::system_error& asio_ex) {
        isc_throw(SessionError, "ASIO write failed: " << asio_ex.what());
    }
}

size_t
SessionImpl::readDataLength() {
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
SessionImpl::readData(void* data, size_t datalen) {
    boost::optional<asio::error_code> read_result;
    boost::optional<asio::error_code> timer_result;

    try {
        asio::async_read(socket_, asio::buffer(data, datalen),
                         boost::bind(&setResult, &read_result, _1));
        asio::deadline_timer timer(socket_.io_service());
    
        if (getTimeout() != 0) {
            timer.expires_from_now(boost::posix_time::milliseconds(getTimeout()));
            timer.async_wait(boost::bind(&setResult, &timer_result, _1));
        }

        // wait until either we have read the data we want, the
        // timer expires, or one of the two is triggered with an error.
        // When one of them has a result, cancel the other, and wait
        // until the cancel is processed before we continue
        while (!read_result && !timer_result) {
            socket_.io_service().run_one();

            // Don't cancel the timer if we haven't set it
            if (read_result && getTimeout() != 0) {
                timer.cancel();
                while (!timer_result) {
                    socket_.io_service().run_one();
                }
            } else if (timer_result) {
                socket_.cancel();
                while (!read_result) {
                    socket_.io_service().run_one();
                }
            }
        }

        // asio::error_code evaluates to false if there was no error
        if (*read_result) {
            if (*read_result == asio::error::operation_aborted) {
                isc_throw(SessionTimeout,
                          "Timeout while reading data from cc session");
            } else {
                isc_throw(SessionError,
                          "Error while reading data from cc session: " <<
                          read_result->message());
            }
        }
    } catch (const asio::system_error& asio_ex) {
        // to hide ASIO specific exceptions, we catch them explicitly
        // and convert it to SessionError.
        isc_throw(SessionError, "ASIO read failed: " << asio_ex.what());
    }
}

void
SessionImpl::startRead(boost::function<void()> user_handler) {
    data_length_ = 0;
    user_handler_ = user_handler;
    asio::async_read(socket_, asio::buffer(&data_length_,
                                           sizeof(data_length_)),
                     boost::bind(&SessionImpl::internalRead, this,
                                 asio::placeholders::error,
                                 asio::placeholders::bytes_transferred));
}

void
SessionImpl::internalRead(const asio::error_code& error,
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

Session::Session(io_service& io_service) : impl_(new SessionImpl(io_service))
{}

Session::~Session() {
    delete impl_;
}

void
Session::disconnect() {
    impl_->disconnect();
}

void
Session::startRead(boost::function<void()> read_callback) {
    impl_->startRead(read_callback);
}

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
Session::establish(const char* socket_file) {
    if (socket_file == NULL) {
        socket_file = getenv("BIND10_MSGQ_SOCKET_FILE");
    }
    if (socket_file == NULL) {
        socket_file = BIND10_MSGQ_SOCKET_FILE;
    }

    impl_->establish(*socket_file);

    // once established, encapsulate the implementation object so that we
    // can safely release the internal resource when exception happens
    // below.
    SessionHolder session_holder(impl_);

    //
    // send a request for our local name, and wait for a response
    //
    ConstElementPtr get_lname_msg =
        Element::fromJSON("{ \"type\": \"getlname\" }");
    sendmsg(get_lname_msg);

    ConstElementPtr routing, msg;
    recvmsg(routing, msg, false);

    impl_->lname_ = msg->get("lname")->stringValue();

    // At this point there's no risk of resource leak.
    session_holder.clear();
}

//
// Convert to wire format and send this via the stream socket with its length
// prefix.
//
void
Session::sendmsg(ConstElementPtr msg) {
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
Session::sendmsg(ConstElementPtr env, ConstElementPtr msg) {
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
Session::recvmsg(ConstElementPtr& msg, bool nonblock, int seq) {
    ConstElementPtr l_env;
    return (recvmsg(l_env, msg, nonblock, seq));
}

bool
Session::recvmsg(ConstElementPtr& env, ConstElementPtr& msg,
                 bool nonblock, int seq)
{
    size_t length = impl_->readDataLength();
    if (hasQueuedMsgs()) {
        ConstElementPtr q_el;
        for (int i = 0; i < impl_->queue_->size(); i++) {
            q_el = impl_->queue_->get(i);
            if (( seq == -1 &&
                  !q_el->get(0)->contains("reply")
                ) || (
                  q_el->get(0)->contains("reply") &&
                  q_el->get(0)->get("reply")->intValue() == seq
                )
               ) {
                   env = q_el->get(0);
                   msg = q_el->get(1);
                   impl_->queue_->remove(i);
                   return (true);
            }
        }
    }
    
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
    ConstElementPtr l_env =
        Element::fromWire(header_wire_stream, header_length);
    
    std::stringstream body_wire_stream;
    body_wire_stream << body_wire;
    ConstElementPtr l_msg =
        Element::fromWire(body_wire_stream, length - header_length);
    if ((seq == -1 &&
         !l_env->contains("reply")
        ) || (
         l_env->contains("reply") &&
         l_env->get("reply")->intValue() == seq
        )
       ) {
        env = l_env;
        msg = l_msg;
        return (true);
    } else {
        ElementPtr q_el = Element::createList();
        q_el->add(l_env);
        q_el->add(l_msg);
        impl_->queue_->add(q_el);
        return (recvmsg(env, msg, nonblock, seq));
    }
    // XXXMLG handle non-block here, and return false for short reads
}

void
Session::subscribe(std::string group, std::string instance) {
    ElementPtr env = Element::createMap();

    env->set("type", Element::create("subscribe"));
    env->set("group", Element::create(group));
    env->set("instance", Element::create(instance));

    sendmsg(env);
}

void
Session::unsubscribe(std::string group, std::string instance) {
    ElementPtr env = Element::createMap();

    env->set("type", Element::create("unsubscribe"));
    env->set("group", Element::create(group));
    env->set("instance", Element::create(instance));

    sendmsg(env);
}

int
Session::group_sendmsg(ConstElementPtr msg, std::string group,
                       std::string instance, std::string to)
{
    ElementPtr env = Element::createMap();
    long int nseq = ++impl_->sequence_;
    
    env->set("type", Element::create("send"));
    env->set("from", Element::create(impl_->lname_));
    env->set("to", Element::create(to));
    env->set("group", Element::create(group));
    env->set("instance", Element::create(instance));
    env->set("seq", Element::create(nseq));
    //env->set("msg", Element::create(msg->toWire()));

    sendmsg(env, msg);
    return (nseq);
}

bool
Session::group_recvmsg(ConstElementPtr& envelope, ConstElementPtr& msg,
                       bool nonblock, int seq)
{
    return (recvmsg(envelope, msg, nonblock, seq));
}

int
Session::reply(ConstElementPtr envelope, ConstElementPtr newmsg) {
    ElementPtr env = Element::createMap();
    long int nseq = ++impl_->sequence_;
    
    env->set("type", Element::create("send"));
    env->set("from", Element::create(impl_->lname_));
    env->set("to", Element::create(envelope->get("from")->stringValue()));
    env->set("group", Element::create(envelope->get("group")->stringValue()));
    env->set("instance", Element::create(envelope->get("instance")->stringValue()));
    env->set("seq", Element::create(nseq));
    env->set("reply", Element::create(envelope->get("seq")->intValue()));

    sendmsg(env, newmsg);

    return (nseq);
}

bool
Session::hasQueuedMsgs() const {
    return (impl_->queue_->size() > 0);
}

void
Session::setTimeout(size_t milliseconds) {
    impl_->setTimeout(milliseconds);
}

size_t
Session::getTimeout() const {
    return (impl_->getTimeout());
}
}
}
