// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <iostream>
#include <sstream>

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

#include <exceptions/exceptions.h>
#include <asiolink/io_address.h>
#include "dhcp/dhcp4.h"
#include "dhcp/dhcp6.h"
#include "dhcp/option4_addrlst.h"
#include "dhcp/option6_addrlst.h"
#include "dhcp/option6_ia.h"
#include "dhcp/option6_iaaddr.h"
#include "dhcp/option6_int.h"
#include "dhcp/option6_int_array.h"
#include "dhcp/option_definition.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

/// @brief OptionDefinition test class.
///
/// This class does not do anything useful but we keep
/// it around for the future.
class OptionDefinitionTest : public ::testing::Test {
public:
    // @brief Constructor.
    OptionDefinitionTest() { }
};

TEST_F(OptionDefinitionTest, constructor) {
    // Specify the option data type as string. This should get converted
    // to enum value returned by getType().
    OptionDefinition opt_def1("OPTION_CLIENTID", 1, "string");
    EXPECT_EQ("OPTION_CLIENTID", opt_def1.getName());
    EXPECT_EQ(1, opt_def1.getCode());
    EXPECT_EQ(OptionDefinition::STRING_TYPE,  opt_def1.getType());
    EXPECT_FALSE(opt_def1.getArrayType());

    // Specify the option data type as an enum value.
    OptionDefinition opt_def2("OPTION_RAPID_COMMIT", 14,
                              OptionDefinition::EMPTY_TYPE);
    EXPECT_EQ("OPTION_RAPID_COMMIT", opt_def2.getName());
    EXPECT_EQ(14, opt_def2.getCode());
    EXPECT_EQ(OptionDefinition::EMPTY_TYPE, opt_def2.getType());
    EXPECT_FALSE(opt_def2.getArrayType());

    // Check if it is possible to set that option is an array.
    OptionDefinition opt_def3("OPTION_NIS_SERVERS", 27,
                              OptionDefinition::IPV6_ADDRESS_TYPE,
                              true);
    EXPECT_EQ("OPTION_NIS_SERVERS", opt_def3.getName());
    EXPECT_EQ(27, opt_def3.getCode());
    EXPECT_EQ(OptionDefinition::IPV6_ADDRESS_TYPE, opt_def3.getType());
    EXPECT_TRUE(opt_def3.getArrayType());

    // The created object is invalid if invalid data type is specified but
    // constructor shouldn't throw exception. The object is validated after
    // it has been created.
    EXPECT_NO_THROW(
        OptionDefinition opt_def4("OPTION_SERVERID",
                                  OptionDefinition::UNKNOWN_TYPE + 10,
                                  OptionDefinition::STRING_TYPE);
    );
}

TEST_F(OptionDefinitionTest, addRecordField) {
    // We can only add fields to record if the option type has been
    // specified as 'record'. We try all other types but 'record'
    // here and expect exception to be thrown.
    for (int i = 0; i < OptionDefinition::UNKNOWN_TYPE; ++i) {
        // Do not try for 'record' type because this is the only
        // type for which adding record will succeed.
        if (i == OptionDefinition::RECORD_TYPE) {
            continue;
        }
        OptionDefinition opt_def("OPTION_IAADDR", 5,
                                 static_cast<OptionDefinition::DataType>(i));
        EXPECT_THROW(opt_def.addRecordField("uint8"), isc::InvalidOperation);
    }

    // Positive scenario starts here.
    OptionDefinition opt_def("OPTION_IAADDR", 5, "record");
    EXPECT_NO_THROW(opt_def.addRecordField("ipv6-address"));
    EXPECT_NO_THROW(opt_def.addRecordField("uint32"));
    // It should not matter if we specify field type by its name or using enum.
    EXPECT_NO_THROW(opt_def.addRecordField(OptionDefinition::UINT32_TYPE));

    // Check what we have actually added.
    OptionDefinition::RecordFieldsCollection fields = opt_def.getRecordFields();
    ASSERT_EQ(3, fields.size());
    EXPECT_EQ(OptionDefinition::IPV6_ADDRESS_TYPE, fields[0]);
    EXPECT_EQ(OptionDefinition::UINT32_TYPE, fields[1]);
    EXPECT_EQ(OptionDefinition::UINT32_TYPE, fields[2]);

    // Let's try some more negative scenarios: use invalid data types.
    EXPECT_THROW(opt_def.addRecordField("unknown_type_xyz"), isc::BadValue);
    OptionDefinition::DataType invalid_type =
        static_cast<OptionDefinition::DataType>(OptionDefinition::UNKNOWN_TYPE + 10);
    EXPECT_THROW(opt_def.addRecordField(invalid_type), isc::BadValue);
}


