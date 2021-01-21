// Copyright (C) 2016-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/opaque_data_tuple.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_opaque_data_tuples.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_vendor_class.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option4_client_fqdn.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/option6_status_code.h>
#include <util/buffer.h>

#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

/// @brief Type of the "copy" operation to be performed in a test.
///
/// Possible operations are:
/// - copy construction,
/// - cloning with Option::clone,
/// - assignment.
enum OpType {
    COPY,
    CLONE,
    ASSIGN
};

/// @brief Generic test for deep copy of an option.
///
/// This test can use one of the three supported operations to deep copy
/// an option: copy construction, cloning or assignment.
///
/// After copying the option the following parameters checked if they
/// have been copied (copied by the Option class):
/// - universe,
/// - option type,
/// - encapsulated space,
/// - data.
///
/// This test also checks that the sub options have been copied by checking
/// that:
/// - options' types match,
/// - binary representations are equal,
/// - pointers to the options are unequal (to make sure that the option has
///   been copied, rather than the pointer).
///
/// @param op_type Copy operation to be performed.
/// @param option Source option.
/// @param option_copy Destination option. Note that this option may be
/// initially set to a non-null value. For the "copy" and "clone" operations
/// the pointer will be reset, so there is no sense to initialize this
/// object to a non-null value. However, for the assignment testing it is
/// recommended to initialize the option_copy to point to an option having
/// different parameters to verify that all parameters have been overridden
/// by the assignment operation.
template<typename OptionType>
void testCopyAssign(const OpType& op_type,
                    boost::shared_ptr<OptionType>& option,
                    boost::shared_ptr<OptionType>& option_copy) {
    // Set the encapsulated to 'foo' because tests usually don't set that
    // value.
    option->setEncapsulatedSpace("foo");

    // Create two sub options of different types to later check that they
    // are copied.
    OptionUint16Ptr sub1 = OptionUint16Ptr(new OptionUint16(Option::V4, 10, 234));
    Option4AddrLstPtr sub2 =
        Option4AddrLstPtr(new Option4AddrLst(11, IOAddress("192.0.2.3")));
    option->addOption(sub1);
    option->addOption(sub2);

    // Copy option by copy construction, cloning or assignment.
    switch (op_type) {
    case COPY:
        option_copy.reset(new OptionType(*option));
        break;
    case CLONE:
        option_copy = boost::dynamic_pointer_cast<OptionType>(option->clone());
        ASSERT_TRUE(option_copy);
        break;
    case ASSIGN:
        option_copy->setEncapsulatedSpace("bar");
        *option_copy = *option;
        break;
    default:
        ADD_FAILURE() << "unsupported operation";
        return;
    }

    // Verify that basic parameters have been copied.
    EXPECT_EQ(option->getUniverse(), option_copy->getUniverse());
    EXPECT_EQ(option->getType(), option_copy->getType());
    EXPECT_EQ(option->len(), option_copy->len());
    EXPECT_EQ(option->getEncapsulatedSpace(), option_copy->getEncapsulatedSpace());
    EXPECT_TRUE(std::equal(option->getData().begin(), option->getData().end(),
                           option_copy->getData().begin()));

    // Retrieve sub options so as they can be compared.
    const OptionCollection& option_subs = option->getOptions();
    const OptionCollection& option_copy_subs = option_copy->getOptions();
    ASSERT_EQ(option_subs.size(), option_copy_subs.size());

    // Iterate over source options.
    OptionCollection::const_iterator it_copy = option_copy_subs.begin();
    for (OptionCollection::const_iterator it = option_subs.begin();
         it != option_subs.end(); ++it, ++it_copy) {
        // The option codes should be equal in both containers.
        EXPECT_EQ(it->first, it_copy->first);
        // Pointers must be unequal because the expectation is that options
        // are copied, rather than pointers.
        EXPECT_NE(it->second, it_copy->second);
        Option* opt_ptr = it->second.get();
        Option* opt_copy_ptr = it_copy->second.get();
        // The C++ types must match.
        EXPECT_TRUE(typeid(*opt_ptr) == typeid(*opt_copy_ptr));
    }

    // Final check is to compare their binary representations.
    std::vector<uint8_t> buf = option->toBinary(true);
    std::vector<uint8_t> buf_copy = option_copy->toBinary(true);

    ASSERT_EQ(buf.size(), buf_copy.size());
    EXPECT_TRUE(std::equal(buf_copy.begin(), buf_copy.end(), buf.begin()));
}

