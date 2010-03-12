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

#include "config.h"

#include <stdint.h>

#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>

#ifdef HAVE_BOOSTLIB
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>
#endif

#include <boost/foreach.hpp>

#include <exceptions/exceptions.h>

#include <cc/data.h>
#include "fake_session.h"

using namespace std;
using namespace isc::cc;
using namespace isc::data;

#ifdef HAVE_BOOSTLIB
// some of the boost::asio names conflict with socket API system calls
// (e.g. write(2)) so we don't import the entire boost::asio namespace.
using boost::asio::io_service;
using boost::asio::ip::tcp;
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


// ok i want these in cc/data 
static bool
listContains(ElementPtr list, ElementPtr el)
{
    if (!list) {
        return false;
    }
    BOOST_FOREACH(ElementPtr l_el, list->listValue()) {
        if (l_el == el) {
            return true;
        }
    }
    return false;
}

static void
listRemove(ElementPtr list, ElementPtr el) {
    int i = -1;
    BOOST_FOREACH(ElementPtr s_el, list->listValue()) {
        if (el == s_el) {
            i = 0;
        }
    }
    if (i >= 0) {
        list->remove(i);
    }
}
// endwant

ElementPtr
getFirstMessage(std::string& group, std::string& to)
{
    ElementPtr el;
    if (msg_queue && msg_queue->size() > 0) {
        el = msg_queue->get(0);
        msg_queue->remove(0);
        group = el->get(0)->stringValue();
        to = el->get(1)->stringValue();
        return el->get(2);
    } else {
        group = "";
        to = "";
        return ElementPtr();
    }
}

void
addMessage(ElementPtr msg, const std::string& group, const std::string& to)
{
    ElementPtr m_el = Element::createFromString("[]");
    m_el->add(Element::create(group));
    m_el->add(Element::create(to));
    m_el->add(msg);
    if (!msg_queue) {
        msg_queue = Element::createFromString("[]");
    }
    msg_queue->add(m_el);
}

bool
haveSubscription(const std::string& group, const std::string& instance)
{
    if (!subscriptions) {
        return false;
    }
    ElementPtr s1 = Element::createFromString("[]");
    ElementPtr s2 = Element::createFromString("[]");
    s1->add(Element::create(group));
    s1->add(Element::create(instance));
    s2->add(Element::create(group));
    s2->add(Element::create("*"));
    bool result = (listContains(subscriptions, s1) || listContains(subscriptions, s2));
    return result;
}

bool
haveSubscription(const ElementPtr group, const ElementPtr instance)
{
    return haveSubscription(group->stringValue(), instance->stringValue());
}

namespace isc {
namespace cc {

Session::Session()
{
}

#ifdef HAVE_BOOSTLIB
Session::Session(io_service& io_service UNUSED_PARAM)
{
}
#endif

Session::~Session() {
}

void
Session::disconnect() {
}

int
Session::getSocket() const {
    return 1;
}

void
Session::startRead(boost::function<void()> read_callback UNUSED_PARAM) {
}

void
Session::establish() {
}

//
// Convert to wire format and send this on the TCP stream with its length prefix
//
void
Session::sendmsg(ElementPtr& msg) {
    //cout << "[XX] client sends message: " << msg << endl;
    // err, to where?
    addMessage(msg, "*", "*");
}

void
Session::sendmsg(ElementPtr& env, ElementPtr& msg) {
    //cout << "[XX] client sends message: " << msg << endl;
    //cout << "[XX] env: " << env << endl;
    addMessage(msg, env->get("group")->stringValue(), env->get("to")->stringValue());
}

bool
Session::recvmsg(ElementPtr& msg, bool nonblock UNUSED_PARAM) {
    //cout << "[XX] client asks for message " << endl;
    if (initial_messages &&
        initial_messages->getType() == Element::list &&
        initial_messages->size() > 0) {
        msg = initial_messages->get(0);
        initial_messages->remove(0);
    } else {
        msg = ElementPtr();
    }
    return (true);
}

bool
Session::recvmsg(ElementPtr& env, ElementPtr& msg, bool nonblock UNUSED_PARAM) {
    //cout << "[XX] client asks for message and env" << endl;
    env = ElementPtr();
    if (initial_messages &&
        initial_messages->getType() == Element::list &&
        initial_messages->size() > 0) {
        // do we need initial message to have env[group] and [to] too?
        msg = initial_messages->get(0);
        initial_messages->remove(0);
        return true;
    } else if (msg_queue) {
        BOOST_FOREACH(ElementPtr c_m, msg_queue->listValue()) {
            ElementPtr to_remove = ElementPtr();
            if (haveSubscription(c_m->get(0), c_m->get(1))) {
                env = Element::createFromString("{}");
                env->set("group", c_m->get(0));
                env->set("to", c_m->get(1));
                msg = c_m->get(2);
                to_remove = c_m;
            }
            if (to_remove) {
                listRemove(msg_queue, to_remove);
                return true;
            }
        }
    }
    msg = ElementPtr();
    env = ElementPtr();
    return false;
}

void
Session::subscribe(std::string group, std::string instance) {
    //cout << "[XX] client subscribes to " << group << " . " << instance << endl;
    ElementPtr s_el = Element::createFromString("[]");
    s_el->add(Element::create(group));
    s_el->add(Element::create(instance));
    if (!subscriptions) {
        subscriptions = Element::createFromString("[]");
    }
    subscriptions->add(s_el);
}

void
Session::unsubscribe(std::string group, std::string instance) {
    //cout << "[XX] client unsubscribes from " << group << " . " << instance << endl;
    ElementPtr s_el = Element::createFromString("[]");
    s_el->add(Element::create(group));
    s_el->add(Element::create(instance));
    if (!subscriptions) {
        return;
    }
    listRemove(subscriptions, s_el);
}

unsigned int
Session::group_sendmsg(ElementPtr msg, std::string group,
                       std::string to, std::string instance UNUSED_PARAM)
{
    //cout << "[XX] client sends message: " << msg << endl;
    //cout << "[XX] to: " << group << " . " << instance << "." << to << endl;
    addMessage(msg, group, to);
    return 1;
}

bool
Session::group_recvmsg(ElementPtr& envelope, ElementPtr& msg,
                       bool nonblock)
{
    return (recvmsg(envelope, msg, nonblock));
}

unsigned int
Session::reply(ElementPtr& envelope, ElementPtr& newmsg) {
    //cout << "[XX] client sends reply: " << newmsg << endl;
    //cout << "[XX] env: " << envelope << endl;
    addMessage(newmsg, envelope->get("group")->stringValue(), envelope->get("to")->stringValue());
    return 1;
}

}
}
