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

// $Id: session.h 1250 2010-03-09 22:52:15Z jinmei $

#ifndef _ISC_SESSION_H
#define _ISC_SESSION_H 1

#include <string>

#include <boost/function.hpp>

#include <exceptions/exceptions.h>

#include <cc/data.h>

namespace boost {
namespace asio {
class io_service;
}
}

// global variables so tests can insert
// update and check, before, during and after
// the actual session object was created/destroyed

// if initial_messages contains a list of messages,
// these are sent when recv_msg or group_recvmsg is called
// instead of whatever is in the msg queue
extern isc::data::ElementPtr initial_messages;
extern isc::data::ElementPtr subscriptions;
extern isc::data::ElementPtr msg_queue;

bool haveSubscription(const std::string& group, const std::string& instance);
bool haveSubscription(const isc::data::ElementPtr group, const isc::data::ElementPtr instance);
isc::data::ElementPtr getFirstMessage(std::string& group, std::string& to);
void addMessage(isc::data::ElementPtr, const std::string& group, const std::string& to);

namespace isc {
    namespace cc {

        class SessionError : public isc::Exception {
        public:
            SessionError(const char* file, size_t line, const char* what) :
                isc::Exception(file, line, what) {}
        };

        class Session {
        private:
            Session(const Session& source);
            Session& operator=(const Session& source);

        public:
            // public so tests can inspect them
        
            Session();
            Session(boost::asio::io_service& ioservice);
            ~Session();

            // XXX: quick hack to allow the user to watch the socket directly.
            int getSocket() const;

            void startRead(boost::function<void()> read_callback);

            void establish(const char* socket_file = NULL);
            bool connect();
            void disconnect();
            void sendmsg(isc::data::ElementPtr& msg);
            void sendmsg(isc::data::ElementPtr& env,
                         isc::data::ElementPtr& msg);
            bool recvmsg(isc::data::ElementPtr& msg,
                         bool nonblock = true, int seq = -1);
            bool recvmsg(isc::data::ElementPtr& env,
                         isc::data::ElementPtr& msg,
                         bool nonblock = true, int seq = -1);
            void subscribe(std::string group,
                           std::string instance = "*");
            void unsubscribe(std::string group,
                             std::string instance = "*");
            unsigned int group_sendmsg(isc::data::ElementPtr msg,
                                       std::string group,
                                       std::string instance = "*",
                                       std::string to = "*");
            bool group_recvmsg(isc::data::ElementPtr& envelope,
                               isc::data::ElementPtr& msg,
                               bool nonblock = true,
                               int seq = -1);
            unsigned int reply(isc::data::ElementPtr& envelope,
                               isc::data::ElementPtr& newmsg);
            bool hasQueuedMsgs();

        };
    } // namespace cc
} // namespace isc

#endif // _ISC_SESSION_H

// Local Variables:
// mode: c++
// End:
