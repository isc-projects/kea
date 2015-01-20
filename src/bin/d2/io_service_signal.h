// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef IO_SERVICE_SIGNAL_H
#define IO_SERVICE_SIGNAL_H

#include <asiolink/io_service.h>
#include <asiolink/interval_timer.h>
#include <exceptions/exceptions.h>

#include <map>
#include <stdint.h>

namespace isc {
namespace d2 {

/// @brief Exception thrown if IOSignal encounters an error.
class IOSignalError : public isc::Exception {
public:
    IOSignalError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Defines a unique identifier type for IOSignal.
typedef uint64_t IOSignalId;

/// @brief Defines a handler function for an IOSignal.
/// IOSignalHandlers should contain the application level logic that would
/// ordinarily be an OS signal handler.
typedef boost::function<void(IOSignalId sequence_id)> IOSignalHandler;

/// @brief Implements an asynchronous "signal" for IOService driven processing
///
/// This class allows a OS signal such as SIGHUP to propagated to an IOService
/// as a ready event with a callback. While boost::asio provides a signal class,
/// it requires linking in additional boost libraries that as of yet we do not
/// need. Therefore, this class was implemented to allow IOService-based
/// processes to handle signals as IOService events.
///
/// The mechanics of IOSignal are straight forward. Upon construction it is
/// given the target IOService, the value of the signal to send (i.e. SIGINT,
/// SIGHUP...), and an IOSignalHandler.  The IOSignalHandler should contain
/// the logic the caller would normally execute in its OS signal handler. Each
/// IOSignal instance has a unique identifier called its sequence_id.
///
/// Internally, IOSignal creates a 1 ms, one-shot timer, on the given
/// IOService.  When the timer expires its event handler invokes the caller's
/// IOSignalHandler passing it the sequence_id of the IOSignal.
///
/// Sending IOSignals is done through an IOSignalQueue.  This class is used to
/// create the signals, house them until they are delivered, and dequeue them
/// so they can be been handled.  To generate an IOSignal when an OS signal
/// arrives, the process's OS signal handler simply calls @ref
/// isc::d2::IOSignalQueue::pushSignal() with the appropriate values.
///
/// @note that an IOSignalQueue requires a non-null IOServicePtr to construct.
/// This ensures that the IOService cannot be destroyed before any pending
/// signals can be canceled.  It also means that a queue can only be used to
/// send signals to that IOService.  If you need to send signals to more than
/// one service, each service must have its own queue.
///
/// To dequeue the IOSignal inside the caller's IOSignalHandler, one simply
/// invokes @ref isc::d2::IOSignalQueue::popSignal() passing it the sequence_id
/// parameter passed to the handler.  This method returns a pointer to
/// instigating IOSignal from which the value of OS signal (i.e. SIGINT,
/// SIGUSR1...) can be obtained.  Note that calling popSignal() removes the
/// IOSignalPtr from the queue, which should reduce its reference count to
/// zero upon exiting the handler (unless a delibrate copy of it is made).
///
/// A typical IOSignalHandler might be structured as follows:
/// @code
///
///    void processSignal(IOSignalId sequence_id) {
///        // Pop the signal instance off the queue.
///        IOSignalPtr signal = io_signal_queue_->popSignal(sequence_id);
///
///        int os_signal_value = signal->getSignum();
///        :
///        // logic based on the signal value
///        :
///     }
///
/// @endcode
///
/// IOSignal handler invocation code will catch, log ,and then swallow any
/// exceptions thrown by a IOSignalHandler invocation.  This is done to protect
/// the integrity IOService context.
///
class IOSignal {
public:
    /// @brief Constructor
    ///
    /// @param io_service IOService to which to send the signal
    /// @param signum value of the signal to send
    /// @param handler the handler to run when IOService "receives" the
    /// signal
    ///
    /// @throw IOSignalError if handler is null
    IOSignal(asiolink::IOService& io_service, int signum,
              IOSignalHandler handler);

    /// @brief Destructor
    ~IOSignal();

    /// @brief Static method for generating IOSignal sequence_ids.
    ///
    /// Generates and returns the next IOSignalId. This method is intentionally
    /// static in the event a process is using generating signals to more than
    /// IOService.  It assures that each IOSignal is unique with the process
    /// space.
    ///
    /// @return The next sequential value as an IOSignalId.
    static IOSignalId nextSequenceId() {
        static IOSignalId next_id_ = 0;
        return (++next_id_);
    }

    /// @brief Gets the IOSignal's sequence_id
    ///
    /// @return The sequence_id of the signal.
    IOSignalId getSequenceId() const {
        return (sequence_id_);
    }