TEST_F(OptionDefinitionTest, factoryAddrList6) {
    OptionDefinition opt_def("OPTION_NIS_SERVERS", D6O_NIS_SERVERS,
                             "ipv6-address", true);
    Option::Factory* factory(NULL);
    EXPECT_NO_THROW(factory = opt_def.getFactory());
    ASSERT_TRUE(factory != NULL);

    // Create a list of some V6 addresses.
    std::vector<asiolink::IOAddress> addrs;
    addrs.push_back(asiolink::IOAddress("2001:0db8::ff00:0042:8329"));
    addrs.push_back(asiolink::IOAddress("2001:0db8::ff00:0042:2319"));
    addrs.push_back(asiolink::IOAddress("::1"));
    addrs.push_back(asiolink::IOAddress("::2"));

    // Write addresses to the buffer.
    OptionBuffer buf;
    for (int i = 0; i < addrs.size(); ++i) {
        unsigned char* data = addrs[i].getAddress().to_v6().to_bytes().data();
        // @todo Are there any sanity checks needed here on this raw pointer?
        buf.insert(buf.end(), data, data + asiolink::V6ADDRESS_LEN);
    }
    // Create DHCPv6 option from this buffer. Once option is created it is
    // supposed to have internal list of addresses that it parses out from
    // the provided buffer.
    OptionPtr option_v6;
    ASSERT_NO_THROW(
        option_v6 = factory(Option::V6, D6O_NIS_SERVERS, buf);
    );
    ASSERT_EQ(typeid(*option_v6), typeid(Option6AddrLst));
    boost::shared_ptr<Option6AddrLst> option_cast_v6 =
        boost::static_pointer_cast<Option6AddrLst>(option_v6);
    ASSERT_TRUE(option_cast_v6);
    // Get the list of parsed addresses from the option object.
    std::vector<asiolink::IOAddress> addrs_returned =
        option_cast_v6->getAddresses();
    // The list of addresses must exactly match addresses that we
    // stored in the buffer to create the option from it.
    EXPECT_EQ(addrs, addrs_returned);

    // The provided buffer's length must be a multiple of V6 address length.
    // Let's extend the buffer by one byte so as this condition is not
    // fulfilled anymore.
    buf.insert(buf.end(), 1, 1);
    // It should throw exception then.
    EXPECT_THROW(
        factory(Option::V6, D6O_NIS_SERVERS, buf),
        isc::OutOfRange
    );
}

TEST_F(OptionDefinitionTest, factoryAddrList4) {
    OptionDefinition opt_def("OPTION_NAME_SERVERS", D6O_NIS_SERVERS,
                             "ipv4-address", true);
    Option::Factory* factory(NULL);
    EXPECT_NO_THROW(factory = opt_def.getFactory());
    ASSERT_TRUE(factory != NULL);

    // Create a list of some V6 addresses.
    std::vector<asiolink::IOAddress> addrs;
    addrs.push_back(asiolink::IOAddress("192.168.0.1"));
    addrs.push_back(asiolink::IOAddress("172.16.1.1"));
    addrs.push_back(asiolink::IOAddress("127.0.0.1"));
    addrs.push_back(asiolink::IOAddress("213.41.23.12"));

    // Write addresses to the buffer.
    OptionBuffer buf;
    for (int i = 0; i < addrs.size(); ++i) {
        unsigned char* data = addrs[i].getAddress().to_v4().to_bytes().data();
        // @todo Are there any sanity checks needed here on this raw pointer?
        buf.insert(buf.end(), data, data + asiolink::V4ADDRESS_LEN);
    }
    // Create DHCPv6 option from this buffer. Once option is created it is
    // supposed to have internal list of addresses that it parses out from
    // the provided buffer.
    OptionPtr option_v4;
    ASSERT_NO_THROW(
        option_v4 = factory(Option::V4, DHO_NAME_SERVERS, buf)
    );
    ASSERT_EQ(typeid(*option_v4), typeid(Option4AddrLst));
    // Get the list of parsed addresses from the option object.
    boost::shared_ptr<Option4AddrLst> option_cast_v4 =
        boost::static_pointer_cast<Option4AddrLst>(option_v4);
    std::vector<asiolink::IOAddress> addrs_returned =
        option_cast_v4->getAddresses();
    // The list of addresses must exactly match addresses that we
    // stored in the buffer to create the option from it.
    EXPECT_EQ(addrs, addrs_returned);

    // The provided buffer's length must be a multiple of V4 address length.
    // Let's extend the buffer by one byte so as this condition is not
    // fulfilled anymore.
    buf.insert(buf.end(), 1, 1);
    // It should throw exception then.
    EXPECT_THROW(factory(Option::V4, DHO_NIS_SERVERS, buf), isc::OutOfRange);
}