// **************************** Option ***************************

/// @brief Test deep copy of option encapsulated by Option type.
///
/// @param op_type Copy operation type.
void testOption(const OpType& op_type) {
    OptionBuffer buf(10, 1);
    OptionPtr option(new Option(Option::V4, 1, buf));
    OptionPtr option_copy(new Option(Option::V6, 1000));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Save binary representation of the original option. We will
    // be later comparing it with a copied option to make sure that
    // modification of the original option doesn't affect the copy.
    std::vector<uint8_t> binary_copy = option_copy->toBinary(true);

    // Modify the original option.
    OptionBuffer buf_modified(10, 2);
    option->setData(buf_modified.begin(), buf_modified.end());

    // Retrieve the binary representation of the copy to verify that
    // it hasn't been modified.
    std::vector<uint8_t> binary_copy_after = option_copy->toBinary(true);

    ASSERT_EQ(binary_copy.size(), binary_copy_after.size());
    EXPECT_TRUE(std::equal(binary_copy_after.begin(), binary_copy_after.end(),
                           binary_copy.begin()));
}

TEST(OptionCopyTest, optionConstructor) {
    testOption(COPY);
}

TEST(OptionCopyTest, optionClone) {
    testOption(CLONE);
}

TEST(OptionCopyTest, optionAssignment) {
    testOption(ASSIGN);
}

// **************************** OptionInt ***************************

/// @brief Test deep copy of option encapsulated by OptionInt type.
///
/// @param op_type Copy operation type.
void testOptionInt(const OpType& op_type) {
    OptionUint16Ptr option(new OptionUint16(Option::V4, 1, 12345));
    OptionUint16Ptr option_copy(new OptionUint16(Option::V6, 10, 11111));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Modify value in the original option.
    option->setValue(9);

    // The value in the copy should not be affected.
    EXPECT_EQ(12345, option_copy->getValue());
}

TEST(OptionCopyTest, optionIntConstructor) {
    testOptionInt(COPY);
}

TEST(OptionCopyTest, optionIntClone) {
    testOptionInt(CLONE);
}

TEST(OptionCopyTest, optionIntAssignment) {
    testOptionInt(ASSIGN);
}

// ************************* OptionIntArray ***************************

/// @brief Test deep copy of option encapsulated by OptionIntArray type.
///
/// @param op_type Copy operation type.
void testOptionIntArray(const OpType& op_type) {
    OptionUint32ArrayPtr option(new OptionUint32Array(Option::V4, 1));;
    option->addValue(2345);
    option->addValue(3456);
    OptionUint32ArrayPtr option_copy(new OptionUint32Array(Option::V6, 10));
    option_copy->addValue(5678);
    option_copy->addValue(6789);

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Modify the values in the original option.
    option->setValues(std::vector<uint32_t>(2, 7));

    // The values in the copy should not be affected.
    std::vector<uint32_t> values_copy = option_copy->getValues();
    ASSERT_EQ(2, values_copy.size());
    EXPECT_EQ(2345, values_copy[0]);
    EXPECT_EQ(3456, values_copy[1]);
}

TEST(OptionCopyTest, optionIntArrayConstructor) {
    testOptionIntArray(COPY);
}

TEST(OptionCopyTest, optionIntArrayClone) {
    testOptionIntArray(CLONE);
}

TEST(OptionCopyTest, optionIntArrayAssignment) {
    testOptionIntArray(ASSIGN);
}

// ************************* Option4AddrLst ***************************

/// @brief Test deep copy of option encapsulated by Option4AddrLst or
/// Option6AddrLst type.
///
/// @param op_type Copy operation type.
/// @param option_address Address carried in the source option.
/// @param option_copy_address Address carried in the destination option.
/// @param option_modified_address Address to which the original address
/// is modified to check that this modification doesn't affect option
/// copy.
/// @tparam OptionType Option4AddrLst or Option6AddrLst.
template<typename OptionType>
void testOptionAddrLst(const OpType& op_type,
                       const IOAddress& option_address,
                       const IOAddress& option_copy_address,
                       const IOAddress& option_modified_address) {
    typedef boost::shared_ptr<OptionType> OptionTypePtr;
    OptionTypePtr option(new OptionType(1, option_address));
    OptionTypePtr option_copy(new OptionType(10, option_copy_address));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Modify the address in the original option.
    option->setAddress(option_modified_address);

    // The address in the copy should not be affected.
    typename OptionType::AddressContainer addrs_copy = option_copy->getAddresses();
    ASSERT_EQ(1, addrs_copy.size());
    EXPECT_EQ(option_address.toText(), addrs_copy[0].toText());
}

