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
