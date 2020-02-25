// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONTEXT_H
#define CONTEXT_H

#include <stats/observation.h>
#include <boost/shared_ptr.hpp>
#include <mutex>
#include <string>

namespace isc {
namespace stats {

/// @brief Exception indicating that a given statistic is duplicated.
class DuplicateStat : public Exception {
public:
    DuplicateStat(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Statistics context
///
/// Statistics context is essentially a container used to group statistics
/// related to a given context together. Two examples of such contexts are
/// all statistics related to a given subnet or all statistics related to a
/// given network interface.
struct StatContext {
public:

    /// @brief Attempts to get an observation
    ///
    /// @param name name of the statistic
    /// @return appropriate Observation object (or NULL)
    ObservationPtr get(const std::string& name) const;

    /// @brief Adds a new observation
    ///
    /// @param obs observation to be added
    /// @throw DuplicateStat if an observation with the same name exists already
    void add(const ObservationPtr& obs);

    /// @brief Attempts to delete an observation
    ///
    /// @param name name of the observation to be deleted
    /// @return true if successful, false if no such statistic was found
    bool del(const std::string& name);

    /// @brief Returns the number of observations
    ///
    /// @return the number of observations
    size_t size();

    /// @brief Removes all observations
    void clear();

    /// @brief Resets all observations
    void resetAll();

    /// @brief Sets max sample count for all observations
    ///
    /// @param max_samples value to be set for all observations
    void setMaxSampleCountAll(uint32_t max_samples);

    /// @brief Sets duration for all observations
    ///
    /// @param duration value to be set for all observations
    void setMaxSampleAgeAll(const StatsDuration& duration);

    /// @brief Returns a map with all observations
    ///
    /// @return map with all observations
    isc::data::ConstElementPtr getAll() const;

private:

    /// @brief Statistics container
    std::map<std::string, ObservationPtr> stats_;
};

/// @brief Pointer to the statistics context
typedef boost::shared_ptr<StatContext> StatContextPtr;

};
};

#endif // CONTEXT_H
