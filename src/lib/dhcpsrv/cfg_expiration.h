// Copyright (C) 2015-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_EXPIRATION_H
#define CFG_EXPIRATION_H

#include <asiolink/interval_timer.h>
#include <cc/cfg_to_element.h>
#include <dhcpsrv/timer_mgr.h>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <stdint.h>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Holds configuration parameters pertaining to lease expiration
/// and lease affinity.
///
/// This class holds the values of the following configuration parameters:
///
/// - reclaim-timer-wait-time - is the time between two cycles of processing
///   expired leases, expressed in seconds, i.e. the time between the end of
///   one cycle and the beginning of the next cycle. If this value is 0, the
///   expired leases are not processed.
///
/// - flush-reclaimed-timer-wait-time - is the time between two cycles of
///   recycling "expired-reclaimed" leases, expressed in seconds. If this
///   value is 0, the expired leases are removed by the leases reclamation
///   routine rather than recycling function. The recycling function is not
///   executed and the value of the "hold-reclaimed-time" is ignored.
///
/// - hold-reclaimed-time -is the time for which "expired-reclaimed" leases
///   are held in the lease database in the "expired-reclaimed" state after
///   they expire. If this time is set to 0, the recycling function is not
///   executed and the value of the "recycle-timer-wait-time" is ignored.
///   This value is expressed in seconds.
///
/// - max-reclaim-leases - is the maximum number of leases to be processed
///   in a single cycle. If this value is 0, all expired leases are
///   processed in a single cycle, unless the maximum processing time
///   (configured with the "max-time") parameter elapses first.
///
/// - max-reclaim-time - the maximum time that a single processing cycle
///   may last, expressed in milliseconds. If this value is 0, there is no
///   limitation for the maximum processing time. This value is expressed
///   in milliseconds.
///
/// - unwarned-reclaim-cycles - is the number of consecutive processing
///   cycles of expired leases, after which the system issues a warning if
///   there are still expired leases in the database. If this value is 0,
///   the warning is never issued.
///
/// The @c CfgExpiration class provides a collection of accessors and
/// modifiers to manage the data. Each accessor checks if the given value
/// is in range allowed for this value.
class CfgExpiration : public isc::data::CfgToElement {
public:

    /// @name Default values.
    ///@{
    ///
    /// @brief Default value for reclaim-timer-wait-time.
    static const uint16_t DEFAULT_RECLAIM_TIMER_WAIT_TIME;

    /// @brief Default value for flush-reclaimed-timer-wait-time.
    static const uint16_t DEFAULT_FLUSH_RECLAIMED_TIMER_WAIT_TIME;

    /// @brief Default value for hold-reclaimed-time.
    static const uint32_t DEFAULT_HOLD_RECLAIMED_TIME;

    /// @brief Default value for max-reclaim-leases.
    static const uint32_t DEFAULT_MAX_RECLAIM_LEASES;

    /// @brief Default value for max-reclaim-time.
    static const uint16_t DEFAULT_MAX_RECLAIM_TIME;

    /// @brief Default value for unwarned-reclaim-cycles.
    static const uint16_t DEFAULT_UNWARNED_RECLAIM_CYCLES;

    ///@}

    /// @name Upper limits for the parameters
    ///@{
    ///
    /// @brief Maximum value for reclaim-timer-wait-time.
    static const uint16_t LIMIT_RECLAIM_TIMER_WAIT_TIME;

    /// @brief Maximum value for flush-reclaimed-timer-wait-time.
    static const uint16_t LIMIT_FLUSH_RECLAIMED_TIMER_WAIT_TIME;

    /// @brief Maximum value for hold-reclaimed-time.
    static const uint32_t LIMIT_HOLD_RECLAIMED_TIME;

    /// @brief Maximum value for max-reclaim-leases.
    static const uint32_t LIMIT_MAX_RECLAIM_LEASES;

    /// @brief Default value for max-reclaim-time.
    static const uint16_t LIMIT_MAX_RECLAIM_TIME;

    /// @brief Maximum value for unwarned-reclaim-cycles.
    static const uint16_t LIMIT_UNWARNED_RECLAIM_CYCLES;

    ///@}

    /// @name Timers' names
    ///@{