TEST_F(OptionDefinitionTest, factoryEmpty) {
    OptionDefinition opt_def("OPTION_RAPID_COMMIT", D6O_RAPID_COMMIT, "empty");
    Option::Factory* factory(NULL);
    EXPECT_NO_THROW(factory = opt_def.getFactory());
    ASSERT_TRUE(factory != NULL);

    // Create option instance and provide empty buffer as expected.
    OptionPtr option_v6;
    ASSERT_NO_THROW(
        option_v6 = factory(Option::V6, D6O_RAPID_COMMIT, OptionBuffer())
    );
    ASSERT_EQ(typeid(*option_v6), typeid(Option));
    // Expect 'empty' DHCPv6 option.
    EXPECT_EQ(Option::V6, option_v6->getUniverse());
    EXPECT_EQ(4, option_v6->getHeaderLen());
    EXPECT_EQ(0, option_v6->getData().size());

    // Repeat the same test scenario for DHCPv4 option.
    EXPECT_THROW(factory(Option::V4, 214, OptionBuffer(2)),isc::BadValue);

    OptionPtr option_v4;
    ASSERT_NO_THROW(option_v4 = factory(Option::V4, 214, OptionBuffer()));
    // Expect 'empty' DHCPv4 option.
    EXPECT_EQ(Option::V4, option_v4->getUniverse());
    EXPECT_EQ(2, option_v4->getHeaderLen());
    EXPECT_EQ(0, option_v4->getData().size());

    // This factory produces empty option (consisting of option type
    // and length). Attempt to provide some data in the buffer should
    // result in exception.
    EXPECT_THROW(factory(Option::V6, D6O_RAPID_COMMIT,OptionBuffer(2)),isc::BadValue);
}

TEST_F(OptionDefinitionTest, factoryIA6) {
    // This option consists of IAID, T1 and T2 fields (each 4 bytes long).
    const int option6_ia_len = 12;

    // Get the factory function pointer.
    OptionDefinition opt_def("OPTION_IA_NA", D6O_IA_NA, "record", true);
    // Each data field is uint32.
    for (int i = 0; i < 3; ++i) {
        EXPECT_NO_THROW(opt_def.addRecordField("uint32"));
    }
    Option::Factory* factory(NULL);
    EXPECT_NO_THROW(factory = opt_def.getFactory());
    ASSERT_TRUE(factory != NULL);

    // Check the positive scenario.
    OptionBuffer buf(12);
    for (int i = 0; i < buf.size(); ++i) {
        buf[i] = i;
    }
    OptionPtr option_v6;
    ASSERT_NO_THROW(option_v6 = factory(Option::V6, D6O_IA_NA, buf));
    ASSERT_EQ(typeid(*option_v6), typeid(Option6IA));
    boost::shared_ptr<Option6IA> option_cast_v6 =
        boost::static_pointer_cast<Option6IA>(option_v6);
    EXPECT_EQ(0x00010203, option_cast_v6->getIAID());
    EXPECT_EQ(0x04050607, option_cast_v6->getT1());
    EXPECT_EQ(0x08090A0B, option_cast_v6->getT2());

    // This should work for DHCPv6 only, try passing invalid universe value.
    EXPECT_THROW(
        factory(Option::V4, D6O_IA_NA, OptionBuffer(option6_ia_len)),
        isc::BadValue
    );
    // The length of the buffer must be 12 bytes.
    // Check too short buffer.
    EXPECT_THROW(
        factory(Option::V6, D6O_IA_NA, OptionBuffer(option6_ia_len - 1)),
        isc::OutOfRange
     );
    // Check too long buffer.
    EXPECT_THROW(
        factory(Option::V6, D6O_IA_NA, OptionBuffer(option6_ia_len + 1)),
        isc::OutOfRange
    );
}

