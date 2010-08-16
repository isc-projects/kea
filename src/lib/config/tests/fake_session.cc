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

// $Id: session.cc 1250 2010-03-09 22:52:15Z jinmei $

#include <config.h>

#include <stdint.h>

#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>

#include <boost/foreach.hpp>

#include <exceptions/exceptions.h>

#include <cc/data.h>
#include <config/tests/fake_session.h>

using namespace std;
using namespace isc::cc;
using namespace isc::data;

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// ok i want these in cc/data 
bool
listContains(ConstElementPtr list, ConstElementPtr el) {
    if (!list) {
        return (false);
    }
    BOOST_FOREACH(ConstElementPtr l_el, list->listValue()) {
        if (*l_el == *el) {
            return (true);
        }
    }
    return (false);
}

void
listRemove(ElementPtr list, ConstElementPtr el) {
    int i = -1;
    BOOST_FOREACH(ConstElementPtr s_el, list->listValue()) {
        if (*el == *s_el) {
            i = 0;
        }
        i++;
    }
    if (i >= 0) {
        list->remove(i);
    }
}
// endwant

namespace isc {
namespace cc {

FakeSession::FakeSession(isc::data::ElementPtr initial_messages,
                         isc::data::ElementPtr subscriptions,
                         isc::data::ElementPtr msg_queue) :
    messages_(initial_messages),
    subscriptions_(subscriptions),
    msg_queue_(msg_queue)
{
}

FakeSession::~FakeSession() {
}

void
FakeSession::disconnect() {
}

void
FakeSession::startRead(boost::function<void()> read_callback UNUSED_PARAM) {
}

void
FakeSession::establish(const char* socket_file) {
}

bool
FakeSession::recvmsg(ConstElementPtr& msg, bool nonblock UNUSED_PARAM,
                     int seq UNUSED_PARAM)
{
    //cout << "[XX] client asks for message " << endl;
    if (messages_ &&
        messages_->getType() == Element::list &&
        messages_->size() > 0) {
        msg = messages_->get(0);
        messages_->remove(0);
    } else {
        msg = ElementPtr();
    }
    return (true);
}

bool
FakeSession::recvmsg(ConstElementPtr& env, ConstElementPtr& msg,
                     bool nonblock UNUSED_PARAM,
                     int seq UNUSED_PARAM)
{
    //cout << "[XX] client asks for message and env" << endl;
    env = ElementPtr();
    if (messages_ &&
        messages_->getType() == Element::list &&
        messages_->size() > 0) {
        // do we need initial message to have env[group] and [to] too?
        msg = messages_->get(0);
        messages_->remove(0);
        return (true);
    } else if (msg_queue_) {
        BOOST_FOREACH(ConstElementPtr c_m, msg_queue_->listValue()) {
            ConstElementPtr to_remove = ElementPtr();
            if (haveSubscription(c_m->get(0), c_m->get(1))) {
                ElementPtr new_env = Element::createMap();
                new_env->set("group", c_m->get(0));
                new_env->set("to", c_m->get(1));
                env = new_env;
                msg = c_m->get(2);
                to_remove = c_m;
            }
            if (to_remove) {
                listRemove(msg_queue_, to_remove);
                return (true);
            }
        }
    }
    msg = ElementPtr();
    env = ElementPtr();
    return (false);
}

void
FakeSession::subscribe(std::string group, std::string instance) {
    //cout << "[XX] client subscribes to " << group << " . " << instance << endl;
    ElementPtr s_el = Element::createList();
    s_el->add(Element::create(group));
    s_el->add(Element::create(instance));
    if (!subscriptions_) {
        subscriptions_ = Element::createList();
    }
    subscriptions_->add(s_el);
}

void
FakeSession::unsubscribe(std::string group, std::string instance) {
    //cout << "[XX] client unsubscribes from " << group << " . " << instance << endl;
    ElementPtr s_el = Element::createList();
    s_el->add(Element::create(group));
    s_el->add(Element::create(instance));
    if (!subscriptions_) {
        return;
    }
    listRemove(subscriptions_, s_el);
}

int
FakeSession::group_sendmsg(ConstElementPtr msg, std::string group,
                           std::string to, std::string instance UNUSED_PARAM)
{
    //cout << "[XX] client sends message: " << msg << endl;
    //cout << "[XX] to: " << group << " . " << instance << "." << to << endl;
    addMessage(msg, group, to);
    return (1);
}

bool
FakeSession::group_recvmsg(ConstElementPtr& envelope, ConstElementPtr& msg,
                           bool nonblock, int seq)
{
    return (recvmsg(envelope, msg, nonblock, seq));
}

int
FakeSession::reply(ConstElementPtr envelope, ConstElementPtr newmsg) {
    //cout << "[XX] client sends reply: " << newmsg << endl;
    //cout << "[XX] env: " << envelope << endl;
    addMessage(newmsg, envelope->get("group")->stringValue(),
               envelope->get("to")->stringValue());
    return (1);
}

bool
FakeSession::hasQueuedMsgs() const {
    return (false);
}

ConstElementPtr
FakeSession::getFirstMessage(std::string& group, std::string& to) const {
    ConstElementPtr el;
    if (msg_queue_ && msg_queue_->size() > 0) {
        el = msg_queue_->get(0);
        msg_queue_->remove(0);
        group = el->get(0)->stringValue();
        to = el->get(1)->stringValue();
        return (el->get(2));
    } else {
        group = "";
        to = "";
        return (ElementPtr());
    }
}

void
FakeSession::addMessage(ConstElementPtr msg, const std::string& group,
                        const std::string& to)
{
    ElementPtr m_el = Element::createList();
    m_el->add(Element::create(group));
    m_el->add(Element::create(to));
    m_el->add(msg);
    if (!msg_queue_) {
        msg_queue_ = Element::createList();
    }
    msg_queue_->add(m_el);
}

bool
FakeSession::haveSubscription(const std::string& group,
                              const std::string& instance)
{
    if (!subscriptions_) {
        return (false);
    }
    ElementPtr s1 = Element::createList();
    ElementPtr s2 = Element::createList();
    s1->add(Element::create(group));
    s1->add(Element::create(instance));
    s2->add(Element::create(group));
    s2->add(Element::create("*"));
    bool result = (listContains(subscriptions_, s1) ||
                   listContains(subscriptions_, s2));
    return (result);
}

bool
FakeSession::haveSubscription(ConstElementPtr group, ConstElementPtr instance)
{
    return (haveSubscription(group->stringValue(), instance->stringValue()));
}

}
}
