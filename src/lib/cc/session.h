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

#ifndef _ISC_SESSION_H
#define _ISC_SESSION_H 1

#include <string>

#include <boost/function.hpp>

#include <exceptions/exceptions.h>

#include "data.h"
#include "session_config.h"

namespace asio {
class io_service;
}

namespace isc {
    namespace cc {
        class SessionImpl;

        class SessionError : public isc::Exception {
        public:
            SessionError(const char* file, size_t line, const char* what) :
                isc::Exception(file, line, what) {}
        };

        class AbstractSession {
        private:
            AbstractSession(const AbstractSession& source);
            AbstractSession& operator=(const AbstractSession& source);
        protected:
            AbstractSession() {}
        public:
            virtual ~AbstractSession() {}
            //@}
            virtual void establish(const char* socket_file) = 0;
            virtual void disconnect() = 0;
            virtual int group_sendmsg(isc::data::ElementPtr msg,
                                      std::string group,
                                      std::string instance = "*",
                                      std::string to = "*") = 0;
            virtual bool group_recvmsg(isc::data::ElementPtr& envelope,
                                       isc::data::ElementPtr& msg,
                                       bool nonblock = true,
                                       int seq = -1) = 0;
            virtual void subscribe(std::string group,
                                   std::string instance = "*") = 0;
            virtual void unsubscribe(std::string group,
                             std::string instance = "*") = 0;
            virtual void startRead(boost::function<void()> read_callback) = 0;
            virtual int reply(isc::data::ElementPtr& envelope,
                               isc::data::ElementPtr& newmsg) = 0;
            virtual bool hasQueuedMsgs() = 0;
        };

    class Session : public AbstractSession {
        private:
            SessionImpl* impl_;

        private:
            Session(const Session& source);
            Session& operator=(const Session& source);

        public:
            Session(asio::io_service& ioservice);
            ~Session();

            virtual void startRead(boost::function<void()> read_callback);

            void establish(const char* socket_file = NULL);
            void disconnect();
            void sendmsg(isc::data::ElementPtr& msg);
            void sendmsg(isc::data::ElementPtr& env,
                         isc::data::ElementPtr& msg);
            bool recvmsg(isc::data::ElementPtr& msg,
                         bool nonblock = true,
                         int seq = -1);
            bool recvmsg(isc::data::ElementPtr& env,
                         isc::data::ElementPtr& msg,
                         bool nonblock = true,
                         int seq = -1);
            virtual void subscribe(std::string group,
                                   std::string instance = "*");
            virtual void unsubscribe(std::string group,
                             std::string instance = "*");
            int group_sendmsg(isc::data::ElementPtr msg,
                                       std::string group,
                                       std::string instance = "*",
                                       std::string to = "*");
            bool group_recvmsg(isc::data::ElementPtr& envelope,
                               isc::data::ElementPtr& msg,
                               bool nonblock = true,
                               int seq = -1);
            virtual int reply(isc::data::ElementPtr& envelope,
                              isc::data::ElementPtr& newmsg);
            virtual bool hasQueuedMsgs();
        };
    } // namespace cc
} // namespace isc

#endif // _ISC_SESSION_H

// Local Variables:
// mode: c++
// End:
