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


#include <dhcpsrv/logging_info.h>

namespace isc {
namespace dhcp {

bool
LoggingDestination::equals(const LoggingDestination& other) const {
    return (output_ == other.output_ &&
            maxver_ == other.maxver_ &&
            maxsize_ == other.maxsize_);
}

bool
LoggingInfo::equals(const LoggingInfo& other) const {
    // If number of destinations aren't equal, the objects are not equal.
    if (destinations_.size() != other.destinations_.size()) {
        return (false);
    }
    // If there is the same number of logging destinations verify that the
    // destinations are equal. The order doesn't matter to we don't expect
    // that they are at the same index of the vectors.
    for (std::vector<LoggingDestination>::const_iterator
             it_this = destinations_.begin();
         it_this != destinations_.end();
         ++it_this) {
        bool match = false;
        for (std::vector<LoggingDestination>::const_iterator
                 it_other = other.destinations_.begin();
             it_other != other.destinations_.end();
             ++it_other) {
            if (it_this->equals(*it_other)) {
                match = true;
                break;
            }
        }
        if (!match) {
            return (false);
        }
    }

    // Logging destinations are equal. Check the rest of the parameters for
    // equality.
    return (name_ == other.name_ &&
            severity_ == other.severity_ &&
            debuglevel_ == other.debuglevel_);
}

} // end of namespace isc::dhcp
} // end of namespace isc