TEST_F(OptionDefinitionTest, factoryIAAddr6) {
    // This option consists of IPV6 Address (16 bytes) and preferred-lifetime and
    // valid-lifetime fields (each 4 bytes long).
    const int option6_iaaddr_len = 24;

    OptionDefinition opt_def("OPTION_IAADDR", D6O_IAADDR, "record");
    ASSERT_NO_THROW(opt_def.addRecordField("ipv6-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("uint32"));
    ASSERT_NO_THROW(opt_def.addRecordField("uint32"));
    Option::Factory* factory(NULL);
    EXPECT_NO_THROW(factory = opt_def.getFactory());
    ASSERT_TRUE(factory != NULL);

    // Check the positive scenario.
    OptionPtr option_v6;
    asiolink::IOAddress addr_v6("2001:0db8::ff00:0042:8329");
    ASSERT_TRUE(addr_v6.getAddress().is_v6());
    unsigned char* addr_bytes_v6 = addr_v6.getAddress().to_v6().to_bytes().data();
    ASSERT_TRUE(addr_bytes_v6 != NULL);
    OptionBuffer buf;
    buf.insert(buf.end(), addr_bytes_v6, addr_bytes_v6 + asiolink::V6ADDRESS_LEN);
    for (int i = 0; i < option6_iaaddr_len - asiolink::V6ADDRESS_LEN; ++i) {
        buf.push_back(i);
    }
    //    ASSERT_NO_THROW(option_v6 = factory(Option::V6, D6O_IAADDR, buf));
    try {
        option_v6 = factory(Option::V6, D6O_IAADDR, buf);
    } catch (const Exception& e) {
        std::cout << e.what() << std::endl;
    }
    ASSERT_EQ(typeid(*option_v6), typeid(Option6IAAddr));
    boost::shared_ptr<Option6IAAddr> option_cast_v6 =
        boost::static_pointer_cast<Option6IAAddr>(option_v6);
    EXPECT_EQ(addr_v6, option_cast_v6->getAddress());
    EXPECT_EQ(0x00010203, option_cast_v6->getPreferred());
    EXPECT_EQ(0x04050607, option_cast_v6->getValid());

    // This should work for DHCPv6 only, try passing invalid universe value.
    EXPECT_THROW(
        factory(Option::V4, D6O_IAADDR, OptionBuffer(option6_iaaddr_len)),
        isc::BadValue
    );
    // The length of the buffer must be 12 bytes.
    // Check too short buffer.
    EXPECT_THROW(
        factory(Option::V6, D6O_IAADDR, OptionBuffer(option6_iaaddr_len - 1)),
        isc::OutOfRange
     );
    // Check too long buffer.
    EXPECT_THROW(
        factory(Option::V6, D6O_IAADDR, OptionBuffer(option6_iaaddr_len + 1)),
        isc::OutOfRange
    );
}

TEST_F(OptionDefinitionTest, factoryIntegerInvalidType) {
    // The template function factoryInteger<> accepts integer values only
    // as template typename. Here we try passing different type and
    // see if it rejects it.
    EXPECT_THROW(
        OptionDefinition::factoryInteger<bool>(Option::V6, D6O_PREFERENCE, OptionBuffer(1)),
        isc::dhcp::InvalidDataType
    );
}

TEST_F(OptionDefinitionTest, factoryUint8) {
    OptionDefinition opt_def("OPTION_PREFERENCE", D6O_PREFERENCE, "uint8");
    Option::Factory* factory(NULL);
    EXPECT_NO_THROW(factory = opt_def.getFactory());
    ASSERT_TRUE(factory != NULL);

    OptionPtr option_v6;
    // Try to use correct buffer length = 1 byte.
    ASSERT_NO_THROW(
        option_v6 = factory(Option::V6, D6O_PREFERENCE, OptionBuffer(1, 1));
    );
    ASSERT_EQ(typeid(*option_v6), typeid(Option6Int<uint8_t>));    // Validate the value.
    boost::shared_ptr<Option6Int<uint8_t> > option_cast_v6 =
        boost::static_pointer_cast<Option6Int<uint8_t> >(option_v6);
    EXPECT_EQ(1, option_cast_v6->getValue());

    // Try to provide too large buffer. Expect exception.
    EXPECT_THROW(
        option_v6 = factory(Option::V6, D6O_PREFERENCE, OptionBuffer(3)),
        isc::OutOfRange
    );

    // Try to provide zero-length buffer. Expect exception.
    EXPECT_THROW(
        option_v6 = factory(Option::V6, D6O_PREFERENCE, OptionBuffer()),
        isc::OutOfRange
    );

    // @todo Add more cases for DHCPv4
}

TEST_F(OptionDefinitionTest, factoryUint16) {
    OptionDefinition opt_def("OPTION_ELAPSED_TIME", D6O_ELAPSED_TIME, "uint16");
    Option::Factory* factory(NULL);
    EXPECT_NO_THROW(factory = opt_def.getFactory());
    ASSERT_TRUE(factory != NULL);

    OptionPtr option_v6;
    // Try to use correct buffer length = 2 bytes.
    OptionBuffer buf;
    buf.push_back(1);
    buf.push_back(2);
    ASSERT_NO_THROW(
        option_v6 = factory(Option::V6, D6O_ELAPSED_TIME, buf);
    );
    ASSERT_EQ(typeid(*option_v6), typeid(Option6Int<uint16_t>));
    // Validate the value.
    boost::shared_ptr<Option6Int<uint16_t> > option_cast_v6 =
        boost::static_pointer_cast<Option6Int<uint16_t> >(option_v6);
    EXPECT_EQ(0x0102, option_cast_v6->getValue());

    // Try to provide too large buffer. Expect exception.
    EXPECT_THROW(
        option_v6 = factory(Option::V6, D6O_ELAPSED_TIME, OptionBuffer(3)),
        isc::OutOfRange
    );
    // Try to provide zero-length buffer. Expect exception.
    EXPECT_THROW(
        option_v6 = factory(Option::V6, D6O_ELAPSED_TIME, OptionBuffer(1)),
        isc::OutOfRange
    );

    // @todo Add more cases for DHCPv4
}

TEST_F(OptionDefinitionTest, factoryUint32) {
    OptionDefinition opt_def("OPTION_CLT_TIME", D6O_CLT_TIME, "uint32");
    Option::Factory* factory(NULL);
    EXPECT_NO_THROW(factory = opt_def.getFactory());
    ASSERT_TRUE(factory != NULL);

    OptionPtr option_v6;
    OptionBuffer buf;
    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);
    buf.push_back(4);
    ASSERT_NO_THROW(
        option_v6 = factory(Option::V6, D6O_CLT_TIME, buf);
    );
    ASSERT_EQ(typeid(*option_v6), typeid(Option6Int<uint32_t>));
    // Validate the value.
    boost::shared_ptr<Option6Int<uint32_t> > option_cast_v6 =
        boost::static_pointer_cast<Option6Int<uint32_t> >(option_v6);
    EXPECT_EQ(0x01020304, option_cast_v6->getValue());

    // Try to provide too large buffer. Expect exception.
    EXPECT_THROW(
        option_v6 = factory(Option::V6, D6O_CLT_TIME, OptionBuffer(5)),
        isc::OutOfRange
    );
    // Try to provide zero-length buffer. Expect exception.
    EXPECT_THROW(
        option_v6 = factory(Option::V6, D6O_CLT_TIME, OptionBuffer(2)),
        isc::OutOfRange
    );

    // @todo Add more cases for DHCPv4
}

TEST_F(OptionDefinitionTest, factoryUint16Array) {
    // Let's define some dummy option.
    const uint16_t opt_code = 79;
    OptionDefinition opt_def("OPTION_UINT16_ARRAY", opt_code, "uint16", true);
    Option::Factory* factory(NULL);
    EXPECT_NO_THROW(factory = opt_def.getFactory());
    ASSERT_TRUE(factory != NULL);

    OptionPtr option_v6;
    // Positive scenario, initiate the buffer with length being
    // multiple of uint16_t size.
    // buffer elements will be: 0x112233.
    OptionBuffer buf(6);
    for (int i = 0; i < 6; ++i) {
        buf[i] = i / 2;
    }
    // Constructor should succeed because buffer has correct size.
    EXPECT_NO_THROW(
        option_v6 = factory(Option::V6, opt_code, buf);
    );
    ASSERT_EQ(typeid(*option_v6), typeid(Option6IntArray<uint16_t>));
    boost::shared_ptr<Option6IntArray<uint16_t> > option_cast_v6 =
        boost::static_pointer_cast<Option6IntArray<uint16_t> >(option_v6);
    // Get the values from the initiated options and validate.
    Option6IntArray<uint16_t>::ValuesCollection values =
        option_cast_v6->getValues();
    for (int i = 0; i < values.size(); ++i) {
        // Expected value is calculated using on the same pattern
        // as the one we used to initiate buffer:
        // for i=0, expected = 0x00, for i = 1, expected == 0x11 etc.
        uint16_t expected = (i << 8) | i;
        EXPECT_EQ(expected, values[i]);
    }

    // Provided buffer size must be greater than zero. Check if we
    // get exception if we provide zero-length buffer.
    EXPECT_THROW(
        option_v6 = factory(Option::V6, opt_code, OptionBuffer()),
        isc::OutOfRange
    );
    // Buffer length must be multiple of data type size.
    EXPECT_THROW(
        option_v6 = factory(Option::V6, opt_code, OptionBuffer(5)),
        isc::OutOfRange
    );
}

TEST_F(OptionDefinitionTest, factoryUint32Array) {
    // Let's define some dummy option.
    const uint16_t opt_code = 80;

    OptionDefinition opt_def("OPTION_UINT32_ARRAY", opt_code, "uint32", true);
    Option::Factory* factory(NULL);
    EXPECT_NO_THROW(factory = opt_def.getFactory());
    ASSERT_TRUE(factory != NULL);

    OptionPtr option_v6;
    // Positive scenario, initiate the buffer with length being
    // multiple of uint16_t size.
    // buffer elements will be: 0x111122223333.
    OptionBuffer buf(12);
    for (int i = 0; i < buf.size(); ++i) {
        buf[i] = i / 4;
    }
    // Constructor should succeed because buffer has correct size.
    EXPECT_NO_THROW(
        option_v6 = factory(Option::V6, opt_code, buf);
    );
    ASSERT_EQ(typeid(*option_v6), typeid(Option6IntArray<uint32_t>));
    boost::shared_ptr<Option6IntArray<uint32_t> > option_cast_v6 =
        boost::static_pointer_cast<Option6IntArray<uint32_t> >(option_v6);
    // Get the values from the initiated options and validate.
    Option6IntArray<uint32_t>::ValuesCollection values =
        option_cast_v6->getValues();
    for (int i = 0; i < values.size(); ++i) {
        // Expected value is calculated using on the same pattern
        // as the one we used to initiate buffer:
        // for i=0, expected = 0x0000, for i = 1, expected == 0x1111 etc.
        uint32_t expected = 0x01010101 * i;
        EXPECT_EQ(expected, values[i]);
    }

    // Provided buffer size must be greater than zero. Check if we
    // get exception if we provide zero-length buffer.
    EXPECT_THROW(
        option_v6 = factory(Option::V6, opt_code, OptionBuffer()),
        isc::OutOfRange
    );
    // Buffer length must be multiple of data type size.
    EXPECT_THROW(
        option_v6 = factory(Option::V6, opt_code, OptionBuffer(5)),
        isc::OutOfRange
    );
}


} // anonymous namespace
