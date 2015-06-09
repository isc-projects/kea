// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef D2_PROCESS_H
#define D2_PROCESS_H

#include <d2/d_process.h>
#include <d2/d2_queue_mgr.h>
#include <d2/d2_update_mgr.h>

namespace isc {
namespace d2 {

/// @brief DHCP-DDNS Application Process
///
/// D2Process provides the top level application logic for DHCP-driven DDNS
/// update processing.  It provides the asynchronous event processing required
/// to receive DNS mapping change requests and carry them out.
/// It implements the DProcessBase interface, which structures it such that it
/// is a managed "application", controlled by a management layer.
class D2Process : public DProcessBase {
public:

    /// @brief Defines the shutdown types supported by D2Process
    ///
    /// * SD_NORMAL - Stops the queue manager and finishes all current
    /// transactions before exiting. This is the default.
    ///
    /// * SD_DRAIN_FIRST - Stops the queue manager but continues processing
    /// requests from the queue until it is empty.
    ///
    /// * SD_NOW - Exits immediately.
    enum ShutdownType {
      SD_NORMAL,
      SD_DRAIN_FIRST,
      SD_NOW
    };

    /// @brief Defines the point at which to resume receiving requests.
    /// If the receive queue has become full, D2Process will "pause" the
    /// reception of requests by putting the queue manager in the stopped
    /// state.  Once the number of entries has decreased to this percentage
    /// of  the maximum allowed, D2Process will "resume" receiving requests
    /// by restarting the queue manager.
    static const unsigned int QUEUE_RESTART_PERCENT;

    /// @brief Constructor
    ///
    /// Construction creates the configuration manager, the queue
    /// manager, and the update manager.
    ///
    /// @param name name is a text label for the process. Generally used
    /// in log statements, but otherwise arbitrary.
    /// @param io_service is the io_service used by the caller for
    /// asynchronous event handling.
    ///
    /// @throw DProcessBaseError if io_service is NULL.
    D2Process(const char* name, const asiolink::IOServicePtr& io_service);

    /// @brief Called after instantiation to perform initialization unique to
    /// D2.
    ///
    /// This is invoked by the controller after command line arguments but
    /// PRIOR to configuration reception.  The base class provides this method
    /// as a place to perform any derivation-specific initialization steps
    /// that are inapppropriate for the constructor but necessary prior to
    /// launch.  So far, no such steps have been identified for D2, so its
    /// implementantion is empty but required.
    ///
    /// @throw DProcessBaseError if the initialization fails.
    virtual void init();

    /// @brief Implements the process's event loop.
    ///
    /// Once entered, the main control thread remains inside this method
    /// until shutdown.  The event loop logic is as follows:
    /// @code
    ///    while should not shutdown {
    ///       process queue manager state change
    ///       process completed jobs
    ///       dequeue new jobs
    ///       wait for IO event(s)
    ///
    ///       ON an exception, exit with fatal error
    ///    }
    /// @endcode
    ///
    /// To summarize, each pass through the event loop first checks the state
    /// of the received queue and takes any steps required to ensure it is
    /// operating in the manner necessary.  Next the update manager is given
    /// a chance to clean up any completed transactions and start new
    /// transactions by dequeuing jobs from the request queue.  Lastly, it
    /// allows IOService to process until one or more event handlers are
    /// called.  Note that this last step will block until at least one
    /// ready handler is invoked.  In other words, if no IO events have occurred
    /// since it was last called, the event loop will block at this step until
    /// an IO event occurs.  At that time we return to the top of the loop.
    ///
    /// @throw DProcessBaseError if an error is encountered.  Note that
    /// exceptions thrown at this point are assumed to be FATAL exceptions.
    /// This includes exceptions generated but not caught by IO callbacks.
    /// Services which rely on callbacks are expected to be well behaved and
    /// any errors they encounter handled internally.
    virtual void run();

