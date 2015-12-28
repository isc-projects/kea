// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONTEXT_H
#define CONTEXT_H

#include <stats/observation.h>
#include <boost/shared_ptr.hpp>
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

    /// @brief attempts to get an observation
    /// @param name name of the statistic
    /// @return appropriate Observation object (or NULL)
    ObservationPtr get(const std::string& name) const;

    /// @brief Adds a new observation
    /// @param obs observation to be added
    /// @throw DuplicateStat if an observation with the same name exists already
    void add(const ObservationPtr& obs);

    /// @brief Attempts to delete an observation
    /// @param name name of the observation to be deleted
    /// @return true if successful, false if no such statistic was found
    bool del(const std::string& name);

    /// @brief Statistics container
    ///
    /// It is public to allow various operations that require iterating over
    /// all elements. In particular, two operations (setting all stats to 0;
    /// reporting all stats) will take advantage of this. Alternatively, we
    /// could make it protected and then return a pointer to it, but that
    /// would defeat the purpose of the hermetization in the first place.
    std::map<std::string, ObservationPtr> stats_;
};

/// @brief Pointer to the statistics context
typedef boost::shared_ptr<StatContext> StatContextPtr;

};
};

#endif // CONTEXT_H