/// @brief Test deep copy of option encapsulated by Option4AddrLst type.
///
/// @param op_type Copy operation type.
void testOption4AddrLst(const OpType& op_type) {
    testOptionAddrLst<Option4AddrLst>(op_type,
                                      IOAddress("127.0.0.1"),
                                      IOAddress("192.0.2.111"),
                                      IOAddress("127.0.0.1"));
}

TEST(OptionCopyTest, option4AddrLstConstructor) {
    testOption4AddrLst(COPY);
}

TEST(OptionCopyTest, option4AddrLstClone) {
    testOption4AddrLst(CLONE);
}

TEST(OptionCopyTest, option4AddrLstAssignment) {
    testOption4AddrLst(ASSIGN);
}

// ************************* Option6AddrLst ***************************

/// @brief Test deep copy of option encapsulated by Option6AddrLst type.
///
/// @param op_type Copy operation type.
void testOption6AddrLst(const OpType& op_type) {
    testOptionAddrLst<Option6AddrLst>(op_type,
                                      IOAddress("2001:db8:1::2"),
                                      IOAddress("3001::cafe"),
                                      IOAddress("3000:1::1"));
}

TEST(OptionCopyTest, option6AddrLstConstructor) {
    testOption6AddrLst(COPY);
}

TEST(OptionCopyTest, option6AddrLstClone) {
    testOption6AddrLst(CLONE);
}

TEST(OptionCopyTest, option6AddrLstAssignment) {
    testOption6AddrLst(ASSIGN);
}

// *************************** Option6IA ***************************

/// @brief Test deep copy of option encapsulated by Option6IA type.
///
/// @param op_type Copy operation type.
void testOption6IA(const OpType& op_type) {
    Option6IAPtr option(new Option6IA(D6O_IA_NA, 1234));
    option->setT1(1000);
    option->setT2(2000);
    Option6IAPtr option_copy(new Option6IA(D6O_IA_PD, 5678));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Modify the values in the original option.
    option->setT1(3000);
    option->setT2(4000);
    option->setIAID(5678);

    // The values in the copy should not be affected.
    EXPECT_EQ(1000, option_copy->getT1());
    EXPECT_EQ(2000, option_copy->getT2());
    EXPECT_EQ(1234, option_copy->getIAID());
}

TEST(OptionCopyTest, option6IAConstructor) {
    testOption6IA(COPY);
}

TEST(OptionCopyTest, option6IAClone) {
    testOption6IA(CLONE);
}

TEST(OptionCopyTest, option6IAAssignment) {
    testOption6IA(ASSIGN);
}

// *************************** Option6IAAddr ***************************

/// @brief Test deep copy of option encapsulated by Option6IAAddr type.
///
/// @param op_type Copy operation type.
void testOption6IAAddr(const OpType& op_type) {
    Option6IAAddrPtr option(new Option6IAAddr(D6O_IAADDR,
                                              IOAddress("2001:db8:1::1"),
                                              60, 90));
    Option6IAAddrPtr option_copy(new Option6IAAddr(D6O_IAADDR,
                                                       IOAddress("2001:db8:1::2"),
                                                       50, 80));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Modify the values in the original option.
    option->setAddress(IOAddress("2001:db8:1::3"));
    option->setPreferred(1000);
    option->setValid(2000);

    // The values in the copy should not be affected.
    EXPECT_EQ("2001:db8:1::1", option_copy->getAddress().toText());
    EXPECT_EQ(60, option_copy->getPreferred());
    EXPECT_EQ(90, option_copy->getValid());
}

TEST(OptionCopyTest, option6IAAddrConstructor) {
    testOption6IAAddr(COPY);
}

TEST(OptionCopyTest, option6IAAddrClone) {
    testOption6IAAddr(CLONE);
}

TEST(OptionCopyTest, option6IAAddrAssignment) {
    testOption6IAAddr(ASSIGN);
}

// *************************** Option6IAPrefix ***************************

