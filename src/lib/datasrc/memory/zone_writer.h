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

#ifndef MEM_ZONE_WRITER_H
#define MEM_ZONE_WRITER_H

#include <datasrc/memory/load_action.h>

#include <boost/noncopyable.hpp>

#include <dns/dns_fwd.h>

namespace isc {
namespace datasrc {
namespace memory {
class ZoneTableSegment;

/// \brief Does an update to a zone.
///
/// This represents the work of a (re)load of a zone.  The work is divided
/// into three stages -- load(), install() and cleanup().  They should
/// be called in this order for the effect to take place.
///
/// We divide them so the update of zone data can be done asynchronously,
/// in a different thread. The install() operation is the only one that needs
/// to be done in a critical section.
///
/// This class provides strong exception guarantee for each public
/// method. That is, when any of the methods throws, the entire state
/// stays the same as before the call.
class ZoneWriter : boost::noncopyable {
public:
    /// \brief Constructor
    ///
    /// \throw isc::InvalidOperation if \c segment is read-only.
    ///
    /// \param segment The zone table segment to store the zone into.
    /// \param load_action The callback used to load data.
    /// \param name The name of the zone.
    /// \param rrclass The class of the zone.
    ZoneWriter(ZoneTableSegment& segment,
               const LoadAction& load_action, const dns::Name& name,
               const dns::RRClass& rrclass);

    /// \brief Destructor.
    ~ZoneWriter();

    /// \brief Get the zone data into memory.
    ///
    /// This is the part that does the time-consuming loading into the memory.
    /// This can be run in a separate thread, for example. It has no effect on
    /// the data actually served, it only prepares them for future use.
    ///
    /// This is the first method you should call on the object. Never call it
    /// multiple times.
    ///
    /// \note As this contains reading of files or other data sources, or with
    ///     some other source of the data to load, it may throw quite anything.
    ///     If it throws, do not call any other methods on the object and
    ///     discard it.
    /// \note After successful load(), you have to call cleanup() some time
    ///     later.
    /// \throw isc::InvalidOperation if called second time.
    void load();

    /// \brief Put the changes to effect.
    ///
    /// This replaces the old version of zone with the one previously prepared
    /// by load(). It takes ownership of the old zone data, if any.
    ///
    /// You may call it only after successful load() and at most once.
    ///
    /// The operation is expected to be fast and is meant to be used inside
    /// a critical section.
    ///
    /// This may throw in rare cases.  If it throws, you still need to
    /// call cleanup().
    ///
    /// \throw isc::InvalidOperation if called without previous load() or for
    ///     the second time or cleanup() was called already.
    void install();

    /// \brief Clean up resources.
    ///
    /// This releases all resources held by owned zone data. That means the
    /// one loaded by load() in case install() was not called or was not
    /// successful, or the one replaced in install().
    ///
    /// \throw none
    void cleanup();

private:
    // We hide details as this class will be used by various applications
    // and we use some internal data structures in the implementation.
    struct Impl;
    Impl* impl_;
};

}
}
}

#endif