    /// @brief Initiates the D2Process shutdown process.
    ///
    /// This is last step in the shutdown event callback chain. It is invoked
    /// to notify D2Process that it needs to begin its shutdown procedure.
    /// Note that shutting down may be neither instantaneous nor synchronous,
    /// This method records the request for and the type of shutdown desired.
    /// Generally it will require one or more subsequent events to complete,
    /// dependent on the type of shutdown requested.  The type of shutdown is
    /// specified as an optional argument of the shutdown command. The types
    /// of shutdown supported are:
    ///
    /// * "normal" - Stops the queue manager and finishes all current
    /// transactions before exiting. This is the default.
    ///
    /// * "drain_first" - Stops the queue manager but continues processing
    /// requests from the queue until it is empty.
    ///
    /// * "now" - Exits immediately.
    ///
    /// @param args Specifies the shutdown "type" as "normal", "drain_first",
    /// or "now"
    ///
    /// @return an Element that contains the results of argument processing,
    /// consisting of an integer status value (0 means successful,
    /// non-zero means failure), and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr
        shutdown(isc::data::ConstElementPtr args);

    /// @brief Processes the given configuration.
    ///
    /// This method may be called multiple times during the process lifetime.
    /// Certainly once during process startup, and possibly later if the user
    /// alters the configuration. This method must not throw, it should catch any
    /// processing errors and return a success or failure answer as described
    /// below.
    ///
    /// This method passes the newly received configuration to the configuration
    /// manager instance for parsing.  The configuration manager parses the
    /// configuration and updates the necessary values within the context,
    /// assuming it parses correctly.  If that's the case this method sets the
    /// flag to reconfigure the queue manager and returns a successful response
    /// as described below.
    ///
    /// If the new configuration fails to parse, then the current configuration
    /// is retained and a failure response is returned as described below.
    ///
    /// @param config_set a new configuration (JSON) for the process
    /// @return an Element that contains the results of configuration composed
    /// of an integer status value (0 means successful, non-zero means failure),
    /// and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr configure(isc::data::ConstElementPtr
                                                 config_set);

    /// @brief Processes the given command.
    ///
    /// This method is called to execute any custom commands supported by the
    /// process. This method must not throw, it should catch any processing
    /// errors and return a success or failure answer as described below.
    ///
    /// @param command is a string label representing the command to execute.
    /// @param args is a set of arguments (if any) required for the given
    /// command. It can be a NULL pointer if no arguments exist for a command.
    /// @return an Element that contains the results of command composed
    /// of an integer status value (0 means successful, non-zero means failure),
    /// and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr command(const std::string& command,
                                               isc::data::ConstElementPtr args);
    /// @brief Destructor
    virtual ~D2Process();

protected:
    /// @brief Monitors current queue manager state, takes action accordingly
    ///
    /// This method ensures that the queue manager transitions to the state
    /// most appropriate to the operational state of the D2Process and any
    /// events that may have occurred since it was last called.  It is called
    /// once for each iteration of the event loop.  It is essentially a
    /// switch statement based on the D2QueueMgr's current state.  The logic
    /// is as follows:
    ///
    /// If the state is D2QueueMgr::RUNNING, and the queue manager needs to be
    /// reconfigured or we have been told to shutdown, then instruct the queue
    /// manager to stop listening. Exit the method.
    ///
    /// If the state is D2QueueMgr::STOPPED_QUEUE_FULL, then check if the
    /// number of entries in the queue has fallen below the "resume threshold".
    /// If it has, then instruct the queue manager to start listening. Exit
    /// the method.
    ///
    /// If the state is D2QueueMgr::STOPPED_RECV_ERROR, then attempt to recover
    /// by calling reconfigureQueueMgr(). Exit the method.
    ///
    /// If the state is D2QueueMgr::STOPPING, simply exit the method. This is
    /// a NOP condition as we are waiting for the IO cancel event
    ///
    /// For any other state, (NOT_INITTED,INITTED,STOPPED), if the reconfigure
    /// queue flag is set, call reconfigureQueueMgr(). Exit the method.
    ///
    /// This method is exception safe.
    virtual void checkQueueStatus();