/// @brief Test deep copy of option encapsulated by Option6IAPrefix type.
///
/// @param op_type Copy operation type.
void testOption6IAPrefix(const OpType& op_type) {
   Option6IAPrefixPtr option(new Option6IAPrefix(D6O_IAPREFIX,
                                                  IOAddress("3000::"),
                                                  64, 60, 90));
    Option6IAPrefixPtr option_copy(new Option6IAPrefix(D6O_IAPREFIX,
                                                           IOAddress("3001::"),
                                                           48, 50, 80));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Modify the values in the original option.
    option->setPrefix(IOAddress("3002::"), 32);
    option->setPreferred(1000);
    option->setValid(2000);

    // The values in the copy should not be affected.
    EXPECT_EQ("3000::", option_copy->getAddress().toText());
    EXPECT_EQ(64, option_copy->getLength());
    EXPECT_EQ(60, option_copy->getPreferred());
    EXPECT_EQ(90, option_copy->getValid());
}

TEST(OptionCopyTest, option6IAPrefixConstructor) {
    testOption6IAPrefix(COPY);
}

TEST(OptionCopyTest, option6IAPrefixClone) {
    testOption6IAPrefix(CLONE);
}

TEST(OptionCopyTest, option6IAPrefixAssignment) {
    testOption6IAPrefix(ASSIGN);
}

// *************************** Option6StatusCode ***************************

/// @brief Test deep copy of option encapsulated by Option6StatusCode type.
///
/// @param op_type Copy operation type.
void testOption6StatusCode(const OpType& op_type) {
    Option6StatusCodePtr option(new Option6StatusCode(STATUS_NoBinding,
                                                      "no binding"));
    Option6StatusCodePtr option_copy(new Option6StatusCode(STATUS_Success,
                                                           "success"));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Modify the values in the original option.
    option->setStatusCode(STATUS_NoAddrsAvail);
    option->setStatusMessage("foo");

    // The values in the copy should not be affected.
    EXPECT_EQ(STATUS_NoBinding, option_copy->getStatusCode());
    EXPECT_EQ("no binding", option_copy->getStatusMessage());
}

TEST(OptionCopyTest, option6StatusCodeConstructor) {
    testOption6StatusCode(COPY);
}

TEST(OptionCopyTest, option6StatusCodeClone) {
    testOption6StatusCode(CLONE);
}

TEST(OptionCopyTest, option6StatusCodeAssignment) {
    testOption6StatusCode(ASSIGN);
}

// *************************** OptionString ***************************

/// @brief Test deep copy of option encapsulated by OptionString type.
///
/// @param op_type Copy operation type.
void testOptionString(const OpType& op_type) {
    OptionStringPtr option(new OptionString(Option::V4, 1, "option value"));
    OptionStringPtr option_copy(new OptionString(Option::V6, 10,
                                                     "another value"));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Modify the string in the original option.
    option->setValue("foo");

    // The string in the copy should not be affected.
    EXPECT_EQ("option value", option_copy->getValue());
}

TEST(OptionCopyTest, optionStringConstructor) {
    testOptionString(COPY);
}

TEST(OptionCopyTest, optionStringClone) {
    testOptionString(CLONE);
}

TEST(OptionCopyTest, optionStringAssignment) {
    testOptionString(ASSIGN);
}

// *************************** OptionVendor ***************************

/// @brief Test deep copy of option encapsulated by OptionVendor type.
///
/// @param op_type Copy operation type.
void testOptionVendor(const OpType& op_type) {
    OptionVendorPtr option(new OptionVendor(Option::V4, 2986));
    OptionVendorPtr option_copy(new OptionVendor(Option::V6, 1111));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Modify the vendor id in the original option.
    option->setVendorId(2222);

    // The vendor id in the copy should not be affected.
    EXPECT_EQ(2986, option_copy->getVendorId());
}

TEST(OptionCopyTest, optionVendorConstructor) {
    testOptionVendor(COPY);
}

TEST(OptionCopyTest, optionVendorClone) {
    testOptionVendor(CLONE);
}

TEST(OptionCopyTest, optionVendorAssignment) {
    testOptionVendor(ASSIGN);
}

// *********************** OptionVendorClass ***************************

