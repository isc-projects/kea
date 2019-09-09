// Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/signal_set.h>

#include <array>
#include <cerrno>
#include <list>

using namespace isc;
using namespace isc::util;

namespace {

/// @brief Fixed size storage for the codes of received signals.
///
/// It is initialized with all zeros, which means that no signals
/// have been received.
std::array<int, 1024> received_signals;

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

    // We haven't yet received this signal so we have to record its
    // reception. We're using the fixed size array to temporarily
    // store the received signal codes. We can't directly insert
    // the signal to the 'states' list because this would cause a
    // new allocation (malloc) which is not async-signal-safe.
    for (int i = 0; i < received_signals.size(); ++i) {
        // We have already recorded this signal.
        if (received_signals[i] == sig) {
            return;

        } else if (received_signals[i] == 0) {
            // We reached the end of the useful data in the storage.
            // Put the signal code into the storage.
            received_signals[i] = sig;
            break;
        }
    }
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

SignalSet::SignalSet(const int sig0)
    : blocked_(false) {
    // Copy static pointers to ensure they don't lose scope before we do.
    registered_signals_ = getRegisteredSignals();
    signal_states_ = getSignalStates();
    add(sig0);
}

SignalSet::SignalSet(const int sig0, const int sig1) :
    blocked_(false) {
    registered_signals_ = getRegisteredSignals();
    signal_states_ = getSignalStates();
    add(sig0);
    add(sig1);
}

SignalSet::SignalSet(const int sig0, const int sig1, const int sig2) :
    blocked_(false) {
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
        const char* errmsg = strerror(errno);
        erase(sig);
        isc_throw(SignalSetError, "failed to register a signal handler for"
                  " signal " << sig << ": " << errmsg);
    }
}

void
SignalSet::block() {
    maskSignals(SIG_BLOCK);
    blocked_ = true;
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
SignalSet::getNext() {
    // Since we're operating on the global values that the signal
    // handler has access to, we have to temporarily block the
    // signals to not interfere with unsafe operations performed
    // by this method. Remember if the signals were blocked or
    // not to be able to determine whether they should be unblocked
    // when the function returns.
    bool was_blocked = blocked_;
    if (!was_blocked) {
        block();
    }

    // We may have some signals received. We need to iterate over those
    // and move them to the signal states structure.
    for (int i = 0; i < received_signals.size(); ++i) {
        // If we hit the end of useful data, break.
        if (received_signals[i] == 0) {
            break;
        }
        // Check if such signal has been already recorded.
        if (std::find(signal_states_->begin(), signal_states_->end(), received_signals[i])
            == signal_states_->end()) {
            signal_states_->push_back(received_signals[i]);
        }
        // Set the current element to 0 to indicate the end of
        // the useful data and process the next element.
        received_signals[i] = 0;
    }

    int sig = -1;
    for (std::list<int>::iterator it = signal_states_->begin();
         it != signal_states_->end(); ++it) {
        if (local_signals_.find(*it) != local_signals_.end()) {
            sig = *it;
            break;
        }
    }

    // If we blocked signals here locally, we have to unblock them.
    if (!was_blocked) {
        unblock();
    }
    return (sig);
}

void
SignalSet::erase(const int sig) {
    if (local_signals_.find(sig) == local_signals_.end()) {
        isc_throw(SignalSetError, "failed to unregister signal " << sig
                  << " from a signal set: signal is not owned by the"
                  " signal set");
    }

    // Since we're operating on the global values that the signal
    // handler has access to, we have to temporarily block the
    // signals to not interfere with unsafe operations performed
    // by this method. Remember if the signals were blocked or
    // not to be able to determine whether they should be unblocked
    // when the function returns.
    bool was_blocked = blocked_;
    if (!was_blocked) {
        block();
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

    // If the signal is no longer supported by this signal set,
    // we have to unblock it, because other signal set instance
    // may be using it. We won't process it anyway after it is
    // removed from this set.
    unblock(sig);

    // Unblock all remaining signals if we have blocked them in
    // this function.
    if (!was_blocked) {
        unblock();
    }
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
SignalSet::maskSignals(const int mask, const int sig) const {
    sigset_t new_set;
    sigemptyset(&new_set);
    if (sig < 0) {
        for (std::set<int>::const_iterator it = registered_signals_->begin();
             it != registered_signals_->end(); ++it) {
            sigaddset(&new_set, *it);
        }
    } else {
        sigaddset(&new_set, sig);
    }
    pthread_sigmask(mask, &new_set, 0);
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
SignalSet::unblock(int sig) {
    // There are two cases supported by this function. One is to
    // unblock some specific signal. Another one is to unblock all
    // signals supported by this function. The maskSignals function
    // will deal wih this internally but we marked signals as unblocked
    // only if we unblocked all of them (sig is negative).
    maskSignals(SIG_UNBLOCK, sig);
    if (sig < 0) {
        blocked_ = false;
    }
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
