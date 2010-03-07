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
#include <vector>
#include <map>

#include "data.h"

namespace isc {
    namespace cc {
        class SessionError : public std::exception {
        public:
            SessionError(std::string m = "CC Session Error") : msg(m) {}
            ~SessionError() throw() {}
            const char* what() const throw() { return msg.c_str(); }
        private:
            std::string msg;
        };

        class Session {
        private:
            int sock;
            int sequence; // the next sequence number to use

        public:
            std::string lname;

            Session();

            // XXX: quick hack to allow the user to watch the socket directly.
            int getSocket() const { return (sock); }

            void establish();
            void disconnect();
            void sendmsg(isc::data::ElementPtr& msg);
            void sendmsg(isc::data::ElementPtr& env, isc::data::ElementPtr& msg);
            bool recvmsg(isc::data::ElementPtr& msg,
                         bool nonblock = true);
            bool recvmsg(isc::data::ElementPtr& env,
                         isc::data::ElementPtr& msg,
                         bool nonblock = true);
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
                               bool nonblock = true);
            unsigned int reply(isc::data::ElementPtr& envelope,
                               isc::data::ElementPtr& newmsg);
        };
    } // namespace cc
} // namespace isc

#endif // _ISC_SESSION_H

// Local Variables:
// mode: c++
// End:
