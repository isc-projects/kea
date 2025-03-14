// Copyright (C) 2012-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/option6_pdexclude.h>
#include <dhcpsrv/pool.h>
#include <testutils/test_to_element.h>

#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <sstream>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::asiolink;

namespace {

/// @brief Class for testing pools.
class PoolTest : public ::testing::Test {
public:
    /// @brief Constructor
    PoolTest() = default;

    /// @brief Destructor
    virtual ~PoolTest() = default;

    /// @brief Verifies the DDNS parameter accessors and the
    /// hasDdnsParameters() method.
    ///
    /// @param family sets the protocol to be used AF_INET or AF_INET6.
    void checkDdnsParameters(uint16_t family) {
        PoolPtr pool;
        if (family == AF_INET) {
            pool.reset(new Pool4(IOAddress("192.0.2.0"), 25));
        } else {
            pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8::1"),
                                 IOAddress("2001:db8::2")));
        }

        EXPECT_FALSE(pool->hasDdnsParameters());

        util::Optional<bool> bool_unspec;
        util::Optional<bool> bool_spec(true);

        pool->setDdnsSendUpdates(bool_spec);
        EXPECT_EQ(pool->getDdnsSendUpdates(), bool_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setDdnsSendUpdates(bool_unspec);
        EXPECT_FALSE(pool->hasDdnsParameters());

        pool->setDdnsOverrideNoUpdate(bool_spec);
        EXPECT_EQ(pool->getDdnsOverrideNoUpdate(), bool_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setDdnsOverrideNoUpdate(bool_unspec);
        EXPECT_FALSE(pool->hasDdnsParameters());

        pool->setDdnsOverrideClientUpdate(bool_spec);
        EXPECT_EQ(pool->getDdnsOverrideClientUpdate(), bool_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setDdnsOverrideClientUpdate(bool_unspec);
        EXPECT_FALSE(pool->hasDdnsParameters());

        util::Optional<D2ClientConfig::ReplaceClientNameMode> mode_unspec;
        util::Optional<D2ClientConfig::ReplaceClientNameMode>
            mode_spec(D2ClientConfig::RCM_WHEN_PRESENT);

        pool->setDdnsReplaceClientNameMode(mode_spec);
        EXPECT_EQ(pool->getDdnsReplaceClientNameMode(), mode_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setDdnsReplaceClientNameMode(mode_unspec);
        EXPECT_FALSE(pool->hasDdnsParameters());

        util::Optional<std::string> string_unspec;
        util::Optional<std::string> string_spec("some_string");

        pool->setDdnsGeneratedPrefix(string_spec);
        EXPECT_EQ(pool->getDdnsGeneratedPrefix(), string_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setDdnsGeneratedPrefix(string_unspec);
        EXPECT_FALSE(pool->hasDdnsParameters());

        pool->setDdnsQualifyingSuffix(string_spec);
        EXPECT_EQ(pool->getDdnsQualifyingSuffix(), string_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setDdnsQualifyingSuffix(string_unspec);
        EXPECT_FALSE(pool->hasDdnsParameters());

        pool->setDdnsUpdateOnRenew(bool_spec);
        EXPECT_EQ(pool->getDdnsUpdateOnRenew(), bool_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setDdnsUpdateOnRenew(bool_unspec);
        EXPECT_FALSE(pool->hasDdnsParameters());

        pool->setDdnsConflictResolutionMode(string_spec);
        EXPECT_EQ(pool->getDdnsConflictResolutionMode(), string_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setDdnsConflictResolutionMode(string_unspec);

        util::Optional<double> double_unspec;
        util::Optional<double> double_spec(0.5);

        pool->setDdnsTtlPercent(double_spec);
        EXPECT_EQ(pool->getDdnsTtlPercent(), double_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setDdnsTtlPercent(double_unspec);
        EXPECT_FALSE(pool->hasDdnsParameters());

        util::Optional<uint32_t> int_unspec;
        util::Optional<uint32_t> int_spec(750);

        pool->setDdnsTtl(int_spec);
        EXPECT_EQ(pool->getDdnsTtl(), int_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setDdnsTtl(int_unspec);
        EXPECT_FALSE(pool->hasDdnsParameters());

        pool->setDdnsTtlMin(int_spec);
        EXPECT_EQ(pool->getDdnsTtlMin(), int_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setDdnsTtlMin(int_unspec);
        EXPECT_FALSE(pool->hasDdnsParameters());

        pool->setDdnsTtlMax(int_spec);
        EXPECT_EQ(pool->getDdnsTtlMax(), int_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setDdnsTtlMax(int_unspec);
        EXPECT_FALSE(pool->hasDdnsParameters());

        pool->setHostnameCharSet(string_spec);
        EXPECT_EQ(pool->getHostnameCharSet(), string_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setHostnameCharSet(string_unspec);
        EXPECT_FALSE(pool->hasDdnsParameters());

        pool->setHostnameCharReplacement(string_spec);
        EXPECT_EQ(pool->getHostnameCharReplacement(), string_spec);
        EXPECT_TRUE(pool->hasDdnsParameters());
        pool->setHostnameCharReplacement(string_unspec);
        EXPECT_FALSE(pool->hasDdnsParameters());
    }
};

TEST(Pool4Test, constructorFirstLast) {

    // let's construct 192.0.2.1-192.0.2.255 pool
    Pool4 pool1(IOAddress("192.0.2.1"), IOAddress("192.0.2.255"));

    EXPECT_EQ(IOAddress("192.0.2.1"), pool1.getFirstAddress());
    EXPECT_EQ(IOAddress("192.0.2.255"), pool1.getLastAddress());

    // This is Pool4, IPv6 addresses do not belong here
    EXPECT_THROW(Pool4(IOAddress("2001:db8::1"),
                       IOAddress("192.168.0.5")), BadValue);
    EXPECT_THROW(Pool4(IOAddress("192.168.0.2"),
                       IOAddress("2001:db8::1")), BadValue);

    // Should throw. Range should be 192.0.2.1-192.0.2.2, not
    // the other way around.
    EXPECT_THROW(Pool4(IOAddress("192.0.2.2"), IOAddress("192.0.2.1")),
                 BadValue);
}

TEST(Pool4Test, constructorPrefixLen) {

    // let's construct 2001:db8:1::/96 pool
    Pool4 pool1(IOAddress("192.0.2.0"), 25);

    EXPECT_EQ("192.0.2.0", pool1.getFirstAddress().toText());
    EXPECT_EQ("192.0.2.127", pool1.getLastAddress().toText());

    // No such thing as /33 prefix
    EXPECT_THROW(Pool4(IOAddress("192.0.2.1"), 33), BadValue);

    // /0 prefix does not make sense
    EXPECT_THROW(Pool4(IOAddress("192.0.2.0"), 0), BadValue);

    // This is Pool6, IPv4 addresses do not belong here
    EXPECT_THROW(Pool4(IOAddress("2001:db8::1"), 20), BadValue);
}

TEST(Pool4Test, in_range) {
   Pool4 pool1(IOAddress("192.0.2.10"), IOAddress("192.0.2.20"));

   EXPECT_FALSE(pool1.inRange(IOAddress("192.0.2.0")));
   EXPECT_TRUE(pool1.inRange(IOAddress("192.0.2.10")));
   EXPECT_TRUE(pool1.inRange(IOAddress("192.0.2.17")));
   EXPECT_TRUE(pool1.inRange(IOAddress("192.0.2.20")));
   EXPECT_FALSE(pool1.inRange(IOAddress("192.0.2.21")));
   EXPECT_FALSE(pool1.inRange(IOAddress("192.0.2.255")));
   EXPECT_FALSE(pool1.inRange(IOAddress("255.255.255.255")));
   EXPECT_FALSE(pool1.inRange(IOAddress("0.0.0.0")));
}

// Checks if the number of possible leases in range is reported correctly.
TEST(Pool4Test, leasesCount) {
    Pool4 pool1(IOAddress("192.0.2.10"), IOAddress("192.0.2.20"));
    EXPECT_EQ(11, pool1.getCapacity());

    Pool4 pool2(IOAddress("192.0.2.0"), IOAddress("192.0.2.255"));
    EXPECT_EQ(256, pool2.getCapacity());

    Pool4 pool3(IOAddress("192.168.0.0"), IOAddress("192.168.255.255"));
    EXPECT_EQ(65536, pool3.getCapacity());

    Pool4 pool4(IOAddress("10.0.0.0"), IOAddress("10.255.255.255"));
    EXPECT_EQ(16777216, pool4.getCapacity());
}

// Simple check if toText returns reasonable values
TEST(Pool4Test, toText) {
    Pool4 pool1(IOAddress("192.0.2.7"), IOAddress("192.0.2.17"));
    EXPECT_EQ("type=V4, 192.0.2.7-192.0.2.17", pool1.toText());

    Pool4 pool2(IOAddress("192.0.2.128"), 28);
    EXPECT_EQ("type=V4, 192.0.2.128-192.0.2.143", pool2.toText());

    Pool4 pool3(IOAddress("192.0.2.0"), IOAddress("192.0.2.127"));
    EXPECT_EQ("type=V4, 192.0.2.0-192.0.2.127", pool3.toText());
}

// Simple check if toElement returns reasonable values
TEST(Pool4Test, toElement) {
    Pool4 pool1(IOAddress("192.0.2.7"), IOAddress("192.0.2.17"));
    std::string expected1 = "{"
        " \"pool\": \"192.0.2.7-192.0.2.17\", "
        " \"option-data\": [ ] "
        "}";
    isc::test::runToElementTest<Pool4>(expected1, pool1);

    Pool4 pool2(IOAddress("192.0.2.128"), 28);
    std::string expected2 = "{"
        " \"pool\": \"192.0.2.128/28\", "
        " \"option-data\": [ ] "
        "}";
    isc::test::runToElementTest<Pool4>(expected2, pool2);

    Pool4 pool3(IOAddress("192.0.2.0"), IOAddress("192.0.2.127"));
    pool3.setID(5);
    std::string expected3 = "{"
        " \"pool\": \"192.0.2.0/25\", "
        " \"option-data\": [ ], "
        " \"pool-id\": 5 "
        "}";
    isc::test::runToElementTest<Pool4>(expected3, pool3);

    pool3.setDdnsSendUpdates(true);
    pool3.setDdnsOverrideNoUpdate(true);
    pool3.setDdnsOverrideClientUpdate(true);
    pool3.setDdnsReplaceClientNameMode(D2ClientConfig::RCM_NEVER);
    pool3.setDdnsGeneratedPrefix("prefix");
    pool3.setDdnsQualifyingSuffix("example.com.");
    pool3.setDdnsUpdateOnRenew(false);
    pool3.setDdnsConflictResolutionMode("check-without-dhcid");
    pool3.setDdnsTtlPercent(0.85);
    pool3.setDdnsTtl(400);
    pool3.setDdnsTtlMin(150);
    pool3.setDdnsTtlMax(650);
    pool3.setHostnameCharReplacement("x");
    pool3.setHostnameCharSet("[^A-Z]");

    std::string expected4 = R"(
        {
         "pool": "192.0.2.0/25",
         "option-data": [ ],
         "pool-id": 5,
         "ddns-send-updates": true,
         "ddns-override-no-update": true,
         "ddns-override-client-update": true,
         "ddns-replace-client-name": "never",
         "ddns-generated-prefix": "prefix",
         "ddns-qualifying-suffix": "example.com.",
         "ddns-update-on-renew": false,
         "ddns-conflict-resolution-mode": "check-without-dhcid",
         "ddns-ttl": 400,
         "ddns-ttl-max": 650,
         "ddns-ttl-min": 150,
         "ddns-ttl-percent": 0.85,
         "hostname-char-replacement": "x",
         "hostname-char-set": "[^A-Z]"
        })";

    isc::test::runToElementTest<Pool4>(expected4, pool3);

}

// This test checks that it is possible to specify pool specific options.
TEST(Pool4Test, addOptions) {
    // Create a pool to add options to it.
    Pool4Ptr pool(new Pool4(IOAddress("192.0.2.0"),
                            IOAddress("192.0.2.255")));

    // Differentiate options by their codes (100-109)
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V4, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(pool->getCfgOption()->add(option, false, false,
                                                  "dhcp4"));
    }

    // Add 7 options to another option space. The option codes partially overlap
    // with option codes that we have added to dhcp4 option space.
    for (uint16_t code = 105; code < 112; ++code) {
        OptionPtr option(new Option(Option::V4, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(pool->getCfgOption()->add(option, false, false, "isc"));
    }

    // Get options from the pool and check if all 10 are there.
    OptionContainerPtr options = pool->getCfgOption()->getAll("dhcp4");
    ASSERT_TRUE(options);
    ASSERT_EQ(10, options->size());

    // Validate codes of options added to dhcp4 option space.
    uint16_t expected_code = 100;
    for (auto const& option_desc : *options) {
        ASSERT_TRUE(option_desc.option_);
        EXPECT_EQ(expected_code, option_desc.option_->getType());
        ++expected_code;
    }

    options = pool->getCfgOption()->getAll("isc");
    ASSERT_TRUE(options);
    ASSERT_EQ(7, options->size());

    // Validate codes of options added to isc option space.
    expected_code = 105;
    for (auto const& option_desc : *options) {
        ASSERT_TRUE(option_desc.option_);
        EXPECT_EQ(expected_code, option_desc.option_->getType());
        ++expected_code;
    }

    // Try to get options from a non-existing option space.
    options = pool->getCfgOption()->getAll("abcd");
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());
}

// This test checks that handling for user-context is valid.
TEST(Pool4Test, userContext) {
    // Create a pool to add options to it.
    Pool4Ptr pool(new Pool4(IOAddress("192.0.2.0"),
                            IOAddress("192.0.2.255")));

    // Context should be empty until explicitly set.
    EXPECT_FALSE(pool->getContext());

    // When set, should be returned properly.
    ElementPtr ctx = Element::create("{ \"comment\": \"foo\" }");
    EXPECT_NO_THROW(pool->setContext(ctx));
    ASSERT_TRUE(pool->getContext());
    EXPECT_EQ(ctx->str(), pool->getContext()->str());
}

// This test checks that handling for client-classes is valid.
TEST(Pool4Test, clientClasses) {
    // Create a pool.
    Pool4Ptr pool(new Pool4(IOAddress("192.0.2.0"),
                            IOAddress("192.0.2.255")));

    // This client does not belong to any class.
    isc::dhcp::ClientClasses no_class;

    // This client belongs to foo only.
    isc::dhcp::ClientClasses foo_class;
    foo_class.insert("foo");

    // This client belongs to bar only. I like that client.
    isc::dhcp::ClientClasses bar_class;
    bar_class.insert("bar");

    // This client belongs to foo, bar and baz classes.
    isc::dhcp::ClientClasses three_classes;
    three_classes.insert("foo");
    three_classes.insert("bar");
    three_classes.insert("baz");

    // No class restrictions defined, any client should be supported
    EXPECT_TRUE(pool->getClientClasses().empty());
    EXPECT_TRUE(pool->clientSupported(no_class));
    EXPECT_TRUE(pool->clientSupported(foo_class));
    EXPECT_TRUE(pool->clientSupported(bar_class));
    EXPECT_TRUE(pool->clientSupported(three_classes));

    // Let's allow only clients belonging to "bar" class.
    pool->allowClientClass("bar");
    EXPECT_TRUE(pool->getClientClasses().contains("bar"));

    EXPECT_FALSE(pool->clientSupported(no_class));
    EXPECT_FALSE(pool->clientSupported(foo_class));
    EXPECT_TRUE(pool->clientSupported(bar_class));
    EXPECT_TRUE(pool->clientSupported(three_classes));
}

// This test checks that handling for evaluate-additional-classes is valid.
TEST(Pool4Test, additionalClasses) {
    // Create a pool.
    Pool4Ptr pool(new Pool4(IOAddress("192.0.2.0"),
                            IOAddress("192.0.2.255")));

    // This client starts with no additional classes.
    EXPECT_TRUE(pool->getAdditionalClasses().empty());

    // Add the first class
    pool->addAdditionalClass("router");
    EXPECT_EQ(1, pool->getAdditionalClasses().size());

    // Add a second class
    pool->addAdditionalClass("modem");
    EXPECT_EQ(2, pool->getAdditionalClasses().size());
    EXPECT_TRUE(pool->getAdditionalClasses().contains("router"));
    EXPECT_TRUE(pool->getAdditionalClasses().contains("modem"));
    EXPECT_FALSE(pool->getAdditionalClasses().contains("foo"));

    // Check that it's ok to add the same class repeatedly
    EXPECT_NO_THROW(pool->addAdditionalClass("foo"));
    EXPECT_NO_THROW(pool->addAdditionalClass("foo"));
    EXPECT_NO_THROW(pool->addAdditionalClass("foo"));

    // Check that 'foo' is marked for additional evaluation
    EXPECT_TRUE(pool->getAdditionalClasses().contains("foo"));
}

TEST(Pool6Test, constructorFirstLast) {

    // let's construct 2001:db8:1:: - 2001:db8:1::ffff:ffff:ffff:ffff pool
    Pool6 pool1(Lease::TYPE_NA, IOAddress("2001:db8:1::"),
                IOAddress("2001:db8:1::ffff:ffff:ffff:ffff"));

    EXPECT_EQ(Lease::TYPE_NA, pool1.getType());
    EXPECT_EQ(IOAddress("2001:db8:1::"), pool1.getFirstAddress());
    EXPECT_EQ(IOAddress("2001:db8:1::ffff:ffff:ffff:ffff"),
              pool1.getLastAddress());

    // This is Pool6, IPv4 addresses do not belong here
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("2001:db8::1"),
                       IOAddress("192.168.0.5")), BadValue);
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("192.168.0.2"),
                       IOAddress("2001:db8::1")), BadValue);

    // Should throw. Range should be 2001:db8::1 - 2001:db8::2, not
    // the other way around.
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("2001:db8::2"),
                       IOAddress("2001:db8::1")), BadValue);
}

TEST(Pool6Test, constructorPrefixLen) {

    // let's construct 2001:db8:1::/96 pool
    Pool6 pool1(Lease::TYPE_NA, IOAddress("2001:db8:1::"), 96);

    EXPECT_EQ(Lease::TYPE_NA, pool1.getType());
    EXPECT_EQ("2001:db8:1::", pool1.getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff", pool1.getLastAddress().toText());

    // No such thing as /130 prefix
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("2001:db8::"), 130),
                 BadValue);

    // /0 prefix does not make sense
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("2001:db8::"), 0),
                 BadValue);

    // This is Pool6, IPv4 addresses do not belong here
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("192.168.0.2"), 96),
                 BadValue);

    // Delegated prefix length for addresses must be /128
    EXPECT_THROW(Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::"), 96, 125),
                 BadValue);
}

TEST(Pool6Test, inRange) {
   Pool6 pool1(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
               IOAddress("2001:db8:1::f"));

   EXPECT_FALSE(pool1.inRange(IOAddress("2001:db8:1::")));
   EXPECT_TRUE(pool1.inRange(IOAddress("2001:db8:1::1")));
   EXPECT_TRUE(pool1.inRange(IOAddress("2001:db8:1::7")));
   EXPECT_TRUE(pool1.inRange(IOAddress("2001:db8:1::f")));
   EXPECT_FALSE(pool1.inRange(IOAddress("2001:db8:1::10")));
   EXPECT_FALSE(pool1.inRange(IOAddress("::")));
}

// Checks that Prefix Delegation pools are handled properly
TEST(Pool6Test, PD) {

    // Let's construct 2001:db8:1::/96 PD pool, split into /112 prefixes
    Pool6 pool1(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 96, 112);

    EXPECT_EQ(Lease::TYPE_PD, pool1.getType());
    EXPECT_EQ(112, pool1.getLength());
    EXPECT_EQ("2001:db8:1::", pool1.getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff", pool1.getLastAddress().toText());

    // Check that it's not possible to have min-max range for PD
    EXPECT_THROW(Pool6 pool2(Lease::TYPE_PD, IOAddress("2001:db8:1::1"),
                             IOAddress("2001:db8:1::f")), BadValue);

    // Check that it's not allowed to specify bigger prefix address than the
    // pool prefix length
    // Should not be able to compute prefix if first address is not starting
    // from prefix length 32 (2001:db8::)
    EXPECT_THROW(Pool6 pool3(Lease::TYPE_PD, IOAddress("2001:db8:1::"),
                             32, 56), BadValue);

    // Check that it's not allowed to delegate bigger prefix than the pool
    // Let's try to split /64 prefix into /56 chunks (should be impossible)
    EXPECT_THROW(Pool6 pool4(Lease::TYPE_PD, IOAddress("2001:db8:1::"),
                             64, 56), BadValue);

    // It should be possible to have a pool split into just a single chunk
    // Let's try to split 2001:db8:1::/77 into a single /77 delegated prefix
    EXPECT_NO_THROW(Pool6 pool5(Lease::TYPE_PD, IOAddress("2001:db8:1::"),
                                77, 77));
}

// Checks that prefix pools with excluded prefixes are handled properly.
TEST(Pool6Test, PDExclude) {
    Pool6Ptr pool;

    // Create a pool with a good excluded prefix. The good excluded prefix
    // is the one for which is a sub-prefix of the main prefix.
    ASSERT_NO_THROW(pool.reset(new Pool6(IOAddress("2001:db8:1::"), 96, 112,
                                         IOAddress("2001:db8:1::2000"), 120)));

    // Verify pool properties.
    EXPECT_EQ(Lease::TYPE_PD, pool->getType());
    EXPECT_EQ(112, pool->getLength());
    EXPECT_EQ("2001:db8:1::", pool->getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff", pool->getLastAddress().toText());

    // It should include Prefix Exclude option.
    Option6PDExcludePtr pd_exclude_option = pool->getPrefixExcludeOption();
    ASSERT_TRUE(pd_exclude_option);
    EXPECT_EQ("2001:db8:1::2:2000", pd_exclude_option->
              getExcludedPrefix(IOAddress("2001:db8:1:0:0:0:2::"), 112).toText());
    EXPECT_EQ(120, static_cast<unsigned>(pd_exclude_option->getExcludedPrefixLength()));

    // Create another pool instance, but with the excluded prefix being
    // "unspecified".
    ASSERT_NO_THROW(pool.reset(new Pool6(IOAddress("2001:db8:1::"), 96, 112,
                                         IOAddress::IPV6_ZERO_ADDRESS(), 0)));

    EXPECT_EQ(Lease::TYPE_PD, pool->getType());
    EXPECT_EQ(112, pool->getLength());
    EXPECT_EQ("2001:db8:1::", pool->getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff", pool->getLastAddress().toText());

    ASSERT_FALSE(pool->getPrefixExcludeOption());

    // Excluded prefix length must be greater than the main prefix length.
    EXPECT_THROW(Pool6(IOAddress("2001:db8:1::"), 96, 112,
                       IOAddress("2001:db8:1::"), 112),
                 BadValue);

    // Again, the excluded prefix length must be greater than main prefix
    // length.
    EXPECT_THROW(Pool6(IOAddress("2001:db8:1::"), 96, 112,
                       IOAddress("2001:db8:1::"), 104),
                 BadValue);

    // The "unspecified" excluded prefix must have both values set to 0.
    EXPECT_THROW(Pool6(IOAddress("2001:db8:1::"), 48, 64,
                       IOAddress("2001:db8:1::"), 0),
                 BadValue);

    // Similar case as above, but the prefix value is 0 and the length
    // is non zero.
    EXPECT_THROW(Pool6(IOAddress("2001:db8:1::"), 48, 64,
                       IOAddress::IPV6_ZERO_ADDRESS(), 72),
                 BadValue);

    // Excluded prefix must be an IPv6 prefix.
    EXPECT_THROW(Pool6(IOAddress("100::"), 8, 16,
                       IOAddress("10.0.0.0"), 24),
                 BadValue);

    // Excluded prefix length must not be greater than 128.
    EXPECT_THROW(Pool6(IOAddress("2001:db8:1::"), 48, 64,
                       IOAddress("2001:db8:1::"), 129),
                 BadValue);
}

// Checks that temporary address pools are handled properly
TEST(Pool6Test, TA) {
    // Note: since we defined TA pool types during PD work, we can test it
    // now. Although the configuration to take advantage of it is not
    // planned for now, we will support it some day.

    // Let's construct 2001:db8:1::/96 temporary addresses
    Pool6Ptr pool1;
    EXPECT_NO_THROW(pool1.reset(new Pool6(Lease::TYPE_TA,
                                          IOAddress("2001:db8:1::"), 96)));

    // Check that TA range can be only defined for single addresses
    EXPECT_THROW(Pool6(Lease::TYPE_TA, IOAddress("2001:db8:1::"), 96, 127),
                 BadValue);

    ASSERT_TRUE(pool1);
    EXPECT_EQ(Lease::TYPE_TA, pool1->getType());
    EXPECT_EQ(128, pool1->getLength()); // singular addresses, not prefixes
    EXPECT_EQ("2001:db8:1::", pool1->getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff", pool1->getLastAddress().toText());

    // Check that it's possible to have min-max range for TA
    Pool6Ptr pool2;
    EXPECT_NO_THROW(pool2.reset(new Pool6(Lease::TYPE_TA,
                                          IOAddress("2001:db8:1::1"),
                                          IOAddress("2001:db8:1::f"))));
    ASSERT_TRUE(pool2);
    EXPECT_EQ(Lease::TYPE_TA, pool2->getType());
    EXPECT_EQ(128, pool2->getLength()); // singular addresses, not prefixes
    EXPECT_EQ("2001:db8:1::1", pool2->getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::f", pool2->getLastAddress().toText());
}

// Simple check if toText returns reasonable values
TEST(Pool6Test, toText) {
    Pool6 pool1(Lease::TYPE_NA, IOAddress("2001:db8::1"),
                IOAddress("2001:db8::2"));
    EXPECT_EQ("type=IA_NA, 2001:db8::1-2001:db8::2, delegated_len=128",
              pool1.toText());

    Pool6 pool2(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 96, 112);
    EXPECT_EQ("type=IA_PD, 2001:db8:1::-2001:db8:1::ffff:ffff, delegated_len=112",
              pool2.toText());

    Pool6 pool3(IOAddress("2001:db8:1::"), 96, 112,
                IOAddress("2001:db8:1::1000"), 120);
    EXPECT_EQ("type=IA_PD, 2001:db8:1::-2001:db8:1::ffff:ffff, delegated_len=112,"
              " excluded_prefix=2001:db8:1::1000/120",
              pool3.toText());

    Pool6 pool4(Lease::TYPE_NA, IOAddress("2001:db8::"),
                IOAddress("2001:db8::ffff"));
    EXPECT_EQ("type=IA_NA, 2001:db8::-2001:db8::ffff, delegated_len=128",
              pool4.toText());
}

// Simple check if toElement returns reasonable values
TEST(Pool6Test, toElement) {
    Pool6 pool1(Lease::TYPE_NA, IOAddress("2001:db8::1"),
                IOAddress("2001:db8::2"));
    std::string expected1 = "{"
        " \"pool\": \"2001:db8::1-2001:db8::2\", "
        " \"option-data\": [ ] "
        "}";
    isc::test::runToElementTest<Pool6>(expected1, pool1);

    Pool6 pool2(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 96, 112);
    std::string expected2 = "{"
        " \"prefix\": \"2001:db8:1::\", "
        " \"prefix-len\": 96, "
        " \"delegated-len\": 112, "
        " \"option-data\": [ ] "
        "}";
    isc::test::runToElementTest<Pool6>(expected2, pool2);

    Pool6 pool3(IOAddress("2001:db8:1::"), 96, 112,
                IOAddress("2001:db8:1::1000"), 120);
    std::string expected3 = "{"
        " \"prefix\": \"2001:db8:1::\", "
        " \"prefix-len\": 96, "
        " \"delegated-len\": 112, "
        " \"excluded-prefix\": \"2001:db8:1::1000\", "
        " \"excluded-prefix-len\": 120, "
        " \"option-data\": [ ] "
        "}";
    isc::test::runToElementTest<Pool6>(expected3, pool3);

    Pool6 pool4(Lease::TYPE_NA, IOAddress("2001:db8::"),
                IOAddress("2001:db8::ffff"));
    pool4.setID(5);
    std::string expected4 = "{"
        " \"pool\": \"2001:db8::/112\", "
        " \"option-data\": [ ], "
        " \"pool-id\": 5 "
        "}";
    isc::test::runToElementTest<Pool6>(expected4, pool4);
}

// Checks if the number of possible leases in range is reported correctly.
TEST(Pool6Test, leasesCount) {
    Pool6 pool1(Lease::TYPE_NA, IOAddress("2001:db8::1"),
                IOAddress("2001:db8::2"));
    EXPECT_EQ(2, pool1.getCapacity());

    Pool6 pool2(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 96, 112);
    EXPECT_EQ(65536, pool2.getCapacity());
}

// This test checks that it is possible to specify pool specific options.
TEST(Pool6Test, addOptions) {
    // Create a pool to add options to it.
    Pool6Ptr pool(new Pool6(Lease::TYPE_PD, IOAddress("3000::"), 64, 128));

    // Differentiate options by their codes (100-109)
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(pool->getCfgOption()->add(option, false, false,
                                                  "dhcp6"));
    }

    // Add 7 options to another option space. The option codes partially overlap
    // with option codes that we have added to dhcp6 option space.
    for (uint16_t code = 105; code < 112; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(pool->getCfgOption()->add(option, false, false, "isc"));
    }

    // Get options from the pool and check if all 10 are there.
    OptionContainerPtr options = pool->getCfgOption()->getAll("dhcp6");
    ASSERT_TRUE(options);
    ASSERT_EQ(10, options->size());

    // Validate codes of options added to dhcp6 option space.
    uint16_t expected_code = 100;
    for (auto const& option_desc : *options) {
        ASSERT_TRUE(option_desc.option_);
        EXPECT_EQ(expected_code, option_desc.option_->getType());
        ++expected_code;
    }

    options = pool->getCfgOption()->getAll("isc");
    ASSERT_TRUE(options);
    ASSERT_EQ(7, options->size());

    // Validate codes of options added to isc option space.
    expected_code = 105;
    for (auto const& option_desc : *options) {
        ASSERT_TRUE(option_desc.option_);
        EXPECT_EQ(expected_code, option_desc.option_->getType());
        ++expected_code;
    }

    // Try to get options from a non-existing option space.
    options = pool->getCfgOption()->getAll("abcd");
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());
}

// This test checks that handling for user-context is valid.
TEST(Pool6Test, userContext) {
    // Create a pool to add options to it.
    Pool6 pool(Lease::TYPE_NA, IOAddress("2001:db8::1"),
                IOAddress("2001:db8::2"));

    // Context should be empty until explicitly set.
    EXPECT_FALSE(pool.getContext());

    // When set, should be returned properly.
    ElementPtr ctx = Element::create("{ \"comment\": \"foo\" }");
    EXPECT_NO_THROW(pool.setContext(ctx));
    ASSERT_TRUE(pool.getContext());
    EXPECT_EQ(ctx->str(), pool.getContext()->str());
}

// This test checks that handling for client-class is valid.
TEST(Pool6Test, clientClass) {
    // Create a pool.
    Pool6 pool(Lease::TYPE_NA, IOAddress("2001:db8::1"),
                IOAddress("2001:db8::2"));

    // This client does not belong to any class.
    isc::dhcp::ClientClasses no_class;

    // This client belongs to foo only.
    isc::dhcp::ClientClasses foo_class;
    foo_class.insert("foo");

    // This client belongs to bar only. I like that client.
    isc::dhcp::ClientClasses bar_class;
    bar_class.insert("bar");

    // This client belongs to foo, bar and baz classes.
    isc::dhcp::ClientClasses three_classes;
    three_classes.insert("foo");
    three_classes.insert("bar");
    three_classes.insert("baz");

    // No class restrictions defined, any client should be supported
    EXPECT_TRUE(pool.getClientClasses().empty());
    EXPECT_TRUE(pool.clientSupported(no_class));
    EXPECT_TRUE(pool.clientSupported(foo_class));
    EXPECT_TRUE(pool.clientSupported(bar_class));
    EXPECT_TRUE(pool.clientSupported(three_classes));

    // Let's allow only clients belonging to "bar" class.
    pool.allowClientClass("bar");
    EXPECT_TRUE(pool.getClientClasses().contains("bar"));

    EXPECT_FALSE(pool.clientSupported(no_class));
    EXPECT_FALSE(pool.clientSupported(foo_class));
    EXPECT_TRUE(pool.clientSupported(bar_class));
    EXPECT_TRUE(pool.clientSupported(three_classes));
}

// This test checks that handling for evaluate-additional-classes is valid.
TEST(Pool6Test, additionalClasses) {
    // Create a pool.
    Pool6 pool(Lease::TYPE_NA, IOAddress("2001:db8::1"),
               IOAddress("2001:db8::2"));

    // This client starts with no additional classes.
    EXPECT_TRUE(pool.getAdditionalClasses().empty());

    // Add the first class
    pool.addAdditionalClass("router");
    EXPECT_EQ(1, pool.getAdditionalClasses().size());

    // Add a second class
    pool.addAdditionalClass("modem");
    EXPECT_EQ(2, pool.getAdditionalClasses().size());
    EXPECT_TRUE(pool.getAdditionalClasses().contains("router"));
    EXPECT_TRUE(pool.getAdditionalClasses().contains("modem"));
    EXPECT_FALSE(pool.getAdditionalClasses().contains("foo"));

    // Check that it's ok to add the same class repeatedly
    EXPECT_NO_THROW(pool.addAdditionalClass("foo"));
    EXPECT_NO_THROW(pool.addAdditionalClass("foo"));
    EXPECT_NO_THROW(pool.addAdditionalClass("foo"));

    // Check that 'foo' is marked for additional evaluation
    EXPECT_TRUE(pool.getAdditionalClasses().contains("foo"));
}

TEST_F(PoolTest, ddnsParameters4) {
    checkDdnsParameters(AF_INET);
}

TEST_F(PoolTest, ddnsParameters6) {
    checkDdnsParameters(AF_INET6);
}

}  // end of anonymous namespace