    /// @brief Gets the OS signal value this IOSignal represents.
    ///
    /// @return The OS signal value (i.e. SIGINT, SIGUSR1...)
    int getSignum() const {
        return (signum_);
    }

    /// @brief Defines the callback used by IOSignal's internal timer.
    ///
    /// This class stores the sequence_id of the IOSignal being sent and the
    /// IOSignalHandler to invoke when delivering the signal.  The () operator
    /// is called by IOService when the timer expires.  This method invokes
    /// the IOSignalHandler passing it the sequence_id.
    class TimerCallback : public std::unary_function<void, void> {
    public:
        /// @brief Constructor
        ///
        /// @param sequence_id sequence_id of the IOSignal to handle
        /// @param handler pointer to the function to handle the IOSignal
        ///
        /// @throw IOSignalError if handler is null.
        TimerCallback(IOSignalId sequence_id, IOSignalHandler handler);

        /// @brief () Operator which serves as the timer's callback
        ///
        /// It is invoked when the timer expires and calls the handler
        /// passing in the signal.
        void operator()();

    private:
        /// @brief Id of the IOSignal to which the callback pertains.
        IOSignalId sequence_id_;

        /// @brief Pointer to the function to handle the signal
        IOSignalHandler handler_;
    };

private:
    /// @brief Value which uniquely identifies each IOSignal instance.
    IOSignalId sequence_id_;

    /// @brief Numeric value of the signal to send (e.g. SIGINT, SIGUSR1...)
    int signum_;

    /// @brief Timer instance created to propagate the signal.
    asiolink::IntervalTimerPtr timer_;
};

/// @brief Defines a pointer to an IOSignal
typedef boost::shared_ptr<IOSignal> IOSignalPtr;

/// @brief Defines a map of IOSignalPtr keyed by id
typedef std::map<IOSignalId, IOSignalPtr> IOSignalMap;

/// @brief Creates and manages IOSignals
///
/// This class is used to create IOSignals, house them until they are delivered,
/// and dequeue them so they can be been handled.  IOSignals are designed to
/// used once and then destroyed.  They need to be created from within OS
/// signal handlers and persist until they have been delivered and processed.
///
/// This class is designed specifically to make managing them painless.
/// It maintains an internal map of IOSignals keyed by sequence_id. When a
/// signal is created via the pushSignal() method it is added to the map. When
/// a signal is retrevied via the popSignal() method it is removed from the map.
class IOSignalQueue {
public:
    /// @brief Constructor
    ///
    /// @param io_service the IOService to which to send signals.
    /// @throw IOSignalError if io_service is NULL.
    IOSignalQueue (asiolink::IOServicePtr& io_service);

    /// @brief Destructor.
    ~IOSignalQueue();

    /// @brief Creates an IOSignal
    ///
    /// Given a signal number and a handler, it will instantiate an IOSignal
    /// and add it to the instance map.  (Remember that IOSignals are really
    /// just timers programmed during construction, so once instantiated
    /// there's nothing more required to "send" the signal other than return
    /// control to IOService::run()).
    ///
    /// @param signum OS signal value of the signal to propagate
    /// @param handler IOSignalHandler to invoke when the signal is delivererd.
    ///
    /// @return The sequence_id of the newly created signal.
    ///
    /// @throw IOSignalError if the sequence_id already exists in the map. This
    /// is virtually impossible unless things have gone very wrong.
    IOSignalId pushSignal(int signum, IOSignalHandler handler);

    /// @brief Removes an IOSignal from the map and returns it.
    ///
    /// Given a sequence_id this method will extract the IOSignal from the
    /// internal map and return.  At that point, the caller will hold the
    /// only copy of the IOSignal.
    ///
    /// @param sequence_id  sequence_id of the IOSignal to retrieve.
    ///
    /// @return A smart pointer to the IOSignal.
    ///
    /// @throw IOSignalError if there is no matching IOSignal in the map for
    /// the given sequence_id.  Other than by doubling popping, this should be
    /// very unlikley.
    IOSignalPtr popSignal(IOSignalId sequence_id);

    /// @brief Erases the contents of the queue.
    ///
    /// Any instances still in the map will be destroyed. This will cause their
    /// timers to be cancelled without any callbacks invoked. (Not sure when
    /// this might be desirable).
    void clear();

private:
    /// @brief Pointer to the IOService which will receive the signals.
    asiolink::IOServicePtr io_service_;

    /// @brief A map of the IOSignals pushed through this queue.
    IOSignalMap signals_;
};

/// @brief Defines a pointer to an IOSignalQueue.
typedef boost::shared_ptr<IOSignalQueue> IOSignalQueuePtr;


}; // end of isc::d2 namespace
}; // end of isc namespace

#endif // IO_SERVICE_SIGNAL_H
