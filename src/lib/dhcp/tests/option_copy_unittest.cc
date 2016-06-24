// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
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

enum OpType {
    COPY,
    CLONE,
    ASSIGN
};

template<typename OptionType>
void testCopyAssign(const OpType& op_type,
                    boost::shared_ptr<OptionType>& option,
                    boost::shared_ptr<OptionType>& option_copy) {
    option->setEncapsulatedSpace("foo");

    OptionUint16Ptr sub1 = OptionUint16Ptr(new OptionUint16(Option::V4, 10, 234));
    Option4AddrLstPtr sub2 =
        Option4AddrLstPtr(new Option4AddrLst(11, IOAddress("192.0.2.3")));
    option->addOption(sub1);
    option->addOption(sub2);

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

    EXPECT_EQ(option->getUniverse(), option_copy->getUniverse());
    EXPECT_EQ(option->getType(), option_copy->getType());
    EXPECT_EQ(option->len(), option_copy->len());
    EXPECT_EQ(option->getEncapsulatedSpace(), option_copy->getEncapsulatedSpace());
    EXPECT_TRUE(std::equal(option->getData().begin(), option->getData().end(),
                           option_copy->getData().begin()));

    const OptionCollection& option_subs = option->getOptions();
    const OptionCollection& option_copy_subs = option_copy->getOptions();

    ASSERT_EQ(option_subs.size(), option_copy_subs.size());
    OptionCollection::const_iterator it_copy = option_copy_subs.begin();
    for (OptionCollection::const_iterator it = option_subs.begin();
         it != option_subs.end(); ++it, ++it_copy) {
        EXPECT_EQ(it->first, it_copy->first);
        EXPECT_NE(it->second, it_copy->second);
        Option* opt_ptr = it->second.get();
        Option* opt_copy_ptr = it_copy->second.get();
        EXPECT_TRUE(typeid(*opt_ptr) == typeid(*opt_copy_ptr));
    }

    std::vector<uint8_t> buf = option->toBinary(true);
    std::vector<uint8_t> buf_copy = option_copy->toBinary(true);

    ASSERT_EQ(buf.size(), buf_copy.size());
    EXPECT_TRUE(std::equal(buf_copy.begin(), buf_copy.end(), buf.begin()));
}

