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

namespace boost {
namespace asio {
class io_service;
}
}

namespace isc {
    namespace cc {
        class SessionImpl;

        class SessionError : public isc::Exception {
        public:
            SessionError(const char* file, size_t line, const char* what) :
                isc::Exception(file, line, what) {}
        };

        class Session {
        private:
            SessionImpl* impl_;

        private:
            Session(const Session& source);
            Session& operator=(const Session& source);

        public:
            Session();
            Session(boost::asio::io_service& ioservice);
            ~Session();

            // XXX: quick hack to allow the user to watch the socket directly.
            int getSocket() const;

            void startRead(boost::function<void()> read_callback);

            void establish();
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
            void subscribe(std::string group,
                           std::string instance = "*");
            void unsubscribe(std::string group,
                             std::string instance = "*");
            int group_sendmsg(isc::data::ElementPtr msg,
                                       std::string group,
                                       std::string instance = "*",
                                       std::string to = "*");
            bool group_recvmsg(isc::data::ElementPtr& envelope,
                               isc::data::ElementPtr& msg,
                               bool nonblock = true,
                               int seq = -1);
            int reply(isc::data::ElementPtr& envelope,
                               isc::data::ElementPtr& newmsg);
            bool hasQueuedMsgs();
        };
    } // namespace cc
} // namespace isc

#endif // _ISC_SESSION_H

// Local Variables:
// mode: c++
// End:
