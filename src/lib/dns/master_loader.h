// Copyright (C) 2012-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MASTER_LOADER_H
#define MASTER_LOADER_H

#include <dns/master_loader_callbacks.h>

#include <boost/noncopyable.hpp>

namespace isc {
namespace dns {

class Name;
class RRClass;

/// \brief Error while loading by MasterLoader without specifying the
///     MANY_ERRORS option.
class MasterLoaderError : public isc::Exception {
public:
    MasterLoaderError(const char* file, size_t line, const char* what) :
        Exception(file, line, what)
    {}
};

/// \brief A class able to load DNS master files
///
/// This class is able to produce a stream of RRs from a master file.
/// It is able to load all of the master file at once, or by blocks
/// incrementally.
///
/// It reports the loaded RRs and encountered errors by callbacks.
class MasterLoader : boost::noncopyable {
public:
    /// \brief Options how the parsing should work.
    enum Options {
        DEFAULT = 0,       ///< Nothing special.
        MANY_ERRORS = 1    ///< Lenient mode (see documentation of MasterLoader
                           ///  constructor).
    };

    /// \brief Constructor
    ///
    /// This creates a master loader and provides it with all
    /// relevant information.
    ///
    /// Except for the exceptions listed below, the constructor doesn't
    /// throw. Most errors (like non-existent master file) are reported
    /// by the callbacks during load() or loadIncremental().
    ///
    /// \param master_file Path to the file to load.
    /// \param zone_origin The origin of zone to be expected inside
    ///     the master file. Currently unused, but it is expected to
    ///     be used for some validation.
    /// \param zone_class The class of zone to be expected inside the
    ///     master file.
    /// \param callbacks The callbacks by which it should report problems.
    ///     Usually, the callback carries a filename and line number of the
    ///     input where the problem happens. There's a special case of empty
    ///     filename and zero line in case the opening of the top-level master
    ///     file fails.
    /// \param add_callback The callback which would be called with each
    ///     loaded RR.
    /// \param options Options for the parsing, which is bitwise-or of
    ///     the Options values or DEFAULT. If the MANY_ERRORS option is
    ///     included, the parser tries to continue past errors. If it
    ///     is not included, it stops at first encountered error.
    /// \throw std::bad_alloc when there's not enough memory.
    /// \throw isc::InvalidParameter if add_callback is empty.
    MasterLoader(const char* master_file,
                 const Name& zone_origin,
                 const RRClass& zone_class,
                 const MasterLoaderCallbacks& callbacks,
                 const AddRRCallback& add_callback,
                 Options options = DEFAULT);

    /// \brief Constructor from a stream
    ///
    /// This is a constructor very similar to the previous one. The only
    /// difference is it doesn't take a filename, but an input stream
    /// to read the data from. It is expected to be mostly used in tests,
    /// but it is public as it may possibly be useful for other currently
    /// unknown purposes.
    MasterLoader(std::istream& input,
                 const Name& zone_origin,
                 const RRClass& zone_class,
                 const MasterLoaderCallbacks& callbacks,
                 const AddRRCallback& add_callback,
                 Options options = DEFAULT);

    /// \brief Destructor
    ~MasterLoader();

    /// \brief Load some RRs
    ///
    /// This method loads at most count_limit RRs and reports them. In case
    /// an error (either fatal or without MANY_ERRORS) or end of file is
    /// encountered, they may be less.
    ///
    /// \param count_limit Upper limit on the number of RRs loaded.
    /// \return In case it stops because of the count limit, it returns false.
    ///     It returns true if the loading is done.
    /// \throw isc::InvalidOperation when called after loading was done
    ///     already.
    /// \throw MasterLoaderError when there's an error in the input master
    ///     file and the MANY_ERRORS is not specified. It never throws this
    ///     in case MANY_ERRORS is specified.
    bool loadIncremental(size_t count_limit);

    /// \brief Load everything
    ///
    /// This simply calls loadIncremental until the loading is done.
    /// \throw isc::InvalidOperation when called after loading was done
    ///     already.
    /// \throw MasterLoaderError when there's an error in the input master
    ///     file and the MANY_ERRORS is not specified. It never throws this
    ///     in case MANY_ERRORS is specified.
    void load() {
        while (!loadIncremental(1000)) { // 1000 = arbitrary largish number
            // Body intentionally left blank
        }
    }

    /// \brief Was the loading successful?
    ///
    /// \return true if and only if the loading was complete (after a call of
    ///     load or after loadIncremental returned true) and there was no
    ///     error. In other cases, return false.
    /// \note While this method works even before the loading is complete (by
    ///     returning false in that case), it is meant to be called only after
    ///     finishing the load.
    bool loadedSuccessfully() const;

    /// \brief Return the total size of the zone files and streams.
    ///
    /// This method returns the size of the source of the zone to be loaded
    /// (master zone files or streams) that is known at the time of the call.
    /// For a zone file, it's the size of the file; for a stream, it's the
    /// size of the data (in bytes) available at the start of the load.
    /// If separate zone files are included via the $INCLUDE directive, the
    /// sum of the sizes of these files are added.
    ///
    /// If the loader is constructed with a stream, the size can be
    /// "unknown" as described for \c MasterLexer::getTotalSourceSize().
    /// In this case this method always returns
    /// \c MasterLexer::SOURCE_SIZE_UNKNOWN.
    ///
    /// If the loader is constructed with a zone file, this method
    /// initially returns 0.  So until either \c load() or \c loadIncremental()
    /// is called, the value is meaningless.
    ///
    /// Note that when the source includes separate files, this method
    /// cannot take into account the included files that the loader has not
    /// recognized at the time of call.  So it's possible that this method
    /// returns different values at different times of call.
    ///
    /// \throw None
    size_t getSize() const;

    /// \brief Return the position of the loader in zone.
    ///
    /// This method returns a conceptual "position" of the loader in the
    /// zone to be loaded.  Specifically, it returns the total number of
    /// characters contained in the zone files and streams and recognized
    /// by the loader.  Before starting the load it returns 0; on successful
    /// completion it will be equal to the return value of \c getSize()
    /// (unless the latter returns \c MasterLexer::SOURCE_SIZE_UNKNOWN).
    ///
    /// \throw None
    size_t getPosition() const;

private:
    class MasterLoaderImpl;
    MasterLoaderImpl* impl_;
};

} // end namespace dns
} // end namespace isc

#endif // MASTER_LOADER_H

// Local Variables:
// mode: c++
// End:
