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

#ifndef _ISC_FAKESESSION_H
#define _ISC_FAKESESSION_H 1

#include <string>

#include <boost/function.hpp>

#include <exceptions/exceptions.h>

#include <cc/data.h>
#include <cc/session.h>

namespace isc {
namespace cc {
class FakeSession : public AbstractSession {
private:
    FakeSession(const Session& source);
    FakeSession& operator=(const Session& source);

public:
    // if initial_messages contains a list of messages,
    // these are sent when recv_msg or group_recvmsg is called
    // instead of whatever is in the msg queue.
    // The test can also add data to a copy of the message later to tweak
    // the group_recvmsg() behavior.  See getMessages() below.
    FakeSession(isc::data::ElementPtr initial_messages,
                isc::data::ElementPtr subscriptions,
                isc::data::ElementPtr msg_queue);
    virtual ~FakeSession();

    virtual void startRead(boost::function<void()> read_callback);

    virtual void establish(const char* socket_file = NULL);
    virtual void disconnect();
    virtual void subscribe(std::string group,
                           std::string instance = "*");
    virtual void unsubscribe(std::string group,
                             std::string instance = "*");
    virtual int group_sendmsg(isc::data::ConstElementPtr msg,
                              std::string group,
                              std::string instance = "*",
                              std::string to = "*");
    virtual bool group_recvmsg(isc::data::ConstElementPtr& envelope,
                               isc::data::ConstElementPtr& msg,
                               bool nonblock = true,
                               int seq = -1);
    virtual int reply(isc::data::ConstElementPtr envelope,
                      isc::data::ConstElementPtr newmsg);
    virtual bool hasQueuedMsgs() const;
    virtual void setTimeout(size_t milliseconds) {}
    virtual size_t getTimeout() const { return (0); }
    isc::data::ConstElementPtr getFirstMessage(std::string& group,
                                               std::string& to) const;
    void addMessage(isc::data::ConstElementPtr, const std::string& group,
                    const std::string& to);
    bool haveSubscription(const std::string& group,
                          const std::string& instance);
    bool haveSubscription(const isc::data::ConstElementPtr group,
                          const isc::data::ConstElementPtr instance);

    // For the convenience of tests, we share these internal members
    // with the tester.  The test code may insert update and check,
    // before (via the constructor parameters), during and after the actual
    // session object was created/destroyed.
    isc::data::ElementPtr getMessages() { return (messages_); }
    isc::data::ElementPtr getMsgQueue() { return (msg_queue_); }

private:
    bool recvmsg(isc::data::ConstElementPtr& msg,
                 bool nonblock = true, int seq = -1);
    bool recvmsg(isc::data::ConstElementPtr& env,
                 isc::data::ConstElementPtr& msg,
                 bool nonblock = true, int seq = -1);

    const isc::data::ElementPtr messages_;
    isc::data::ElementPtr subscriptions_;
    isc::data::ElementPtr msg_queue_;
};
} // namespace cc
} // namespace isc

#endif // _ISC_FAKESESSION_H

// Local Variables:
// mode: c++
// End:
