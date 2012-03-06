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

#ifndef __NAME_INTERNAL_H
#define __NAME_INTERNAL_H 1

// This is effectively a "private" namespace for the Name class implementation,
// but exposed publicly so the definitions in it can be shared with the
// LabelSequence class.  It's not expected to be used even by other modules
// of this library, much less by normal applications.  This header file is
// therefore not expected to be installed as part of the library.
namespace isc {
namespace dns {
namespace name {
namespace internal {
extern const unsigned char maptolower[];
} // end of internal
} // end of name
} // end of dns
} // end of isc
#endif // __NAME_INTERNAL_H

// Local Variables:
// mode: c++
// End:
