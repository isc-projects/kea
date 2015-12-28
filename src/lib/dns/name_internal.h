// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NAME_INTERNAL_H
#define NAME_INTERNAL_H 1

// This is effectively a "private" namespace for the Name class implementation,
// but exposed publicly so the definitions in it can be shared with other
// modules of the library (as of its introduction, used by LabelSequence and
// MessageRenderer).  It's not expected to be used even by normal applications.
// This header file is therefore not expected to be installed as part of the
// library.
//
// Note: if it turns out that we need this shortcut for many other places
// we may even want to make it expose to other Kea modules, but for now
// we'll keep it semi-private (note also that except for very performance
// sensitive applications the standard std::tolower() function should be just
// sufficient).
namespace isc {
namespace dns {
namespace name {
namespace internal {
extern const uint8_t maptolower[];
} // end of internal
} // end of name
} // end of dns
} // end of isc
#endif // NAME_INTERNAL_H

// Local Variables:
// mode: c++
// End:
