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

#ifndef DATASRC_ZONE_LOADER_H
#define DATASRC_ZONE_LOADER_H

#include <datasrc/exceptions.h>

#include <dns/master_loader.h>

#include <cstdlib> // For size_t
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

namespace isc {
namespace dns {
// Forward declaration
class Name;
}
namespace datasrc {

// Forward declarations
class DataSourceClient;
class ZoneIterator;
typedef boost::shared_ptr<ZoneIterator> ZoneIteratorPtr;
class ZoneUpdater;
typedef boost::shared_ptr<ZoneUpdater> ZoneUpdaterPtr;

/// \brief Exception thrown when there's a problem with master file.
///
/// This is thrown by the ZoneLoader when there's a fatal problem with
/// a master file being loaded.
class MasterFileError : public DataSourceError {
public:
    MasterFileError(const char* file, size_t line, const char* what) :
        DataSourceError(file, line, what)
    {}
};

/// \brief Exception thrown when the zone doesn't pass post-load check.
///
/// This is thrown by the ZoneLoader when the zone is loaded, but it
/// doesn't pass basic sanity checks.
class ZoneContentError : public DataSourceError {
public:
    ZoneContentError(const char* file, size_t line, const char* what) :
        DataSourceError(file, line, what)
    {}
};

/// \brief Class to load data into a data source client.
///
/// This is a small wrapper class that is able to load data into a data source.
/// It can load either from another data source or from a master file. The
/// purpose of the class is only to hold the state for incremental loading.
///
/// The old content of zone is discarded and no journal is stored.
class ZoneLoader {
public:
    /// \brief Constructor from master file.
    ///
    /// This initializes the zone loader to load from a master file.
    ///
    /// \param destination The data source into which the loaded data should
    ///     go.
    /// \param zone_name The origin of the zone. The class is implicit in the
    ///     destination.
    /// \param master_file Path to the master file to read data from.
    /// \throw DataSourceError in case the zone does not exist in destination.
    ///     This class does not support creating brand new zones, only loading
    ///     data into them. In case a new zone is needed, it must be created
    ///     beforehand.
    /// \throw DataSourceError in case of other (possibly low-level) errors,
    ///     such as read-only data source or database error.
    ZoneLoader(DataSourceClient& destination, const isc::dns::Name& zone_name,
               const char* master_file);

    /// \brief Constructor from another data source.
    ///
    /// This initializes the zone loader to read from another data source.
    /// It'll effectively copy data from one data source to another.
    ///
    /// \param destination The data source into which the loaded data should
    ///     go.
    /// \param zone_name The origin of the zone.
    /// \param source The data source from which the data would be read.
    /// \throw InvalidParameter in case the class of destination and source
    ///     differs.
    /// \throw NotImplemented in case the source data source client doesn't
    ///     provide an iterator.
    /// \throw DataSourceError in case the zone does not exist in destination.
    ///     This class does not support creating brand new zones, only loading
    ///     data into them. In case a new zone is needed, it must be created
    ///     beforehand.
    /// \throw DataSourceError in case the zone does not exist in the source.
    /// \throw DataSourceError in case of other (possibly low-level) errors,
    ///     such as read-only data source or database error.
    ZoneLoader(DataSourceClient& destination, const isc::dns::Name& zone_name,
               DataSourceClient& source);

    /// \brief Perform the whole load.
    ///
    /// This performs the whole loading operation. It may take a long time.
    ///
    /// \throw InvalidOperation in case the loading was already completed
    ///     before this call.
    /// \throw DataSourceError in case some error (possibly low-level) happens.
    /// \throw MasterFileError when the master_file is badly formatted or some
    ///     similar problem is found when loading the master file.
    /// \throw ZoneContentError when the zone doesn't pass sanity check.
    void load() {
        while (!loadIncremental(1000)) { // 1000 is arbitrary largish number
            // Body intentionally left blank.
        }
    }

