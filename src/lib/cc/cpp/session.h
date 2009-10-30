#ifndef _ISC_SESSION_H
#define _ISC_SESSION_H 1

#include <string>
#include <vector>
#include <map>

#include <iostream>

#include "data.h"

namespace ISC {
    namespace CC {
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

            void establish();
            void disconnect();
            void sendmsg(ISC::Data::ElementPtr& msg);
            bool recvmsg(ISC::Data::ElementPtr& msg,
                         bool nonblock = true);
            void subscribe(std::string group,
                           std::string instance = "*",
                           std::string subtype = "normal");
            void unsubscribe(std::string group,
                             std::string instance = "*");
            unsigned int group_sendmsg(ISC::Data::ElementPtr& msg,
                                       std::string group,
                                       std::string instance = "*",
                                       std::string to = "*");
            bool group_recvmsg(ISC::Data::ElementPtr& envelope,
                               ISC::Data::ElementPtr& msg,
                               bool nonblock = true);
            unsigned int reply(ISC::Data::ElementPtr& envelope,
                               ISC::Data::ElementPtr& newmsg);
        };
    } // namespace CC
} // namespace ISC

#endif // _ISC_SESSION_H