void testOption(const OpType& op_type) {
    OptionBuffer buf(10, 1);
    OptionPtr option(new Option(Option::V4, 1, buf));
    OptionPtr option_copy(new Option(Option::V6, 1000));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    std::vector<uint8_t> binary_copy = option_copy->toBinary(true);

    OptionBuffer buf_modified(10, 2);
    option->setData(buf_modified.begin(), buf_modified.end());

    std::vector<uint8_t> binary_modified = option->toBinary(true);

    ASSERT_EQ(binary_modified.size(), binary_copy.size());
    EXPECT_FALSE(std::equal(binary_copy.begin(), binary_copy.end(),
                            binary_modified.begin()));
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


void testOptionInt(const OpType& op_type) {
    OptionUint16Ptr option(new OptionUint16(Option::V4, 1, 12345));
    OptionUint16Ptr option_copy(new OptionUint16(Option::V6, 10, 11111));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    ASSERT_EQ(12345, option->getValue());
    ASSERT_EQ(12345, option_copy->getValue());

    option->setValue(9);
    ASSERT_EQ(9, option->getValue());
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

void testOptionIntArray(const OpType& op_type) {
    OptionUint32ArrayPtr option(new OptionUint32Array(Option::V4, 1));;
    option->addValue(2345);
    option->addValue(3456);
    OptionUint32ArrayPtr option_copy(new OptionUint32Array(Option::V6, 10));
    option_copy->addValue(5678);
    option_copy->addValue(6789);

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    option->setValues(std::vector<uint32_t>(2, 7));

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

template<typename OptionType>
void testOptionAddrLst(const OpType& op_type,
                       const IOAddress& option_address,
                       const IOAddress& option_copy_address,
                       const IOAddress& option_modified_address) {
    typedef boost::shared_ptr<OptionType> OptionTypePtr;
    OptionTypePtr option(new OptionType(1, option_address));
    OptionTypePtr option_copy(new OptionType(10, option_copy_address));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    option->setAddress(option_modified_address);
    typename OptionType::AddressContainer addrs_copy = option_copy->getAddresses();
    ASSERT_EQ(1, addrs_copy.size());
    EXPECT_EQ(option_address.toText(), addrs_copy[0].toText());
}

void testOption4AddrLst(const OpType& op_type) {
    testOptionAddrLst<Option4AddrLst>(op_type,
                                      IOAddress("127.0.0.1"),
                                      IOAddress("192.0.2.111"),
                                      IOAddress("127.0.0.1"));
}

void testOption6AddrLst(const OpType& op_type) {
    testOptionAddrLst<Option6AddrLst>(op_type,
                                      IOAddress("2001:db8:1::2"),
                                      IOAddress("3001::cafe"),
                                      IOAddress("3000:1::1"));
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

TEST(OptionCopyTest, option6AddrLstConstructor) {
    testOption6AddrLst(COPY);
}

TEST(OptionCopyTest, option6AddrLstClone) {
    testOption6AddrLst(CLONE);
}

TEST(OptionCopyTest, option6AddrLstAssignment) {
    testOption6AddrLst(ASSIGN);
}

void testOption6IA(const OpType& op_type) {
    Option6IAPtr option(new Option6IA(D6O_IA_NA, 1234));
    option->setT1(1000);
    option->setT2(2000);
    Option6IAPtr option_copy(new Option6IA(D6O_IA_PD, 5678));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    option->setT1(3000);
    option->setT2(4000);
    option->setIAID(5678);

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

void testOption6IAAddr(const OpType& op_type) {
    Option6IAAddrPtr option(new Option6IAAddr(D6O_IAADDR,
                                              IOAddress("2001:db8:1::1"),
                                              60, 90));
    Option6IAAddrPtr option_copy(new Option6IAAddr(D6O_IAADDR,
                                                       IOAddress("2001:db8:1::2"),
                                                       50, 80));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    option->setAddress(IOAddress("2001:db8:1::3"));
    option->setPreferred(1000);
    option->setValid(2000);

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

void testOption6IAPrefix(const OpType& op_type) {
   Option6IAPrefixPtr option(new Option6IAPrefix(D6O_IAPREFIX,
                                                  IOAddress("3000::"),
                                                  64, 60, 90));
    Option6IAPrefixPtr option_copy(new Option6IAPrefix(D6O_IAPREFIX,
                                                           IOAddress("3001::"),
                                                           48, 50, 80));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    option->setPrefix(IOAddress("3002::"), 32);
    option->setPreferred(1000);
    option->setValid(2000);

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

void testOption6StatusCode(const OpType& op_type) {
    Option6StatusCodePtr option(new Option6StatusCode(STATUS_NoBinding,
                                                      "no binding"));
    Option6StatusCodePtr option_copy(new Option6StatusCode(STATUS_Success,
                                                           "success"));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    option->setStatusCode(STATUS_NoAddrsAvail);
    option->setStatusMessage("foo");

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

void testOptionString(const OpType& op_type) {
    OptionStringPtr option(new OptionString(Option::V4, 1, "option value"));
    OptionStringPtr option_copy(new OptionString(Option::V6, 10,
                                                     "another value"));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    option->setValue("foo");
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

void testOptionVendor(const OpType& op_type) {
    OptionVendorPtr option(new OptionVendor(Option::V4, 2986));
    OptionVendorPtr option_copy(new OptionVendor(Option::V6, 1111));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    option->setVendorId(2222);
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

void testOptionVendorClass(const OpType& op_type) {
    OptionVendorClassPtr option(new OptionVendorClass(Option::V4, 2986));
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    tuple = "vendor-class-value";
    option->setTuple(0, tuple);
    OptionVendorClassPtr option_copy(new OptionVendorClass(Option::V6,
                                                               1111));
    OpaqueDataTuple tuple_copy(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "vendor-class-assigned";
    option_copy->addTuple(tuple_copy);

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    tuple = "modified-vendor-class-value";
    option->setTuple(0, tuple);
    tuple = "another-modified-vendor-class-value";
    option->addTuple(tuple);

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

template<typename OptionType>
void testOptionClientFqdn(const OpType& op_type,
                          boost::shared_ptr<OptionType>& option,
                          boost::shared_ptr<OptionType>& option_copy) {
    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));

    option->setDomainName("newname", OptionType::PARTIAL);
    option->setFlag(OptionType::FLAG_S, false);
    option->setFlag(OptionType::FLAG_N, true);

    Option4ClientFqdnPtr option4 =
        boost::dynamic_pointer_cast<Option4ClientFqdn>(option);
    if (option4) {
        option4->setRcode(64);
    }

    EXPECT_EQ("myname.example.org.", option_copy->getDomainName());
    EXPECT_EQ(OptionType::FULL, option_copy->getDomainNameType());
    EXPECT_TRUE(option_copy->getFlag(OptionType::FLAG_S));
    EXPECT_FALSE(option_copy->getFlag(OptionType::FLAG_N));

    Option4ClientFqdnPtr option_copy4 =
        boost::dynamic_pointer_cast<Option4ClientFqdn>(option_copy);
    if (option_copy4) {
        EXPECT_EQ(255, option_copy4->getRcode().first.getCode());
        EXPECT_EQ(255, option_copy4->getRcode().second.getCode());
    }
}

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

void testOptionCustom(const OpType& op_type) {
    OptionDefinition def("foo", 1, "uint16", true);
    OptionCustomPtr option(new OptionCustom(def, Option::V4));
    OptionDefinition def_assigned("bar", 10, "record");
    def_assigned.addRecordField("ipv4-address");
    def_assigned.addRecordField("uint32");
    OptionCustomPtr option_copy(new OptionCustom(def_assigned, Option::V6));

    ASSERT_NO_FATAL_FAILURE(testCopyAssign(op_type, option, option_copy));
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

    tuple = "modified-first-tuple";
    option->setTuple(0, tuple);
    tuple = "modified-second-tuple";
    option->addTuple(tuple);

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