    /// @brief Name of the timer for reclaiming expired leases.
    static const std::string RECLAIM_EXPIRED_TIMER_NAME;

    /// @brief Name of the timer for flushing reclaimed leases.
    static const std::string FLUSH_RECLAIMED_TIMER_NAME;

    ///@}

    /// @brief Constructor.
    ///
    /// Sets all parameters to their defaults.
    ///
    /// @param test_mode Indicates if the instance should be created in the
    /// test mode. In this mode the intervals for the timers are considered to
    /// be specified in milliseconds, rather than seconds. This facilitates
    /// testing execution of timers without the delays.
    CfgExpiration(const bool test_mode = false);

    /// @brief Returns reclaim-timer-wait-time
    uint16_t getReclaimTimerWaitTime() const {
        return (reclaim_timer_wait_time_);
    }

    /// @brief Sets reclaim-timer-wait-time
    ///
    /// @param reclaim_timer_wait_time New value.
    void setReclaimTimerWaitTime(const int64_t reclaim_timer_wait_time);

    /// @brief Returns flush-reclaimed-timer-wait-time.
    uint16_t getFlushReclaimedTimerWaitTime() const {
        return (flush_reclaimed_timer_wait_time_);
    }

    /// @brief Sets flush-reclaimed-timer-wait-time.
    ///
    /// @param flush_reclaimed_wait_time New value.
    void setFlushReclaimedTimerWaitTime(const int64_t flush_reclaimed_wait_time);

    /// @brief Returns hold-reclaimed-time.
    uint32_t getHoldReclaimedTime() const {
        return (hold_reclaimed_time_);
    }

    /// @brief Sets hold-reclaimed-time
    ///
    /// @param hold_reclaimed_time New value.
    void setHoldReclaimedTime(const int64_t hold_reclaimed_time);

    /// @brief Returns max-reclaim-leases.
    uint32_t getMaxReclaimLeases() const {
        return (max_reclaim_leases_);
    }

    /// @brief Sets max-reclaim-leases.
    ///
    /// @param max_reclaim_leases New value.
    void setMaxReclaimLeases(const int64_t max_reclaim_leases);

    /// @brief Returns max-reclaim-time.
    uint16_t getMaxReclaimTime() const {
        return (max_reclaim_time_);
    }

    /// @brief Sets max-reclaim-time.
    ///
    /// @param max_reclaim_time New value.
    void setMaxReclaimTime(const int64_t max_reclaim_time);

    /// @brief Returns unwarned-reclaim-cycles.
    uint16_t getUnwarnedReclaimCycles() const {
        return (unwarned_reclaim_cycles_);
    }

    /// @brief Sets unwarned-reclaim-cycles.
    ///
    /// @param unwarned_reclaim_cycles New value.
    void setUnwarnedReclaimCycles(const int64_t unwarned_reclaim_cycles);

    /// @brief Setup timers for the reclamation of expired leases according
    /// to the configuration parameters.
    ///
    /// This method includes the logic for setting the interval timers
    /// performing the reclamation of the expired leases and the removal
    /// of expired-reclaimed leases.
    ///
    /// The following is the sample code illustrating how to call this function
    /// to setup the leases reclamation for the DHCPv4 server.
    /// @code
    ///     CfgExpiration cfg;
    ///
    ///     (set some cfg values here)
    ///
    ///     AllocEnginePtr alloc_engine(new AllocEngine(...));
    ///     cfg.setupTimers(&AllocEngine::reclaimExpiredLeases4,
    ///                     &AllocEngine::deleteExpiredReclaimedLeases4,
    ///                     alloc_engine.get());
    /// @endcode
    ///
    /// @param reclaim_fun Pointer to the leases reclamation routine.
    /// @param delete_fun Pointer to the function which removes the
    /// expired-reclaimed leases from the lease database.
    /// @param instance_ptr Pointer to the instance of the object which
    /// implements the lease reclamation routine. Typically it will be
    /// the pointer to the @c AllocEngine. In case of unit tests it
    /// will be a pointer to some test class which provides stub
    /// implementation of the leases reclamation routines.
    /// @tparam Instance Instance of the object in which both functions
    /// are implemented.
    template<typename Instance>
    void setupTimers(void (Instance::*reclaim_fun)(const size_t, const uint16_t,
                                                   const bool, const uint16_t),
                     void (Instance::*delete_fun)(const uint32_t),
                     Instance* instance_ptr) const;

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

private:

