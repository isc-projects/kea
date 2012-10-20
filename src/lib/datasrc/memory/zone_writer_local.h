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

#ifndef MEM_ZONE_WRITER_LOCAL_H
#define MEM_ZONE_WRITER_LOCAL_H

#include "zone_writer.h"

#include <dns/rrclass.h>
#include <dns/name.h>

namespace isc {
namespace datasrc {
namespace memory {

class ZoneData;
class ZoneTableSegmentLocal;

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
    ZoneWriterLocal(ZoneTableSegmentLocal* segment,
                    const LoadAction& load_action, const dns::Name& name,
                    const dns::RRClass& rrclass);

    /// \brief Destructor
    ~ZoneWriterLocal();

    /// \brief Loads the data.
    ///
    /// This calls the load_action (passed to constructor) and stores the
    /// data for future use.
    ///
    /// \throw isc::InvalidOperation if it is called the second time in
    ///     lifetime of the object.
    /// \throw Whatever the load_action throws, it is propagated up.
    virtual void load();

    /// \brief Installs the zone.
    ///
    /// It modifies the zone table accessible through the segment (passed to
    /// constructor).
    ///
    /// \throw isc::InvalidOperation if it is called the second time in
    ///     lifetime of the object or if load() was not called previously or if
    ///     cleanup() was already called.
    virtual void install();

    /// \brief Clean up memory.
    ///
    /// Cleans up the memory used by load()ed zone if not yet installed, or
    /// the old zone replaced by install().
    virtual void cleanup();
private:
    ZoneTableSegmentLocal* segment_;
    LoadAction load_action_;
    dns::Name origin_;
    dns::RRClass rrclass_;
    ZoneData* zone_data_;
    enum State {
        ZW_UNUSED,
        ZW_LOADED,
        ZW_INSTALLED,
        ZW_CLEANED
    };
    State state_;
};

}
}
}

#endif
