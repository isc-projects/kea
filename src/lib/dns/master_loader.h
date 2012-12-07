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

#ifndef MASTER_LOADER_H
#define MASTER_LOADER_H

#include <dns/master_loader_callbacks.h>

#include <boost/noncopyable.hpp>

namespace isc {
namespace dns {

class Name;
class RRClass;

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
        MANY_ERRORS = 1    ///< Lenient mode.
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
    bool loadIncremental(size_t count_limit);

    /// \brief Load everything
    ///
    /// This simply calls loadIncremental until the loading is done.
    /// \throw isc::InvalidOperation when called after loading was done
    ///     already.
    void load() {
        while (!loadIncremental(1000)) { // 1000 = arbitrary largish number
            // Body intentionally left blank
        }
    }

private:
    class MasterLoaderImpl;
    MasterLoaderImpl* impl_;
};

} // end namespace dns
} // end namespace isc

#endif // MASTER_LOADER_H
