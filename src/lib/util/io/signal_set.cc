// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <util/io/signal_set.h>

#include <list>

using namespace isc;
using namespace isc::util::io;

namespace {

std::list<int>* getSignalStates() {
    static std::list<int> states;
    return (&states);
}

void internalHandler(int sig) {
    std::list<int>* states = getSignalStates();
    for (std::list<int>::const_iterator it = states->begin();
         it != states->end(); ++it) {
        if (sig == *it) {
            return;
        }
    }
    states->push_back(sig);
}

}

namespace isc {
namespace util {
namespace io {

SignalSet::SignalSet(const int sig0) {
    add(sig0);
}

SignalSet::SignalSet(const int sig0, const int sig1) {
    add(sig0);
    add(sig1);
}

SignalSet::SignalSet(const int sig0, const int sig1, const int sig2) {
    add(sig0);
    add(sig1);
    add(sig2);
}

void
SignalSet::add(const int sig) {
    std::pair<Pool::iterator, bool> ret = registered_signals_.insert(sig);
    if (!ret.second) {
        isc_throw(SignalSetError, "attempt to register a duplicate signal "
                  << sig);
    }
    struct sigaction sa;
    sa.sa_handler = internalHandler;
    if (sigaction(sig, &sa, 0) < 0) {
        registered_signals_.erase(sig);
        isc_throw(SignalSetError, "failed to register a signal handler for"
                  " signal " << sig << ": " << strerror(errno));
    }
}

void
SignalSet::clear() {
    Pool all_signals = registered_signals_;
    for (Pool::const_iterator it = all_signals.begin();
         it != all_signals.end(); ++it) {
        remove(*it);
    }
}

int
SignalSet::getNext() const {
    std::list<int>* states = getSignalStates();
    if (states->empty()) {
        return (-1);
    }
    return (*states->begin());
}

void
SignalSet::handleNext(SignalHandler signal_handler) {
    block();
    int signum = getNext();
    if (signum >= 0) {
        popNext();
        try {
            signal_handler(signum);
        } catch (...) {
            unblock();
            throw;
        }
    }
    unblock();
}

void
SignalSet::maskSignals(const int mask) const {
    sigset_t new_set;
    for (Pool::const_iterator it = registered_signals_.begin();
         it != registered_signals_.end(); ++it) {
        sigaddset(&new_set, *it);
    }
    sigprocmask(mask, &new_set, 0);
}

void
SignalSet::popNext() const {
    std::list<int>* states = getSignalStates();
    if (!states->empty()) {
        states->pop_front();
    }
}

void
SignalSet::remove(const int sig) {
    if (registered_signals_.find(sig) != registered_signals_.end()) {
        struct sigaction sa;
        sa.sa_handler = SIG_DFL;
        if (sigaction(sig, &sa, 0) < 0) {
            isc_throw(SignalSetError, "unable to restore original signal"
                      " handler for signal: " << sig);
        }
        registered_signals_.erase(sig);
    }
}

} // end of isc::util::io
} // end of isc::util
} // end of isc