    /// \brief Load up to limit RRs.
    ///
    /// This performs a part of the loading. In case there's enough data in the
    /// source, it copies limit RRs. It can copy less RRs during the final call
    /// (when there's less than limit left).
    ///
    /// This can be called repeatedly until the whole zone is loaded, having
    /// pauses in the loading for some purposes (for example reporting
    /// progress).
    ///
    /// After the last RR is loaded, a sanity check of the zone is performed by
    /// isc::dns::validateZone. It reports errors and warnings by logging them
    /// directly. If there are any errors, a ZoneContentError exception is
    /// thrown and the load is aborted (preserving the old version of zone, if
    /// any).
    ///
    /// \param limit The maximum allowed number of RRs to be loaded during this
    ///     call.
    /// \return True in case the loading is completed, false if there's more
    ///     to load.
    /// \throw InvalidOperation in case the loading was already completed
    ///     before this call (by load() or by a loadIncremental that returned
    ///     true).
    /// \throw DataSourceError in case some error (possibly low-level) happens.
    /// \throw MasterFileError when the master_file is badly formatted or some
    ///     similar problem is found when loading the master file.
    /// \throw ZoneContentError when the zone doesn't pass sanity check.
    /// \note If the limit is exactly the number of RRs available to be loaded,
    ///     the method still returns false and true'll be returned on the next
    ///     call (which will load 0 RRs). This is because the end of iterator
    ///     or master file is detected when reading past the end, not when the
    ///     last one is read.
    bool loadIncremental(size_t limit);

    /// \brief Return the number of RRs loaded.
    ///
    /// This method returns the number of RRs loaded via this loader by the
    /// time of the call.  Before starting the load it will return 0.
    /// It will return the total number of RRs of the zone on and after
    /// completing the load.
    ///
    /// \throw None
    size_t getRRCount() const;

    /// \brief Return the current progress of the loader.
    ///
    /// This method returns the current estimated progress of loader as a
    /// value between 0 and 1 (inclusive); it's 0 before starting the load,
    /// and 1 at the completion, and a value between these (exclusive) in the
    /// middle of loading.  It's an implementation detail how to calculate
    /// the progress, which may vary depending on how the loader is
    /// constructed and may even be impossible to detect effectively.
    ///
    /// If the progress cannot be determined, this method returns a special
    /// value of PROGRESS_UNKNOWN, which is not included in the range between
    /// 0 and 1.
    ///
    /// As such, the application should use the return value only for
    /// informational purposes such as logging.  For example, it shouldn't
    /// be used to determine whether loading is completed by comparing it
    /// to 1.  It should also expect the possibility of getting
    /// \c PROGRESS_UNKNOWN at any call to this method; it shouldn't assume
    /// the specific way of internal implementation as described below (which
    /// is provided for informational purposes only).
    ///
    /// In this implementation, if the loader is constructed with a file
    /// name, the progress value is measured by the number of characters
    /// read from the zone file divided by the size of the zone file
    /// (with taking into account any included files).  Note that due to
    /// the possibility of intermediate included files, the total file size
    /// cannot be fully fixed until the completion of the load.  And, due to
    /// this possibility, return values from this method may not always
    /// increase monotonically.
    ///
    /// If it's constructed with another data source client, this method
    /// always returns \c PROGRESS_UNKNOWN; in future, however, it may become
    /// possible to return something more useful, e.g, based on the result
    /// of \c getRRCount() and the total number of RRs if the underlying data
    /// source can provide the latter value efficiently.
    ///
    /// \throw None
    double getProgress() const;

    /// \brief A special value for \c getProgress, meaning the progress is
    /// unknown.
    ///
    /// See the method description for details.
    static const double PROGRESS_UNKNOWN;

private:
    /// \brief The iterator used as source of data in case of the copy mode.
    const ZoneIteratorPtr iterator_;
    /// \brief The destination zone updater
    const ZoneUpdaterPtr updater_;
    /// \brief The master loader (for the master file mode)
    boost::scoped_ptr<isc::dns::MasterLoader> loader_;
    /// \brief Indicator if loading was completed
    bool complete_;
    /// \brief Was the loading successful?
    bool loaded_ok_;
    size_t rr_count_;
};

}
}

#endif  // DATASRC_ZONE_LOADER_H

// Local Variables:
// mode: c++
// End:
