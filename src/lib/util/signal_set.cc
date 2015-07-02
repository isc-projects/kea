// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
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
/// and update the set. Note we use a smart pointer so callers can ensure
/// the static object doesn't go out of scope before they are done with it
/// during process exit.
///
/// @return Pointer to the global set of registered signals. This pointer
/// is always initialized and points to a valid object.
SigIntSetPtr getRegisteredSignals() {
    static SigIntSetPtr registered_signals(new SigIntSet());
    return (registered_signals);
}

/// @brief Returns a pointer to static collection of signals received.
///
/// Multiple instances of @c SignalSet may use this pointer to access
/// and update the queue of signals received.  Note we use a smart pointer
/// so callers can ensure the static object doesn't go out of scope before
/// they are done with it during process exit.
///
/// @return Static collection of signals received. This pointer is always
/// initialized and points to a valid object.
SigIntListPtr getSignalStates() {
    static SigIntListPtr signal_states(new SigIntList());
    return (signal_states);
}

/// @brief Internal signal handler for @c isc::util::SignalSet class.
///
/// This handler catches all registered signals. When a signal arrives it
/// passes the signal to invokeOnReceiptHandler for "on-receipt" processing.
/// If this processing returns true if exists without further action,
/// otherwise it adds the signal number to the queue of received signals.
/// It prevents adding duplicated signals. All duplicated signals are dropped.
/// This prevents hammering a process to invoke handlers (e.g. DHCP server
/// reconfiguration), when many of the same signals are received one after
/// another.
///
/// @param sig Signal number.
void internalHandler(int sig) {
    if (SignalSet::invokeOnReceiptHandler(sig)) {
        // Signal has been handled by the on-receipt handler.
        return;
    }

    // Signal is using post-receipt handling, see if we've
    // already received it.
    SigIntListPtr states = getSignalStates();
    for (std::list<int>::const_iterator it = states->begin();
        it != states->end(); ++it) {
            if (sig == *it) {
                return;
        }
    }

    // First occurrence, so save it.
    states->push_back(sig);
}

/// @brief Optional handler to execute at the time of signal receipt
BoolSignalHandler onreceipt_handler_ = BoolSignalHandler();

}; // end anon namespace

namespace isc {
namespace util {

bool
SignalSet::invokeOnReceiptHandler(int sig) {
    if (!onreceipt_handler_) {
        return (false);
    }

    // First we set the signal to SIG_IGN.  This causes any repeat occurrences
    // to be discarded, not deferred as they would be if blocked.   Note that
    // we save the current sig action so we can restore it later.
    struct sigaction sa;
    struct sigaction prev_sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = SIG_IGN;
    if (sigaction(sig, &sa, &prev_sa) < 0) {
        // Highly unlikely we can get here.
        const char* errmsg = strerror(errno);
        isc_throw(SignalSetError, "failed to set SIG_IGN for signal "
                  << sig << ": " << errmsg);
    }

    // Call the registered handler.
    bool signal_processed = false;
    try {
        signal_processed = onreceipt_handler_(sig);
    } catch (const std::exception& ex) {
        // Restore the handler.  We might fail to restore it, but we likely
        // have bigger issues anyway: for that reason, the return value is
        // ignored.  To avoid complaints from static code checkers that notice
        // that the return values from other calls to sigaction() have been
        // used, the call to sigaction is explicitly cast to void to indicate
        // that the return value is intentionally being ignored.
        static_cast<void>(sigaction(sig, &prev_sa, 0));
        isc_throw(SignalSetError, "onreceipt_handler failed for signal "
                  << sig << ": " << ex.what());
    }

    // Restore the sig action to re-enable handling this signal.
    if (sigaction(sig, &prev_sa, 0) < 0) {
        // Highly unlikely we can get here.
        const char* errmsg = strerror(errno);
        isc_throw(SignalSetError, "failed to restore handler for signal "
                  << sig << ": " << errmsg);
    }

    return (signal_processed);
}

SignalSet::SignalSet(const int sig0) {
    // Copy static pointers to ensure they don't lose scope before we do.
    registered_signals_ = getRegisteredSignals();
    signal_states_ = getSignalStates();
    add(sig0);
}

SignalSet::SignalSet(const int sig0, const int sig1) {
    registered_signals_ = getRegisteredSignals();
    signal_states_ = getSignalStates();
    add(sig0);
    add(sig1);
}

SignalSet::SignalSet(const int sig0, const int sig1, const int sig2) {
    registered_signals_ = getRegisteredSignals();
    signal_states_ = getSignalStates();
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
SignalSet::block() const {
    maskSignals(SIG_BLOCK);
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
    for (std::list<int>::iterator it = signal_states_->begin();
         it != signal_states_->end(); ++it) {
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
    registered_signals_->erase(sig);
    // Remove unhandled signals from the queue.
    for (std::list<int>::iterator it = signal_states_->begin();
         it != signal_states_->end(); ++it) {
        if (*it == sig) {
            it = signal_states_->erase(it);
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
    if ((registered_signals_->find(sig) != registered_signals_->end()) ||
        (local_signals_.find(sig) != local_signals_.end())) {
        isc_throw(SignalSetError, "attempt to register a duplicate signal "
                  << sig);
    }
    registered_signals_->insert(sig);
    local_signals_.insert(sig);
}

void
SignalSet::maskSignals(const int mask) const {
    sigset_t new_set;
    sigemptyset(&new_set);
    for (std::set<int>::const_iterator it = registered_signals_->begin();
         it != registered_signals_->end(); ++it) {
        sigaddset(&new_set, *it);
    }
    sigprocmask(mask, &new_set, 0);
}

void
SignalSet::popNext() {
    for (std::list<int>::iterator it = signal_states_->begin();
         it != signal_states_->end(); ++it) {
        if (local_signals_.find(*it) != local_signals_.end()) {
            signal_states_->erase(it);
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

void
SignalSet::unblock() const {
    maskSignals(SIG_UNBLOCK);
}


void
SignalSet::setOnReceiptHandler(BoolSignalHandler handler) {
    onreceipt_handler_ = handler;
}

void
SignalSet::clearOnReceiptHandler() {
    onreceipt_handler_ = BoolSignalHandler();
}

} // end of isc::util
} // end of isc
