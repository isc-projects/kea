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

#ifndef ZONE_RELOADER_H
#define ZONE_RELOADER_H

#include "load_action.h"

#include <dns/rrclass.h>
#include <dns/name.h>

namespace isc {
namespace datasrc {
namespace memory {
class ZoneData;
class ZoneTableSegment;

/// \brief Does an update to a zone.
///
/// This abstract base class represents the work of a reload of a zone.
/// The work is divided into three stages -- load(), install() and cleanup().
/// They should be called in this order for the effect to take place.
///
/// We divide them so the update of zone data can be done asynchronously,
/// in a different thread. The install() operation is the only one that needs
/// to be done in a critical section.
class ZoneWriter {
public:
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
    /// \throw isc::Unexpected if called second time.
    virtual void load() = 0;

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
    /// This may throw in rare cases, depending on the concrete implementation.
    /// If it throws, you still need to call cleanup().
    ///
    /// \throw isc::Unexpected if called without previous load() or for the
    ///     second time or cleanup() was called already.
    virtual void install() = 0;

    /// \brief Clean up resources.
    ///
    /// This releases all resources held by owned zone data. That means the
    /// one loaded by load() in case install() was not called or was not
    /// successful, or the one replaced in install().
    ///
    /// Generally, this should never throw.
    virtual void cleanup() = 0;
};

/// \brief Writer implementation which loads data locally.
///
/// This implementation prepares a clean zone data and lets one callback
/// to fill it and another to install it somewhere. The class does mostly
/// nothing (and delegates the work to the callbacks), just stores little bit
/// of state between the calls.
class ZoneWriterLocal : public ZoneWriter {
public:
    /// \brief Constructor
    ///
    /// \param segment The zone table segment to store the zone into.
    /// \param load_action The callback used to load data.
    /// \param install_action The callback used to install the loaded zone.
    /// \param rrclass The class of the zone.
    ZoneWriterLocal(ZoneTableSegment* segment, const LoadAction& load_action,
                      const dns::Name& name, const dns::RRClass& rrclass);

    /// \brief Destructor
    ~ZoneWriterLocal();

    /// \brief Loads the data.
    ///
    /// This prepares an empty ZoneData and calls load_action (passed to
    /// constructor) to fill it with data.
    ///
    /// \throw std::bad_alloc If there's a problem allocating the ZoneData.
    /// \throw isc::Unexpected if it is called the second time in lifetime
    ///     of the object.
    /// \throw Whatever the load_action throws, it is propagated up.
    virtual void load();

    /// \brief Installs the zone.
    ///
    /// This simply calls the install_action.
    ///
    /// \throw isc::Unexpected if it is called the second time in lifetime
    ///     of the object or if load() was not called previously or if
    ///     cleanup() was already called.
    /// \throw Whatever the install_action throws, it is propagated up.
    virtual void install();

    /// \brief Clean up memory.
    ///
    /// Cleans up the memory used by load()ed zone if not yet installed, or
    /// the old zone replaced by install().
    virtual void cleanup();
private:
    ZoneTableSegment* segment_;
    LoadAction load_action_;
    dns::Name origin_;
    dns::RRClass rrclass_;
    ZoneData* zone_data_;
    // The load was performed
    bool loaded_;
    // The data are ready to be installed
    bool data_ready_;
};

}
}
}

#endif
