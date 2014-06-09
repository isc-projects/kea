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

#ifndef SIGNAL_SET_H
#define SIGNAL_SET_H

#include <exceptions/exceptions.h>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <set>
#include <signal.h>

namespace isc {
namespace util {

/// @brief Exception thrown when the @c isc::util::io::SignalSet class
/// experiences an error.
class SignalSetError : public Exception {
public:
    SignalSetError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Forward declaration to the @c isc::util::io::SignalSet.
class SignalSet;
/// @brief Pointer to the @c isc::util::io::SignalSet.
typedef boost::shared_ptr<SignalSet> SignalSetPtr;
/// @brief Pointer to the signal handling function.
typedef boost::function<void(int signum)> SignalHandler;

/// @brief Represents a collection of signals handled in a customized way.
///
/// Kea processes must handle selected signals in a specialized way. For
/// example: SIGINT and SIGTERM must perform a graceful shut down of the
/// server. The SIGHUP signal is used to trigger server's reconfiguration.
///
/// This class allows specifying signals which should be handled in a
/// specialized way as well as specifying a signal handler function.
/// When a signal is received the signal handler function is called and
/// the code of the received signal is recorded. This function doesn't
/// do anything beyond recording the signal number to minimize the time
/// spent on handling the signal and process interruption. The process
/// can later check the signals received and call the handlers on its
/// descretion by calling a @c isc::util::io::SignalSet::handleNext function.
///
/// @note This class is not thread safe. It uses static variables and
/// functions to track a global state of signal registration and received
/// signals' queue.
class SignalSet : public boost::noncopyable {
public:

    /// @brief Constructor installing one signal.
    ///
    /// @param sig0 First signal.
    /// @throw SignalSetError If attempting to add duplicated signal or
    /// the signal is invalid.
    SignalSet(const int sig0);

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
    /// This function calls @c isc::util::io::SignalSet::remove for each
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

private:

    /// @brief Blocks signals in the set.
    ///
    /// This function blocks the signals in a set to prevent race condition
    /// between the signal handler and the new signal coming in.
    void block() const {
        maskSignals(SIG_BLOCK);
    }

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
    void unblock() const {
        maskSignals(SIG_UNBLOCK);
    }

    /// @brief Stores the set of signals registered in this signal set.
    std::set<int> local_signals_;
};

}
}

#endif // SIGNAL_SET_H

