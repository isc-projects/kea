// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp/option_space.h>
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

    using namespace boost::algorithm;

    // Allowed characters are: lower or upper case letters, digits,
    // underscores and hyphens. Empty option spaces are not allowed.
    if (all(name, boost::is_from_range('a', 'z') ||
            boost::is_from_range('A', 'Z') ||
            boost::is_digit() ||
            boost::is_any_of(std::string("-_"))) &&
        !name.empty() &&
        // Hyphens and underscores are not allowed at the beginning
        // and at the end of the option space name.
        !all(find_head(name, 1), boost::is_any_of(std::string("-_"))) &&
        !all(find_tail(name, 1), boost::is_any_of(std::string("-_")))) {
        return (true);

    }
    return (false);
}

OptionSpace6::OptionSpace6(const std::string& name)
    : OptionSpace(name),
      enterprise_number_(0) {
}

OptionSpace6::OptionSpace6(const std::string& name,
                           const uint32_t enterprise_number)
    : OptionSpace(name, true),
      enterprise_number_(enterprise_number) {
}

void
OptionSpace6::setVendorSpace(const uint32_t enterprise_number) {
    enterprise_number_ = enterprise_number;
    OptionSpace::setVendorSpace();
}

} // end of isc::dhcp namespace
} // end of isc namespace
