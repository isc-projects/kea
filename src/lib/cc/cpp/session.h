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