/// @brief Test deep copy of option encapsulated by OptionVendorClass type.
///
/// @param op_type Copy operation type.
void testOptionVendorClass(const OpType& op_type) {
    // Create a DHCPv4 option with a single tuple.
    OptionVendorClassPtr option(new OptionVendorClass(Option::V4, 2986));
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    tuple = "vendor-class-value";
    option->setTuple(0, tuple);

    // Create a DHCPv6 option with a single tuple.
    OptionVendorClassPtr option_copy(new OptionVendorClass(Option::V6,
                                                               1111));
    OpaqueDataTuple tuple_copy(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "vendor-class-assigned";
    option_copy->addTuple(tuple_copy);

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Modify the tuple in the original option and add one more tuple.
    tuple = "modified-vendor-class-value";
    option->setTuple(0, tuple);
    tuple = "another-modified-vendor-class-value";
    option->addTuple(tuple);

    // That change shouldn't affect the original option. It should still
    // contain a single tuple with the original value.
    ASSERT_EQ(1, option_copy->getTuplesNum());
    tuple = option_copy->getTuple(0);
    EXPECT_TRUE(tuple.equals("vendor-class-value"));
}

TEST(OptionCopyTest, optionVendorClassConstructor) {
    testOptionVendorClass(COPY);
}

TEST(OptionCopyTest, optionVendorClassClone) {
    testOptionVendorClass(CLONE);
}

TEST(OptionCopyTest, optionVendorClassAssignment) {
    testOptionVendorClass(ASSIGN);
}

// ************************** Option4ClientFqdn ***************************

/// @brief Test deep copy of option encapsulated by Option4ClientFqdn or
/// Option6ClientFqdn type.
///
/// @param op_type Copy operation type.
/// @param option Option to be copied.
/// @param option_copy Destination option. Note that this option may be
/// initially set to a non-null value. For the "copy" and "clone" operations
/// the pointer will be reset, so there is no sense to initialize this
/// object to a non-null value. However, for the assignment testing it is
/// recommended to initialize the option_copy to point to an option having
/// different parameters to verify that all parameters have been overridden
/// by the assignment operation.
///
/// @tparam OptionType Option4ClientFqdn or Option6ClientFqdn.
template<typename OptionType>
void testOptionClientFqdn(const OpType& op_type,
                          boost::shared_ptr<OptionType>& option,
                          boost::shared_ptr<OptionType>& option_copy) {
    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Modify the values in the original option.
    option->setDomainName("newname", OptionType::PARTIAL);
    option->setFlag(OptionType::FLAG_S, false);
    option->setFlag(OptionType::FLAG_N, true);

    // Rcode is carried on the in the DHCPv4 Client FQDN option.
    // If the OptionType is pointing to a DHCPv6 option the dynamic
    // cast will result in NULL pointer and we'll not check the
    // RCODE.
    Option4ClientFqdnPtr option4 =
        boost::dynamic_pointer_cast<Option4ClientFqdn>(option);
    if (option4) {
        option4->setRcode(64);
    }

    // Verify that common parameters haven't been modified in the
    // copied option by the change in the original option.
    EXPECT_EQ("myname.example.org.", option_copy->getDomainName());
    EXPECT_EQ(OptionType::FULL, option_copy->getDomainNameType());
    EXPECT_TRUE(option_copy->getFlag(OptionType::FLAG_S));
    EXPECT_FALSE(option_copy->getFlag(OptionType::FLAG_N));

    // If we're dealing with DHCPv4 Client FQDN, we also need to
    // test RCODE.
    Option4ClientFqdnPtr option_copy4 =
        boost::dynamic_pointer_cast<Option4ClientFqdn>(option_copy);
    if (option_copy4) {
        EXPECT_EQ(255, option_copy4->getRcode().first.getCode());
        EXPECT_EQ(255, option_copy4->getRcode().second.getCode());
    }
}

/// @brief Test deep copy of option encapsulated by Option4ClientFqdn type.
///
/// @param op_type Copy operation type.
void testOption4ClientFqdn(const OpType& op_type) {
    Option4ClientFqdnPtr
        option(new Option4ClientFqdn(Option4ClientFqdn::FLAG_S,
                                     Option4ClientFqdn::Rcode(255),
                                     "myname.example.org"));
    Option4ClientFqdnPtr
        option_copy(new Option4ClientFqdn(Option4ClientFqdn::FLAG_O,
                                          Option4ClientFqdn::Rcode(0),
                                          "other.example.org"));

    ASSERT_NO_FATAL_FAILURE(testOptionClientFqdn<Option4ClientFqdn>(op_type, option,
                                                                    option_copy));
}

TEST(OptionCopyTest, option4ClientFqdnConstructor) {
    testOption4ClientFqdn(COPY);
}

TEST(OptionCopyTest, option4ClientFqdnClone) {
    testOption4ClientFqdn(CLONE);
}

TEST(OptionCopyTest, option4ClientFqdnAssignment) {
    testOption4ClientFqdn(ASSIGN);
}

// ************************** Option6ClientFqdn ***************************

/// @brief Test deep copy of option encapsulated by Option6ClientFqdn type.
///
/// @param op_type Copy operation type.
void testOption6ClientFqdn(const OpType& op_type) {
    Option6ClientFqdnPtr
        option(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S,
                                     "myname.example.org"));
    Option6ClientFqdnPtr
        option_copy(new Option6ClientFqdn(Option6ClientFqdn::FLAG_O,
                                          "other.example.org"));

    ASSERT_NO_FATAL_FAILURE(testOptionClientFqdn<Option6ClientFqdn>(op_type, option,
                                                                    option_copy));
}

