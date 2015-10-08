// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef CFG_EXPIRATION_H
#define CFG_EXPIRATION_H

#include <boost/shared_ptr.hpp>
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
class CfgExpiration {
public:

    /// @name Default values.
    //@{
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

    //@}

    /// @name Upper limits for the parameters
    //@{
    ///
    /// @brief Maximum value for reclaim-timer-wait-time.
    static const uint16_t LIMIT_RECLAIM_TIMER_WAIT_TIME;

    /// @brief Maximum value for flush-reclaimed-timer-wait-time.
    static const uint16_t LIMIT_FLUSH_RECLAIMED_TIMER_WAIT_TIME;

    /// @brief Maximum value for hold-reclaimed-time.
    static const uint32_t LIMIT_HOLD_RECLAIMED_TIME;

    /// @brief Maximum value for max-reclaim-leases.
    static const uint32_t LIMIT_MAX_RECLAIM_LEASES;

    /// @brief Defalt value for max-reclaim-time.
    static const uint16_t LIMIT_MAX_RECLAIM_TIME;

    /// @brief Maximum value for unwarned-reclaim-cycles.
    static const uint16_t LIMIT_UNWARNED_RECLAIM_CYCLES;

    //@}

    /// @brief Constructor.
    ///
    /// Sets all parameters to their defaults.
    CfgExpiration();

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

};

/// @name Pointers to the @c CfgExpiration objects.
//@{
/// @brief Pointer to the Non-const object.
typedef boost::shared_ptr<CfgExpiration> CfgExpirationPtr;

/// @brief Pointer to the const object.
typedef boost::shared_ptr<const CfgExpiration> ConstCfgExpirationPtr;

//@}

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // CFG_EXPIRATION_H
