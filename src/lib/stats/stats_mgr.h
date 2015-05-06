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

#ifndef STATSMGR_H
#define STATSMGR_H

#include <stats/observation.h>
#include <stats/context.h>
#include <boost/noncopyable.hpp>

#include <map>
#include <string>
#include <vector>

namespace isc {
namespace stats {

class StatsMgr : public boost::noncopyable {
 public:

    static StatsMgr& instance();

    // methods used data producers
    void addValue(const std::string& name, uint64_t value = 1);
    void addValue(const std::string& name, double value = 1.0f);
    void addValue(const std::string& name, StatsDuration time);
    void setValue(const std::string& name, uint64_t value = 1);
    void setValue(const std::string& name, double value = 1.0f);
    void setValue(const std::string& name, StatsDuration time);

    // resets statistic
    // this is a convenience function and is equivalent to
    // setValue(0) or setValue(0.0f)
    void reset(const std::string& name);

    /// @brief determines whether a given statistic is kept as a single value
    ///        or as a number of values
    /// 
    /// Specifies that statistic name should be stored not as a single value,
    /// but rather as a set of values. duration determines the timespan.
    /// Samples older than duration will be discarded. This is time-constrained
    /// approach. For sample count constrained approach, see setStorage() below.
    ///
    /// Example: to set a statistic to keep observations for the last 5 minutes,
    /// call setStorage("incoming-packets", time_duration(0,5,0,0));
    /// to revert statistic to a single value, call:
    /// setStorage("incoming-packets" time_duration(0,0,0,0))
    void setStorage(const std::string& name,
                    boost::posix_time::time_duration duration);

    /// @brief determines how many samples of a given statistic should be kept.
    ///
    /// Specifies that statistic name should be stored not as single value, but
    /// rather as a set of values. In this form, at most max_samples will be kept.
    /// When adding max_samples+1 sample, the oldest sample will be discarded.
    ///
    /// Example:
    /// To set a statistic to keep the last 100 observations, call:
    /// setStorage("incoming-packets", 100);
    void setStorage(const std::string& name, uint32_t max_samples);

    // methods used by data consumers
    const ObservationPtr& getValue(const std::string& name);

    // returns all statistics
    const std::map<std::string, ObservationPtr> getValues();

 private:
    /// @brief returns a context for specified name
    StatContextPtr getContext(const std::string& name);

    // This is a global context. All stats will initially be stored here.
    StatContextPtr global_;

    std::map<std::string, StatContextPtr> contexts_;
};

};
};

#endif // STATS_MGR