TEST(OptionCopyTest, option6ClientFqdnConstructor) {
    testOption6ClientFqdn(COPY);
}

TEST(OptionCopyTest, option6ClientFqdnClone) {
    testOption6ClientFqdn(CLONE);
}

TEST(OptionCopyTest, option6ClientFqdnAssignment) {
    testOption6ClientFqdn(ASSIGN);
}

// **************************** OptionCustom ***************************

/// @brief Test deep copy of option encapsulated by OptionCustom type.
///
/// @param op_type Copy operation type.
void testOptionCustom(const OpType& op_type) {
    // Create option with a single field carrying 16-bits integer.
    OptionDefinition def("foo", 1, "my-space", "uint16", true);
    OptionCustomPtr option(new OptionCustom(def, Option::V4));
    option->addArrayDataField<uint16_t>(5555);

    // Create option with two fields carrying IPv4 address and 32-bit
    // integer.
    OptionDefinition def_copy("bar", 10, "my-space", "record");
    def_copy.addRecordField("ipv4-address");
    def_copy.addRecordField("uint32");
    OptionCustomPtr option_copy(new OptionCustom(def_copy, Option::V6));
    option_copy->writeAddress(IOAddress("192.0.0.2"));
    option_copy->writeInteger<uint32_t>(12, 1);

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Modify the original option value.
    option->writeInteger<uint16_t>(1000);

    // The copied option should not be affected.
    ASSERT_EQ(1, option_copy->getDataFieldsNum());
    EXPECT_EQ(5555, option_copy->readInteger<uint16_t>());
}

TEST(OptionCopyTest, optionCustomConstructor) {
    testOptionCustom(COPY);
}

TEST(OptionCopyTest, optionCustomClone) {
    testOptionCustom(CLONE);
}

TEST(OptionCopyTest, optionCustomAssignment) {
    testOptionCustom(ASSIGN);
}

// ************************ OptionOpaqueDataTuples ***********************

/// @brief Test deep copy of option encapsulated by OptionOpaqueDataTuples type.
///
/// @param op_type Copy operation type.
void testOptionOpaqueDataTuples(const OpType& op_type) {
    OptionOpaqueDataTuplesPtr option(new OptionOpaqueDataTuples(Option::V4, 1));
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    tuple = "a string";
    option->addTuple(tuple);
    tuple = "another string";
    option->addTuple(tuple);
    OptionOpaqueDataTuplesPtr option_copy(new OptionOpaqueDataTuples(Option::V6, 10));
    OpaqueDataTuple tuple_copy(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple_copy = "copy string";
    option_copy->addTuple(tuple_copy);

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    // Modify the value in the first tuple and add one more tuple.
    tuple = "modified-first-tuple";
    option->setTuple(0, tuple);
    tuple = "modified-second-tuple";
    option->setTuple(1, tuple);

    // This should not affect the values in the original option.
    ASSERT_EQ(2, option_copy->getTuplesNum());
    EXPECT_TRUE(option_copy->getTuple(0).equals("a string"));
    EXPECT_TRUE(option_copy->getTuple(1).equals("another string"));
}

TEST(OptionCopyTest, optionOpaqueDataTuplesConstructor) {
    testOptionOpaqueDataTuples(COPY);
}

TEST(OptionCopyTest, optionOpaqueDataTuplesClone) {
    testOptionOpaqueDataTuples(CLONE);
}

TEST(OptionCopyTest, optionOpaqueDataTuplesAssign) {
    testOptionOpaqueDataTuples(ASSIGN);
}

}