    /// @brief Checks if the value being set by one of the modifiers is
    /// within an allowed range.
    ///
    /// @param value Value to be checked.
    /// @param max_value Maximum allowed value.
    /// @param config_parameter_name A name of the configuration parameter
    /// (used for logging purposes if value is out of range).
    ///
    /// @throw isc::OutOfRange if the value is negative or greater than
    /// the maximum value.
    void rangeCheck(const int64_t value, const uint64_t max_value,
                    const std::string& config_parameter_name) const;

    /// @brief reclaim-timer-wait-time
    uint16_t reclaim_timer_wait_time_;

    /// @brief flush-reclaimed-timer-wait-time
    uint16_t flush_reclaimed_timer_wait_time_;

    /// @brief hold-reclaimed-time
    uint32_t hold_reclaimed_time_;

    /// @brief max-reclaim-leases
    uint32_t max_reclaim_leases_;

    /// @brief max-reclaim-time
    uint16_t max_reclaim_time_;

    /// @brief unwarned-reclaim-cycles.
    uint16_t unwarned_reclaim_cycles_;

    /// @brief Pointer to the instance of the Timer Manager.
    TimerMgrPtr timer_mgr_;

    /// @brief Indicates if the instance is in the test mode.
    bool test_mode_;
};

/// @name Pointers to the @c CfgExpiration objects.
///@{
/// @brief Pointer to the Non-const object.
typedef boost::shared_ptr<CfgExpiration> CfgExpirationPtr;

/// @brief Pointer to the const object.
typedef boost::shared_ptr<const CfgExpiration> ConstCfgExpirationPtr;

///@}

template<typename Instance>
void
CfgExpiration::setupTimers(void (Instance::*reclaim_fun)(const size_t,
                                                         const uint16_t,
                                                         const bool,
                                                         const uint16_t),
                           void (Instance::*delete_fun)(const uint32_t),
                           Instance* instance_ptr) const {
    // One of the parameters passed to the leases' reclamation routine
    // is a boolean value which indicates if reclaimed leases should
    // be removed by the leases' reclamation routine. This is the case
    // when the timer for flushing reclaimed leases is set to 0
    // (disabled).
    const bool flush_timer_disabled = (getFlushReclaimedTimerWaitTime() == 0);

    // If the timer interval for the leases reclamation is non-zero
    // the timer will be scheduled.
    if (getReclaimTimerWaitTime() > 0) {
        // In the test mode the interval is expressed in milliseconds.
        // If this is not the test mode, the interval is in seconds.
        const long reclaim_interval = test_mode_ ? getReclaimTimerWaitTime() :
            1000 * getReclaimTimerWaitTime();
        // Register timer for leases' reclamation routine.
        timer_mgr_->registerTimer(RECLAIM_EXPIRED_TIMER_NAME,
                                  std::bind(reclaim_fun, instance_ptr,
                                            getMaxReclaimLeases(),
                                            getMaxReclaimTime(),
                                            flush_timer_disabled,
                                            getUnwarnedReclaimCycles()),
                                  reclaim_interval,
                                  asiolink::IntervalTimer::ONE_SHOT);
        timer_mgr_->setup(RECLAIM_EXPIRED_TIMER_NAME);
    }

    // If the interval for the timer flushing expired-reclaimed leases
    // is set we will schedule the timer.
    if (!flush_timer_disabled) {
        // The interval is specified in milliseconds if we're in the test mode.
        // It is specified in seconds otherwise.
        const long flush_interval = test_mode_ ?
            getFlushReclaimedTimerWaitTime() :
            1000 * getFlushReclaimedTimerWaitTime();
        // Register and setup the timer.
        timer_mgr_->registerTimer(FLUSH_RECLAIMED_TIMER_NAME,
                                  std::bind(delete_fun, instance_ptr,
                                            getHoldReclaimedTime()),
                                  flush_interval,
                                  asiolink::IntervalTimer::ONE_SHOT);
        timer_mgr_->setup(FLUSH_RECLAIMED_TIMER_NAME);
    }
}


} // end of isc::dhcp namespace
} // end of isc namespace

#endif // CFG_EXPIRATION_H
