// Copyright (C) 2009, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef ISC_SESSION_H
#define ISC_SESSION_H 1

#include <cc/api.h>
#include <cc/data.h>
#include <cc/session_config.h>
#include <cc/proto_defs.h>

#include <exceptions/exceptions.h>

#include <string>

#include <boost/function.hpp>

namespace asio {
class io_service;
}

namespace isc {
    namespace cc {
        class SessionImpl;

        class KEA_CC_API SessionError : public isc::Exception {
        public:
            SessionError(const char* file, size_t line, const char* what) :
                isc::Exception(file, line, what) {}
        };

        /// \brief A standard Exception class that is thrown when a
        /// blocking readData call does not read the given number of
        /// bytes before the timeout expires
        class KEA_CC_API SessionTimeout : public isc::Exception {
        public:
            SessionTimeout(const char* file, size_t line, const char* what) :
                isc::Exception(file, line, what) {}
        };

        /// \brief The AbstractSession class is an abstract base class that
        /// defines the interfaces of Session.
        /// The intended primary usage of abstraction is to allow tests for the
        /// user class of Session without requiring actual communication
        /// channels.
        /// For simplicity we only define the methods that are necessary for
        /// existing test cases that use this base class.  Eventually we'll
        /// probably have to extend them.
        class KEA_CC_API AbstractSession {
            ///
            /// \name Constructors, Assignment Operator and Destructor.
            ///
            /// Note: The copy constructor and the assignment operator are
            /// intentionally defined as private to make it explicit that
            /// this is a pure base class.
            //@{
        private:
            AbstractSession(const AbstractSession& source);
            AbstractSession& operator=(const AbstractSession& source);
        protected:
            /// \brief The default constructor.
            ///
            /// This is intentionally defined as \c protected as this base
            /// class should never be instantiated (except as part of a
            /// derived class).
            AbstractSession() {}
        public:
            /// \brief The destructor.
            virtual ~AbstractSession() {}
            //@}
            virtual void establish(const char* socket_file) = 0;
            virtual void disconnect() = 0;
            virtual int group_sendmsg(isc::data::ConstElementPtr msg,
                                      std::string group,
                                      std::string instance =
                                          CC_INSTANCE_WILDCARD,
                                      std::string to = CC_TO_WILDCARD,
                                      bool want_answer = false) = 0;
            virtual bool group_recvmsg(isc::data::ConstElementPtr& envelope,
                                       isc::data::ConstElementPtr& msg,
                                       bool nonblock = true,
                                       int seq = -1) = 0;
            virtual void subscribe(std::string group,
                                   std::string instance = "*") = 0;
            virtual void unsubscribe(std::string group,
                             std::string instance = "*") = 0;
            virtual void startRead(boost::function<void()> read_callback) = 0;
            virtual int reply(isc::data::ConstElementPtr envelope,
                               isc::data::ConstElementPtr newmsg) = 0;
            virtual bool hasQueuedMsgs() const = 0;

            /// \brief Sets the default timeout for blocking reads
            ///        in this session to the given number of milliseconds
            /// \param milliseconds the timeout for blocking reads in
            ///        milliseconds; if this is set to 0, reads will block
            ///        forever.
            virtual void setTimeout(size_t milliseconds) = 0;

            /// \brief Returns the current timeout for blocking reads
            /// \return The timeout (in milliseconds)
            virtual size_t getTimeout() const = 0;
        };

    class KEA_CC_API Session : public AbstractSession {
        private:
            SessionImpl* impl_;

        private:
            Session(const Session& source);
            Session& operator=(const Session& source);

        public:
            Session(asio::io_service& ioservice);
            virtual ~Session();

            virtual void startRead(boost::function<void()> read_callback);

            virtual void establish(const char* socket_file = NULL);
            virtual void disconnect();
            virtual void subscribe(std::string group,
                                   std::string instance = "*");
            virtual void unsubscribe(std::string group,
                             std::string instance = "*");

            /// \brief Send a message to a group.
            ///
            /// \todo Can someone explain how the group, instance and to work?
            ///     What is the desired semantics here?
            /// \param msg The message to send.
            /// \param group Part of addressing.
            /// \param instance Part of addressing.
            /// \param to Part of addressing.
            /// \param want_answer Require an answer? If it is true and there's
            ///     no recipient, the message queue answers by an error
            ///     instead.
            /// \return The squence number of the message sent. It can be used
            ///     to wait for an answer by group_recvmsg.
            virtual int group_sendmsg(isc::data::ConstElementPtr msg,
                                      std::string group,
                                      std::string instance = "*",
                                      std::string to = "*",
                                      bool want_answer = false);

            virtual bool group_recvmsg(isc::data::ConstElementPtr& envelope,
                                       isc::data::ConstElementPtr& msg,
                                       bool nonblock = true,
                                       int seq = -1);
            virtual int reply(isc::data::ConstElementPtr envelope,
                              isc::data::ConstElementPtr newmsg);
            virtual bool hasQueuedMsgs() const;
            virtual void setTimeout(size_t milliseconds);
            virtual size_t getTimeout() const;

            /// @brief returns socket descriptor from underlying socket connection
            ///
            /// @return socket descriptor used for session connection
            virtual int getSocketDesc() const;
    private:
            // The following two methods are virtual to allow tests steal and
            // replace them. It is not expected to be specialized by a derived
            // class. Actually, it is not expected to inherit from this class
            // to begin with.
            virtual void sendmsg(isc::data::ConstElementPtr header);
            virtual void sendmsg(isc::data::ConstElementPtr header,
                                 isc::data::ConstElementPtr payload);

            bool recvmsg(isc::data::ConstElementPtr& msg,
                         bool nonblock = true,
                         int seq = -1);
            bool recvmsg(isc::data::ConstElementPtr& env,
                         isc::data::ConstElementPtr& msg,
                         bool nonblock = true,
                         int seq = -1);
        };
    } // namespace cc
} // namespace isc

#endif // ISC_SESSION_H

// Local Variables:
// mode: c++
// End:
