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

#include <util/signal_set.h>

#include <cerrno>
#include <list>

using namespace isc;
using namespace isc::util;

namespace {

/// @brief Returns a pointer to the global set of registered signals.
///
/// Multiple instances of @c SignalSet may use this pointer to access
/// and update the set.
///
/// @return Pointer to the global set of registered signals. This pointer
/// is always initialized and points to a valid object.
std::set<int>* getRegisteredSignals() {
    static std::set<int> registered_signals;
    return (&registered_signals);
}

/// @brief Returns a pointer to static collection of signals received.
///
/// Multiple instances of @c SignalSet may use this pointer to access
/// and update the queue of signals received.
///
/// @return Static collection of signals received. This pointer is always
/// initialized and points to a valid object.
std::list<int>* getSignalStates() {
    static std::list<int> states;
    return (&states);
}

/// @brief Internal signal handler for @c isc::util::io::SignalSet class.
///
/// This signal handler adds a signal number for which it is being
/// invoked to the queue of received signals. It prevents adding duplicated
/// signals. All duplicated signals are dropped. This prevents hammering
/// a process to invoke handlers (e.g. DHCP server reconfiguration), when
/// many the same signals are received one after another.
///
/// @param sig Signal number.
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

SignalSet::~SignalSet() {
    // Set default signal handlers.
    try {
        clear();
    } catch (...) {
        // Not a good thing to throw from a destructor. in fact this should
        // not throw an exception because we just unregister the signals
        // that we have previously registered. So the signal codes are fine.
    }
}

void
SignalSet::add(const int sig) {
    insert(sig);
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = internalHandler;
    sigfillset(&sa.sa_mask);
    if (sigaction(sig, &sa, 0) < 0) {
        erase(sig);
        isc_throw(SignalSetError, "failed to register a signal handler for"
                  " signal " << sig << ": " << strerror(errno));
    }
}

void
SignalSet::clear() {
    // Iterate over a copy of the registered signal set because the
    // remove function is erasing the elements and we don't want to
    // erase the elements we are iterating over. This would cause
    // a segfault.
    std::set<int> all_signals = local_signals_;
    for (std::set<int>::const_iterator it = all_signals.begin();
         it != all_signals.end(); ++it) {
        remove(*it);
    }
}

int
SignalSet::getNext() const {
    std::list<int>* states = getSignalStates();
    for (std::list<int>::iterator it = states->begin();
         it != states->end(); ++it) {
        if (local_signals_.find(*it) != local_signals_.end()) {
            return (*it);
        }
    }
    return (-1);
}

void
SignalSet::erase(const int sig) {
    if (local_signals_.find(sig) == local_signals_.end()) {
        isc_throw(SignalSetError, "failed to unregister signal " << sig
                  << " from a signal set: signal is not owned by the"
                  " signal set");
    }
    // Remove globally registered signal.
    getRegisteredSignals()->erase(sig);
    // Remove unhandled signals from the queue.
    for (std::list<int>::iterator it = getSignalStates()->begin();
         it != getSignalStates()->end(); ++it) {
        if (*it == sig) {
            it = getSignalStates()->erase(it);
        }
    }
    // Remove locally registered signal.
    local_signals_.erase(sig);
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
SignalSet::insert(const int sig) {
    std::set<int>* global_signals = getRegisteredSignals();
    if ((global_signals->find(sig) != global_signals->end()) ||
        (local_signals_.find(sig) != local_signals_.end())) {
        isc_throw(SignalSetError, "attempt to register a duplicate signal "
                  << sig);
    }
    global_signals->insert(sig);
    local_signals_.insert(sig);
}

void
SignalSet::maskSignals(const int mask) const {
    sigset_t new_set;
    for (std::set<int>::const_iterator it = getRegisteredSignals()->begin();
         it != getRegisteredSignals()->end(); ++it) {
        sigaddset(&new_set, *it);
    }
    sigprocmask(mask, &new_set, 0);
}

void
SignalSet::popNext() {
    std::list<int>* states = getSignalStates();
    for (std::list<int>::iterator it = states->begin();
         it != states->end(); ++it) {
        if (local_signals_.find(*it) != local_signals_.end()) {
            states->erase(it);
            return;
        }
    }
}

void
SignalSet::remove(const int sig) {
    // Unregister only if we own this signal.
    if (local_signals_.find(sig) != local_signals_.end()) {
        struct sigaction sa;
        memset(&sa, 0, sizeof(sa));
        sa.sa_handler = SIG_DFL;
        sigfillset(&sa.sa_mask);
        if (sigaction(sig, &sa, 0) < 0) {
            isc_throw(SignalSetError, "unable to restore original signal"
                      " handler for signal: " << sig);
        }
        erase(sig);
    } else {
        isc_throw(SignalSetError, "failed to unregister signal " << sig
                  << ": this signal is not owned by the signal set");
    }
}

} // end of isc::util
} // end of isc
