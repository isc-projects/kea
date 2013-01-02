// Copyright (C) 2012, 2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/option_space.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace isc {
namespace dhcp {

OptionSpace::OptionSpace(const std::string& name, const bool vendor_space)
    : name_(name), vendor_space_(vendor_space) {
    //  Check that provided option space name is valid.
    if (!validateName(name_)) {
        isc_throw(InvalidOptionSpace, "Invalid option space name "
                  << name_);
    }
}

bool
OptionSpace::validateName(const std::string& name) {
    // Allowed digits are: lower or upper case letters, digits,
    // underscores and dashes. Empty option spaces are not allowed.
    if (boost::algorithm::all(name, boost::is_from_range('a', 'z') ||
                              boost::is_from_range('A', 'Z') ||
                              boost::is_digit() ||
                              boost::is_any_of("-_")) &&
        !name.empty()) {
        return (true);
    }
    return (false);
}

OptionSpace6::OptionSpace6(const std::string& name)
    : OptionSpace(name),
      enterprise_number_(0) {
}

OptionSpace6::OptionSpace6(const std::string& name,
                           const uint32_t enterprise_id)
    : OptionSpace(name, true),
      enterprise_number_(enterprise_id) {
}

void
OptionSpace6::setVendorSpace(const uint32_t enterprise_id) {
    enterprise_number_ = enterprise_id;
    OptionSpace::setVendorSpace();
}

} // end of isc::dhcp namespace
} // end of isc namespace
