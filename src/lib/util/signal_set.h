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

#ifndef SIGNAL_SET_H
#define SIGNAL_SET_H

#include <exceptions/exceptions.h>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <set>
#include <list>
#include <pthread.h>
#include <signal.h>

namespace isc {
namespace util {

/// @brief Exception thrown when the @c isc::util::SignalSet class
/// experiences an error.
class SignalSetError : public Exception {
public:
    SignalSetError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief Defines a set of integer signal identifiers: SIGHUP, SIGTERM...
typedef std::set<int> SigIntSet;
/// @brief Pointer to a set of signal identifiers
typedef boost::shared_ptr<SigIntSet> SigIntSetPtr;

/// @brief Defines a list of integer signal identifiers: SIGHUP, SIGTERM...
typedef std::list<int> SigIntList;
/// @brief Pointer to a list of signal identifiers
typedef boost::shared_ptr<SigIntList> SigIntListPtr;


/// @brief Forward declaration to the @c isc::util::SignalSet.
class SignalSet;
/// @brief Pointer to the @c isc::util::SignalSet.
typedef boost::shared_ptr<SignalSet> SignalSetPtr;
/// @brief Pointer to the signal handling function.
typedef boost::function<void(int signum)> SignalHandler;

/// @brief Pointer to a signal handling function which returns bool result.
///
/// The handler is expected to return true if the signal it was given has
/// been processed (i.e. should not be recorded for deferred processing) or
/// false in which case it will be recorded.
typedef boost::function<bool(int signum)> BoolSignalHandler;

/// @brief Represents a collection of signals handled in a customized way.
///
/// Kea processes must handle selected signals in a specialized way. For
/// example: SIGINT and SIGTERM must perform a graceful shut down of the
/// server. The SIGHUP signal is used to trigger server's reconfiguration.
///
/// This class allows the caller to register one or more signals to catch
/// and process.  Signals may be handled either immediately upon arrival and/or
/// recorded and processed later.  To process signals immediately, the caller
/// must register an "on-receipt" handler.  This handler is expected to return
/// a true or false indicating whether or not the signal has been processed.
/// Signal occurrences that are not processed by the on-receipt handler are
/// remembered by SignalSet for deferred processing.  The caller can then query
/// SignalSet at their discretion to determine if any signal occurrences are
/// pending and process them.
///
/// SignalSet uses an internal handler to catch all registered signals. When
/// a signal arrives the internal handler will first attempt to invoke the
/// on-receipt handler.  If one has been registered it is passed the
/// signal value as an argument and if it returns true upon completion, the
/// internal handler will exit without further action.  If the on-receipt
/// handler returned false or one is not registered, then internal handler
/// will record the signal value for deferred processing.  Note that once a
/// particular signal has been recorded, any further occurrences of that signal
/// will be discarded until the original occurrence has been processed.  This
/// guards against rapid-fire occurrences of the same signal.
///
/// @note This class is not thread safe. It uses static variables and
/// functions to track a global state of signal registration and received
/// signals' queue. But the thread library is signal safe as new threads
/// are created with all signals blocked.
class SignalSet : public boost::noncopyable {
public:
    /// @brief Constructor installing one signal.
    ///
    /// @param sig0 First signal.
    /// @throw SignalSetError If attempting to add duplicated signal or
    /// the signal is invalid.
    explicit SignalSet(const int sig0);

    /// @brief Constructor installing two signals.
    ///
    /// @param sig0 First signal.
    /// @param sig1 Second signal.
    /// @throw SignalSetError If attempting to add duplicated signal or
    /// the signal is invalid.
    SignalSet(const int sig0, const int sig1);

    /// @brief Constructor installing three signals.
    ///
    /// @param sig0 First signal.
    /// @param sig1 Second signal.
    /// @param sig2 Third signal.
    /// @throw SignalSetError If attempting to add duplicated signal or
    /// the signal is invalid.
    SignalSet(const int sig0, const int sig1, const int sig2);

    /// @brief Destructor.
    ///
    /// Removes installed handlers.
    ~SignalSet();

