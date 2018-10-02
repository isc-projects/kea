// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/libdhcp++.h>
#include <dhcp/option_vendor.h>
#include <dhcpsrv/testutils/generic_backend_unittest.h>

namespace isc {
namespace dhcp {
namespace test {

GenericBackendTest::GenericBackendTest() {
    LibDHCP::clearRuntimeOptionDefs();
}

GenericBackendTest::~GenericBackendTest() {
    LibDHCP::clearRuntimeOptionDefs();
}

OptionDescriptor
GenericBackendTest::createEmptyOption(const Option::Universe& universe,
                                      const uint16_t option_type,
                                      const bool persist) const {
    OptionPtr option(new Option(universe, option_type));
    OptionDescriptor desc(option, persist);
    return (desc);
}

OptionDescriptor
GenericBackendTest::createVendorOption(const Option::Universe& universe,
                                       const bool persist,
                                       const bool formatted,
                                       const uint32_t vendor_id) const {
    OptionVendorPtr option(new OptionVendor(universe, vendor_id));

    std::ostringstream s;
    if (formatted) {
        // Vendor id comprises vendor-id field, for which we need to
        // assign a value in the textual (formatted) format.
        s << vendor_id;
    }

    OptionDescriptor desc(option, persist, s.str());
    return (desc);
}


} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