    /// @brief Initializes then starts the queue manager.
    ///
    /// This method initializes the queue manager with the current
    /// configuration parameters and instructs it to start listening.
    /// Note the existing listener instance (if it exists) is destroyed,
    /// and that a new listener is created during initialization.
    ///
    /// This method is exception safe.
    virtual void reconfigureQueueMgr();

    /// @brief Allows IO processing to run until at least callback is invoked.
    ///
    /// This method is called from within the D2Process main event loop and is
    /// the point at which the D2Process blocks, waiting for IO events to
    /// cause IO event callbacks to be invoked.
    ///
    /// If callbacks are ready to be executed upon entry, the method will
    /// return as soon as these callbacks have completed.  If no callbacks
    /// are ready, then it will wait (indefinitely) until at least one callback
    /// is executed.
    ///
    /// @note: Should become desirable to periodically force an
    /// event, an interval timer could be used to do so.
    ///
    /// @return The number of callback handlers executed, or 0 if the IO
    /// service has been stopped.
    ///
    /// @throw This method does not throw directly, but the execution of
    /// callbacks invoked in response to IO events might.  If so, these
    /// will propagate upward out of this method.
    virtual size_t runIO();

    /// @brief Indicates whether or not the process can perform a shutdown.
    ///
    /// Determines if the process has been instructed to shutdown and if
    /// the criteria for performing the type of shutdown requested has been
    /// met.
    ///
    /// @return Returns true if the criteria has been met, false otherwise.
    virtual bool canShutdown() const;

    /// @brief Sets queue reconfigure indicator to the given value.
    ///
    /// @param value is the new value to assign to the indicator
    ///
    /// @note this method is really only intended for testing purposes.
    void setReconfQueueFlag(const bool value) {
        reconf_queue_flag_ = value;
    }

    /// @brief Sets the shutdown type to the given value.
    ///
    /// @param value is the new value to assign to shutdown type.
    ///
    /// @note this method is really only intended for testing purposes.
    void setShutdownType(const ShutdownType& value) {
        shutdown_type_ = value;
    }

public:
    /// @brief Returns a pointer to the configuration manager.
    /// Note, this method cannot return a reference as it uses dynamic
    /// pointer casting of the base class configuration manager.
    D2CfgMgrPtr getD2CfgMgr();

    /// @brief Returns a reference to the queue manager.
    const D2QueueMgrPtr& getD2QueueMgr() const {
        return (queue_mgr_);
    }

    /// @brief Returns a reference to the update manager.
    const D2UpdateMgrPtr& getD2UpdateMgr() const {
        return (update_mgr_);
    }

    /// @brief Returns true if the queue manager should be reconfigured.
    bool getReconfQueueFlag() const {
        return (reconf_queue_flag_);
    }

    /// @brief Returns the type of shutdown requested.
    ///
    /// Note, this value is meaningless unless shouldShutdown() returns true.
    ShutdownType getShutdownType() const {
        return (shutdown_type_);
    }

    /// @brief Returns a text label for the given shutdown type.
    ///
    /// @param type the numerical shutdown type for which the label is desired.
    ///
    /// @return A text label corresponding the value or "invalid" if the
    /// value is not a valid value.
    static const char* getShutdownTypeStr(const ShutdownType& type);

private:
    /// @brief Pointer to our queue manager instance.
    D2QueueMgrPtr queue_mgr_;

    /// @brief Pointer to our update manager instance.
    D2UpdateMgrPtr update_mgr_;

    /// @brief Indicates if the queue manager should be reconfigured.
    bool reconf_queue_flag_;

    /// @brief Indicates the type of shutdown requested.
    ShutdownType shutdown_type_;
};

/// @brief Defines a shared pointer to D2Process.
typedef boost::shared_ptr<D2Process> D2ProcessPtr;

}; // namespace isc::d2
}; // namespace isc

#endif
