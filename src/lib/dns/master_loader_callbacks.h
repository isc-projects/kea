// Copyright (C) 2012-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MASTER_LOADER_CALLBACKS_H
#define MASTER_LOADER_CALLBACKS_H

#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>
#include <functional>
#include <string>

namespace isc {
namespace dns {
class Name;
class RRClass;
class RRType;
class RRTTL;
namespace rdata {
class Rdata;
typedef boost::shared_ptr<Rdata> RdataPtr;
}

/// \brief Type of callback to add a RR.
///
/// This type of callback is used by the loader to report another loaded
/// RR. The Rdata is no longer preserved by the loader and is fully
/// owned by the callback.
///
/// \param name The domain name where the RR belongs.
/// \param rrclass The class of the RR.
/// \param rrtype Type of the RR.
/// \param rrttl Time to live of the RR.
/// \param rdata The actual carried data of the RR.
typedef std::function<void(const Name& name, const RRClass& rrclass,
                           const RRType& rrtype, const RRTTL& rrttl,
                           const rdata::RdataPtr& rdata)>
    AddRRCallback;

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
    typedef std::function<void(const std::string& source_name,
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
        if (!error_ || !warning_) {
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
               const std::string& reason) const
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
                 const std::string& reason) const
    {
        warning_(source_name, source_line, reason);
    }

    /// \brief Return a callbacks instance with null callbacks
    ///
    /// This is a convenience wrapper to generate a
    /// \c MasterLoaderCallbacks object with both callbacks being nothing.
    /// This will be useful for applications that only need to run
    /// \c MasterLoader and get the end result.
    ///
    /// \throw None
    static MasterLoaderCallbacks getNullCallbacks();

private:
    const IssueCallback error_, warning_;
};

}
}

#endif // MASTER_LOADER_CALLBACKS_H
