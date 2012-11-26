// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef MASTER_LOADER_CALLBACKS_H
#define MASTER_LOADER_CALLBACKS_H

#include <exceptions/exceptions.h>

#include <string>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dns {

class AbstractRRset;
typedef boost::shared_ptr<AbstractRRset> RRsetPtr;

/// \brief Type of callback to add a RRset.
///
/// This type of callback is used by the loader to report another loaded
/// RRset. The RRset is no longer preserved by the loader and is fully
/// owned by the callback.
///
/// \param RRset The rrset to add. It does not contain the accompanying
///     RRSIG (if the zone is signed), they are reported with separate
///     calls to the callback.
typedef boost::function<void(const RRsetPtr& rrset)> AddRRsetCallback;

/// \brief Set of issue callbacks for a loader.
///
/// This holds a set of callbacks by which a loader (such as MasterLoader)
/// can report loaded RRsets, errors and other unusual conditions.
///
/// All the callbacks must be set.
class MasterLoaderCallbacks {
public:
    /// \brief Type of one callback to report problems.
    ///
    /// This is the type of one callback used to report an unusual
    /// condition or error.
    ///
    /// \param source_name The name of the source where the problem happened.
    ///     This is usually a file name.
    /// \param source_line Position of the problem, counted in lines from the
    ///     beginning of the source.
    /// \param reason Human readable description of what happened.
    typedef boost::function<void(const std::string& source_name,
                                 size_t source_line,
                                 const std::string& reason)> IssueCallback;

    /// \brief Constructor
    ///
    /// Initializes the callbacks.
    ///
    /// \param error The error callback to use.
    /// \param warning The warning callback to use.
    /// \throw isc::InvalidParameter if any of the callbacks is empty.
    MasterLoaderCallbacks(const IssueCallback& error,
                          const IssueCallback& warning) :
        error_(error),
        warning_(warning)
    {
        if (error_.empty() || warning_.empty()) {
            isc_throw(isc::InvalidParameter,
                      "Empty function passed as callback");
        }
    }

    /// \brief Call callback for serious errors
    ///
    /// This is called whenever there's a serious problem which makes the data
    /// being loaded unusable. Further processing may or may not happen after
    /// this (for example to detect further errors), but the data should not
    /// be used.
    ///
    /// It calls whatever was passed to the error parameter to the constructor.
    ///
    /// If the caller of the loader wants to abort, it is possible to throw
    /// from the callback, which aborts the load.
    void error(const std::string& source_name, size_t source_line,
               const std::string& reason)
    {
        error_(source_name, source_line, reason);
    }

    /// \brief Call callback for potential problems
    ///
    /// This is called whenever a minor problem is discovered. This might mean
    /// the data is completely OK, it just looks suspicious.
    ///
    /// It calls whatever was passed to the warn parameter to the constructor.
    ///
    /// The loading will continue after the callback. If the caller wants to
    /// abort (which is probably not a very good idea, since warnings
    /// may be false positives), it is possible to throw from inside the
    /// callback.
    void warning(const std::string& source_name, size_t source_line,
                 const std::string& reason)
    {
        warning_(source_name, source_line, reason);
    }

private:
    IssueCallback error_, warning_;
};

}
}

#endif // LOADER_CALLBACKS_H