    /// @brief Installs the handler for the specified signal.
    ///
    /// This function adds a signal to the set. When the signal is received
    /// by the process, it will be recorded and a signal can be later handled
    /// by the process.
    ///
    /// @param sig Signal code.
    /// @throw SignalSetError if signal being added duplicates an existing
    /// signal.
    void add(const int sig);

    /// @brief Uninstalls all signals.
    ///
    /// This function calls @c isc::util::SignalSet::remove for each
    /// installed signal.
    void clear();

    /// @brief Returns a code of the next received signal.
    ///
    /// @return A code of the next received signal or -1 if there are no
    /// more signals received.
    int getNext() const;

    /// @brief Calls a handler for the next received signal.
    ///
    /// This function handles the next received signal and removes it from the
    /// queue of received signals. While the function is executed, all custom
    /// signal handlers are blocked to prevent race condition.
    ///
    /// @param signal_handler A pointer to the signal handler function to
    /// be used to handle the signal.
    void handleNext(SignalHandler signal_handler);

    /// @brief Uninstalls signal handler for a specified signal.
    ///
    /// @param sig A code of the signal to be removed.
    void remove(const int sig);

    /// @brief Registers a handler as the onreceipt signal handler
    ///
    /// Sets the given handler as the handler to invoke immediately
    /// upon receipt of a a registered signal.
    ///
    /// @note Currently, the on-receipt handler is stored as a static
    /// value and hence there may only be one such handler at a time
    /// for a given process.
    ///
    /// @param handler the signal handler to register
    static void setOnReceiptHandler(BoolSignalHandler handler);

    /// @brief Unregisters the onreceipt signal handler
    static void clearOnReceiptHandler();

    /// @brief Invokes the onreceipt handler if it exists
    ///
    /// This static method is used by @c isc::util::SignalSet class to
    /// invoke the registered handler (if one) immediately upon receipt of
    /// a registered signal.
    ///
    /// Prior to invoking the handler, it sets signal action for the
    /// given signal to SIG_IGN which prevents any repeat signal
    /// occurrences from queuing while the handler is executing.  Upon
    /// completion of the handler, the signal action is restored which
    /// re-enables receipt and handling of the signal.
    ///
    /// @param sig Signal number.
    /// @return Boolean false if no on-receipt handler was registered,
    /// otherwise it is the value returned by the on-receipt handler.
    static bool invokeOnReceiptHandler(int sig);

private:

    /// @brief Blocks signals in the set.
    ///
    /// This function blocks the signals in a set to prevent race condition
    /// between the signal handler and the new signal coming in.
    void block() const;

    /// @brief Removes the signal from the set.
    ///
    /// This function removes only a signal which is owned by this signal set.
    ///
    /// @param sig Signal to be removed.
    /// @throw SignalSetError if the signal being removed is not owned by this
    /// signal set.
    void erase(const int sig);

    /// @brief Insert a signal to the set.
    ///
    /// @param sig Signal to be inserted.
    /// @throw SignalSetError if a signal being inserted has already been
    /// registered in this or other signal set.
    void insert(const int sig);

    /// @brief Applies a mask to all signals in the set.
    ///
    /// This function is used by @c SignalSet::block and @c SignalSet::unblock
    /// to apply the SIG_BLOCK and SIG_UNBLOCK mask to signals.
    ///
    /// @param mask A mask to be applied to all signals.
    void maskSignals(const int mask) const;

    /// @brief Pops a next signal number from the static collection of signals.
    ///
    /// The static collection of signals is updated by the internal signal
    /// handler being invoked when one of the installed signals is received by
    /// the process. This function removes the first element of the collection.
    void popNext();

    /// @brief Unblocks signals in the set.
    ///
    /// This function unblocks the signals in a set.
    void unblock() const;

    /// @brief Stores the set of signals registered in this signal set.
    std::set<int> local_signals_;

    /// @brief Shared pointer to static set of registered signals
    /// Set during construction to ensure static set does not lose scope
    /// before we do.
    SigIntSetPtr registered_signals_;

    /// @brief Shared pointer to static list of pending signals
    /// Set during construction to ensure static list does not lose scope
    /// before we do.
    SigIntListPtr signal_states_;
};

}
}

#endif // SIGNAL_SET_H

