// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <set>
#include <string>

/// @file   classify.h
///
/// @brief Defines basic elements of client classification.
///
/// This file defines common elements used for client classification.
/// It is simple for now, but the complexity involved in client
/// classification is expected to grow significantly.
///
/// @todo This file should be moved to dhcpsrv eventually as the classification
/// is server side concept. That is not possible yet, as the Pkt4 and Pkt6
/// classes have server-side implementation, even though they reside in the
/// dhcp directory.

namespace isc {

namespace dhcp {

    /// Definition of a single class.
    typedef std::string ClientClass;

    /// Container for storing client classes
    typedef std::set<ClientClass> ClientClasses;

};

};
