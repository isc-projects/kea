// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/testutils/host_data_source_utils.h>
#include <asiolink/io_address.h>
#include <boost/foreach.hpp>
#include <cc/data.h>
#include <gtest/gtest.h>

using namespace std;
using namespace isc::data;
using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {
namespace test {

std::vector<uint8_t>
HostDataSourceUtils::generateHWAddr(const bool new_identifier) {
    // Let's use something that is easily printable. That's convenient
    // if you need to enter MySQL queries by hand.
    static uint8_t hwaddr[] = {65, 66, 67, 68, 69, 70};

    if (new_identifier) {
        // Increase the address for the next time we use it.
        // This is primitive, but will work for 65k unique
        // addresses.
        hwaddr[sizeof(hwaddr) - 1]++;
        if (hwaddr[sizeof(hwaddr) - 1] == 0) {
            hwaddr[sizeof(hwaddr) - 2]++;
        }
    }
    return (std::vector<uint8_t>(hwaddr, hwaddr + sizeof(hwaddr)));
}

std::vector<uint8_t>
HostDataSourceUtils::generateIdentifier(const bool new_identifier) {
    // Let's use something that is easily printable. That's convenient
    // if you need to enter MySQL queries by hand.
    static uint8_t ident[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74};

    if (new_identifier) {
        // Increase the identifier for the next time we use it.
        // This is primitive, but will work for 65k unique identifiers.
        ident[sizeof(ident) - 1]++;
        if (ident[sizeof(ident) - 1] == 0) {
            ident[sizeof(ident) - 2]++;
        }
    }
    return (std::vector<uint8_t>(ident, ident + sizeof(ident)));
}

HostPtr
HostDataSourceUtils::initializeHost4(const std::string& address,
                                     const Host::IdentifierType& id) {
    std::vector<uint8_t> ident;
    if (id == Host::IDENT_HWADDR) {
        ident = generateHWAddr();
    } else {
        ident = generateIdentifier();
    }

    // Let's create ever increasing subnet-ids. Let's keep those different,
    // so subnet4 != subnet6. Useful for catching cases if the code confuses
    // subnet4 with subnet6.
    static SubnetID subnet4 = 0;
    static SubnetID subnet6 = 100;
    ++subnet4;
    ++subnet6;

    IOAddress addr(address);
    HostPtr host(new Host(&ident[0], ident.size(), id, subnet4, subnet6, addr));

    return (host);
}

HostPtr
HostDataSourceUtils::initializeHost6(std::string address,
                                     Host::IdentifierType identifier,
                                     bool prefix,
                                     bool new_identifier,
                                     const std::string auth_key) {
    std::vector<uint8_t> ident;
    switch (identifier) {
    case Host::IDENT_HWADDR:
        ident = generateHWAddr(new_identifier);
        break;
    case Host::IDENT_DUID:
        ident = generateIdentifier(new_identifier);
        break;
    default:
        ADD_FAILURE() << "Unknown IdType: " << identifier;
        return HostPtr();
    }

    // Let's create ever increasing subnet-ids. Let's keep those different,
    // so subnet4 != subnet6. Useful for catching cases if the code confuses
    // subnet4 with subnet6.
    static SubnetID subnet4 = 0;
    static SubnetID subnet6 = 100;
    ++subnet4;
    ++subnet6;

    HostPtr host(new Host(&ident[0], ident.size(), identifier, subnet4, subnet6,
                          IOAddress("0.0.0.0")));

    host->setKey(AuthKey(auth_key));

    if (!prefix) {
        // Create IPv6 reservation (for an address)
        IPv6Resrv resv(IPv6Resrv::TYPE_NA, IOAddress(address), 128);
        host->addReservation(resv);
    } else {
        // Create IPv6 reservation for a /64 prefix
        IPv6Resrv resv(IPv6Resrv::TYPE_PD, IOAddress(address), 64);
        host->addReservation(resv);
    }
    return (host);
}

bool
HostDataSourceUtils::reservationExists(const IPv6Resrv& resrv,
                                       const IPv6ResrvRange& range) {
    for (IPv6ResrvIterator it = range.first; it != range.second; ++it) {
        if (resrv == it->second) {
            return true;
        }
    }
    return false;
}

void
HostDataSourceUtils::compareHwaddrs(const ConstHostPtr& host1,
                                    const ConstHostPtr& host2,
                                    bool expect_match) {
    ASSERT_TRUE(host1);
    ASSERT_TRUE(host2);

    // Compare if both have or have not HWaddress set.
    if ((host1->getHWAddress() && !host2->getHWAddress()) ||
        (!host1->getHWAddress() && host2->getHWAddress())) {
        // One host has hardware address set while the other has not.
        // Let's see if it's a problem.
        if (expect_match) {
            ADD_FAILURE() << "Host comparison failed: host1 hwaddress="
                          << host1->getHWAddress()
                          << ", host2 hwaddress=" << host2->getHWAddress();
        }
        return;
    }

    // Now we know that either both or neither have hw address set.
    // If host1 has it, we can proceed to value comparison.
    if (host1->getHWAddress()) {
        if (expect_match) {
            // Compare the actual address if they match.
            EXPECT_TRUE(*host1->getHWAddress() == *host2->getHWAddress());
        } else {
            EXPECT_FALSE(*host1->getHWAddress() == *host2->getHWAddress());
        }
        if (*host1->getHWAddress() != *host2->getHWAddress()) {
            cout << host1->getHWAddress()->toText(true) << endl;
            cout << host2->getHWAddress()->toText(true) << endl;
        }
    }
}

void
HostDataSourceUtils::compareDuids(const ConstHostPtr& host1,
                                  const ConstHostPtr& host2,
                                  bool expect_match) {
    ASSERT_TRUE(host1);
    ASSERT_TRUE(host2);

    // compare if both have or have not DUID set
    if ((host1->getDuid() && !host2->getDuid()) ||
        (!host1->getDuid() && host2->getDuid())) {
        // One host has a DUID and the other doesn't.
        // Let's see if it's a problem.
        if (expect_match) {
            ADD_FAILURE() << "DUID comparison failed: host1 duid="
                          << host1->getDuid()
                          << ", host2 duid=" << host2->getDuid();
        }
        return;
    }

    // Now we know that either both or neither have DUID set.
    // If host1 has it, we can proceed to value comparison.
    if (host1->getDuid()) {
        if (expect_match) {
            EXPECT_TRUE(*host1->getDuid() == *host2->getDuid());
        } else {
            EXPECT_FALSE(*host1->getDuid() == *host2->getDuid());
        }
        if (*host1->getDuid() != *host2->getDuid()) {
            cout << host1->getDuid()->toText() << endl;
            cout << host2->getDuid()->toText() << endl;
        }
    }
}

void
HostDataSourceUtils::compareHosts(const ConstHostPtr& host1,
                                  const ConstHostPtr& host2) {
    // Let's compare HW addresses and expect match.
    compareHwaddrs(host1, host2, true);

    // Now compare DUIDs
    compareDuids(host1, host2, true);

    // Now check that the identifiers returned as vectors are the same
    EXPECT_EQ(host1->getIdentifierType(), host2->getIdentifierType());
    EXPECT_TRUE(host1->getIdentifier() == host2->getIdentifier());

    // Check host parameters
    EXPECT_EQ(host1->getIPv4SubnetID(), host2->getIPv4SubnetID());
    EXPECT_EQ(host1->getIPv6SubnetID(), host2->getIPv6SubnetID());
    EXPECT_EQ(host1->getIPv4Reservation(), host2->getIPv4Reservation());
    EXPECT_EQ(host1->getHostname(), host2->getHostname());
    EXPECT_EQ(host1->getNextServer(), host2->getNextServer());
    EXPECT_EQ(host1->getServerHostname(), host2->getServerHostname());
    EXPECT_EQ(host1->getBootFileName(), host2->getBootFileName());
    EXPECT_TRUE(host1->getKey() == host2->getKey());
    ConstElementPtr ctx1 = host1->getContext();
    ConstElementPtr ctx2 = host2->getContext();
    if (ctx1) {
        EXPECT_TRUE(ctx2);
        if (ctx2) {
            EXPECT_EQ(*ctx1, *ctx2);
        }
    } else {
        EXPECT_FALSE(ctx2);
    }

    // Compare IPv6 reservations
    compareReservations6(host1->getIPv6Reservations(),
                         host2->getIPv6Reservations());

    // Compare client classification details
    compareClientClasses(host1->getClientClasses4(),
                         host2->getClientClasses4());

    compareClientClasses(host1->getClientClasses6(),
                         host2->getClientClasses6());

    // Compare DHCPv4 and DHCPv6 options.
    compareOptions(host1->getCfgOption4(), host2->getCfgOption4());
    compareOptions(host1->getCfgOption6(), host2->getCfgOption6());
}

void
HostDataSourceUtils::compareReservations6(IPv6ResrvRange resrv1,
                                          IPv6ResrvRange resrv2) {
    // Compare number of reservations for both hosts
    if (std::distance(resrv1.first, resrv1.second) !=
        std::distance(resrv2.first, resrv2.second)) {
        ADD_FAILURE() << "Reservation comparison failed, "
                         "hosts got different number of reservations.";
        return;
    }

    // Iterate over the range of reservations to find a match in the
    // reference range.
    for (IPv6ResrvIterator r1 = resrv1.first; r1 != resrv1.second; ++r1) {
        IPv6ResrvIterator r2 = resrv2.first;
        for (; r2 != resrv2.second; ++r2) {
            // IPv6Resrv object implements equality operator.
            if (r1->second == r2->second) {
                break;
            }
        }
        // If r2 iterator reached the end of the range it means that there
        // is no match.
        if (r2 == resrv2.second) {
            ADD_FAILURE() << "No match found for reservation: "
                          << resrv1.first->second.getPrefix().toText();
        }
    }

    if (std::distance(resrv1.first, resrv1.second) > 0) {
        for (; resrv1.first != resrv1.second; resrv1.first++) {
            IPv6ResrvIterator iter = resrv2.first;
            while (iter != resrv2.second) {
                if ((resrv1.first->second.getType() ==
                     iter->second.getType()) &&
                    (resrv1.first->second.getPrefixLen() ==
                     iter->second.getPrefixLen()) &&
                    (resrv1.first->second.getPrefix() ==
                     iter->second.getPrefix())) {
                    break;
                }
                iter++;
                if (iter == resrv2.second) {
                    ADD_FAILURE() << "Reservation comparison failed, "
                                     "no match for reservation: "
                                  << resrv1.first->second.getPrefix().toText();
                }
            }
        }
    }
}

void
HostDataSourceUtils::compareClientClasses(const ClientClasses& classes1,
                                          const ClientClasses& classes2) {
    EXPECT_TRUE(std::equal(classes1.cbegin(), classes1.cend(), classes2.cbegin()));
}

void
HostDataSourceUtils::compareOptions(const ConstCfgOptionPtr& cfg1,
                                    const ConstCfgOptionPtr& cfg2) {
    ASSERT_TRUE(cfg1);
    ASSERT_TRUE(cfg2);

    // Combine option space names with vendor space names in a single list.
    std::list<std::string> option_spaces = cfg2->getOptionSpaceNames();
    std::list<std::string> vendor_spaces = cfg2->getVendorIdsSpaceNames();
    option_spaces.insert(option_spaces.end(), vendor_spaces.begin(),
                         vendor_spaces.end());

    // Make sure that the number of option spaces is equal in both
    // configurations.
    EXPECT_EQ(option_spaces.size(), cfg1->getOptionSpaceNames().size());
    EXPECT_EQ(vendor_spaces.size(), cfg1->getVendorIdsSpaceNames().size());

    // Iterate over all option spaces existing in cfg2.
    BOOST_FOREACH (std::string space, option_spaces) {
        // Retrieve options belonging to the current option space.
        OptionContainerPtr options1 = cfg1->getAll(space);
        OptionContainerPtr options2 = cfg2->getAll(space);
        ASSERT_TRUE(options1) << "failed for option space " << space;
        ASSERT_TRUE(options2) << "failed for option space " << space;

        // If number of options doesn't match, the test fails.
        ASSERT_EQ(options1->size(), options2->size())
            << "failed for option space " << space;

        // Iterate over all options within this option space.
        BOOST_FOREACH (OptionDescriptor desc1, *options1) {
            OptionDescriptor desc2 = cfg2->get(space, desc1.option_->getType());
            // Compare persistent flag.
            EXPECT_EQ(desc1.persistent_, desc2.persistent_)
                << "failed for option " << space << "."
                << desc1.option_->getType();
            // Compare formatted value.
            EXPECT_EQ(desc1.formatted_value_, desc2.formatted_value_)
                << "failed for option " << space << "."
                << desc1.option_->getType();

            // Compare user context.
            ConstElementPtr ctx1 = desc1.getContext();
            ConstElementPtr ctx2 = desc2.getContext();
            if (ctx1) {
                EXPECT_TRUE(ctx2);
                if (ctx2) {
                    EXPECT_EQ(*ctx1, *ctx2)
                        << "failed for option " << space << "." << desc1.option_->getType();
                }
            } else {
                EXPECT_FALSE(ctx2);
            }

            // Retrieve options.
            Option* option1 = desc1.option_.get();
            Option* option2 = desc2.option_.get();

            // Options must be represented by the same C++ class derived from
            // the Option class.
            EXPECT_TRUE(typeid(*option1) == typeid(*option2))
                << "Compared DHCP options, having option code "
                << desc1.option_->getType() << " and belonging to the " << space
                << " option space, are represented "
                   "by different C++ classes: "
                << typeid(*option1).name() << " vs " << typeid(*option2).name();

            // Because we use different C++ classes to represent different
            // options, the simplest way to make sure that the options are
            // equal is to simply compare them in wire format.
            OutputBuffer buf1(option1->len());
            ASSERT_NO_THROW(option1->pack(buf1));
            OutputBuffer buf2(option2->len());
            ASSERT_NO_THROW(option2->pack(buf2));

            ASSERT_EQ(buf1.getLength(), buf2.getLength())
                << "failed for option " << space << "."
                << desc1.option_->getType();
            EXPECT_EQ(0,
                      memcmp(buf1.getData(), buf2.getData(), buf1.getLength()))
                << "failed for option " << space << "."
                << desc1.option_->getType();
        }
    }
}


}
}
}

