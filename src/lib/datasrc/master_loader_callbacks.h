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

#ifndef DATASRC_MASTER_LOADER_CALLBACKS_H
#define DATASRC_MASTER_LOADER_CALLBACKS_H

#include <dns/master_loader_callbacks.h>

namespace isc {
namespace datasrc {

class ZoneUpdater;

/// \brief Create issue callbacks for MasterLoader
///
/// This will create set of callbacks for the MasterLoader that
/// will be used to report any issues found in the zone data.
///
/// \param name Name of the zone. Used in logging.
/// \param rrclass The class of the zone. Used in logging.
/// \param ok If this is non-NULL and there are any errors during
///     the loading, it is set to false. Otherwise, it is untouched.
/// \return Set of callbacks to be passed to the master loader.
/// \throw std::bad_alloc when allocation fails.
isc::dns::MasterLoaderCallbacks
createMasterLoaderCallbacks(const isc::dns::Name& name,
                            const isc::dns::RRClass& rrclass, bool* ok);

/// \brief Create a callback for MasterLoader to add RRsets.
///
/// This creates a callback that can be used by the MasterLoader to add
/// loaded RRsets into a zone updater.
///
/// The zone updater should be opened in the replace mode no changes should
/// have been done to it yet (but it is not checked). It is not commited
/// automatically and it is up to the caller to commit the changes (or not).
/// It must not be destroyed for the whole time of loading.
///
/// The function is mostly straightforward packing of the updater.addRRset
/// into a boost::function, it is defined explicitly due to small technical
/// annoyences around boost::bind application, so it can be reused.
///
/// \param updater The zone updater to use.
/// \return The callback to be passed to MasterLoader.
/// \throw std::bad_alloc when allocation fails.
isc::dns::AddRRsetCallback
createMasterLoaderAddCallback(ZoneUpdater& updater);

}
}

#endif
