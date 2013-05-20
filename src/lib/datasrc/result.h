// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DATASRC_RESULT_H
#define DATASRC_RESULT_H 1

namespace isc {
namespace datasrc {
namespace result {
/// \brief Result codes of various public methods of DataSourceClient.
///
/// The detailed semantics may differ in different methods.
/// See the description of specific methods for more details.
enum Result {
    SUCCESS,  ///< The operation is successful.
    EXIST,    ///< The search key is already stored.
    NOTFOUND, ///< The specified object is not found.
    PARTIALMATCH ///< Only a partial match is found.
};

/// \brief Flags for supplemental information along with the \c Result
///
/// Initially there's only one flag defined, but several flags will be added
/// later.  One likely case is to indicate a flag that is listed in in-memory
/// but its content is served in the underlying data source.  This will help
/// when only a subset of zones are cached in-memory so the lookup code can
/// efficiently detect whether it doesn't exist or is not just cached.
/// When more flags are added, the logical-or operation should be allowed
/// (by defining \c operator|) on these flags.
enum ResultFlags {
    FLAGS_DEFAULT = 0,          // no flags
    ZONE_EMPTY = 1 ///< The zone found is empty, normally meaning it's broken
};

}
}
}

#endif  // DATASRC_RESULT_H

// Local Variables:
// mode: c++
// End:
