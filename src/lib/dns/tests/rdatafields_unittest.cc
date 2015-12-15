// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <vector>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rdatafields.h>
#include <dns/tests/unittest_util.h>

#include <util/unittests/wiredata.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::OutputBuffer;
using isc::util::InputBuffer;
using isc::util::unittests::matchWireData;

namespace {
class RdataFieldsTest : public ::testing::Test {
protected:
    RdataFieldsTest() : obuffer(0), ns_name("example.com"),
                        other_name("www.example.com")
    {}
    void constructCommonTests(const RdataFields& fields,
                              const uint8_t* const expected_data,
                              const size_t expected_data_len);
    void constructCommonTestsNS(const RdataFields& fields);
    void constructCommonTestsTXT(const RdataFields& fields);
    void constructCommonTestsRRSIG(const RdataFields& fields);
    void constructCommonTestsOPT(const RdataFields& fields);
    OutputBuffer obuffer;
    MessageRenderer renderer;
    const Name ns_name;
    const Name other_name;
    vector<unsigned char> expected_wire;
    vector<unsigned char> fields_wire;
};

const uint8_t in_a_data[] = { 192, 0, 2, 1 };
// binary representation of example.com.
const uint8_t ns_data[] = { 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65,
                            0x03, 0x63, 0x6f, 0x6d, 0x00 };

//
// IN/A RDATA: fixed length, single data field
//
void
RdataFieldsTest::constructCommonTests(const RdataFields& fields,
                                      const uint8_t* const expected_data,
                                      const size_t expected_data_len)
{
    matchWireData(expected_data, expected_data_len,
                  fields.getData(), fields.getDataLength());

    EXPECT_EQ(sizeof(RdataFields::FieldSpec), fields.getFieldSpecDataSize());
    EXPECT_EQ(1, fields.getFieldCount());
    EXPECT_EQ(RdataFields::DATA, fields.getFieldSpec(0).type);
    EXPECT_EQ(4, fields.getFieldSpec(0).len);

    fields.toWire(obuffer);
    matchWireData(expected_data, expected_data_len,
                  obuffer.getData(), obuffer.getLength());

    fields.toWire(renderer);
    matchWireData(expected_data, expected_data_len,
                  renderer.getData(), renderer.getLength());
}

TEST_F(RdataFieldsTest, constructFromRdata) {
    const RdataFields fields(in::A("192.0.2.1"));
    constructCommonTests(fields, in_a_data, sizeof(in_a_data));
}

TEST_F(RdataFieldsTest, constructFromParams) {
    const RdataFields::FieldSpec spec(RdataFields::DATA, 4);
    const RdataFields fields(&spec, sizeof(spec), in_a_data,
                             sizeof(in_a_data));
    constructCommonTests(fields, in_a_data, sizeof(in_a_data));
}

//
// NS RDATA: containing a compressible name.
//
void
RdataFieldsTest::constructCommonTestsNS(const RdataFields& fields) {
    EXPECT_EQ(sizeof(RdataFields::FieldSpec), fields.getFieldSpecDataSize());
    EXPECT_EQ(1, fields.getFieldCount());
    EXPECT_EQ(RdataFields::COMPRESSIBLE_NAME, fields.getFieldSpec(0).type);
    EXPECT_EQ(ns_name.getLength(), fields.getFieldSpec(0).len);

    expected_wire.clear();
    UnitTestUtil::readWireData("rdatafields1.wire", expected_wire);
    other_name.toWire(obuffer);
    fields.toWire(obuffer);
    matchWireData(&expected_wire[0], expected_wire.size(),
                  obuffer.getData(), obuffer.getLength());

    expected_wire.clear();
    UnitTestUtil::readWireData("rdatafields2.wire", expected_wire);
    other_name.toWire(renderer);
    fields.toWire(renderer);
    matchWireData(&expected_wire[0], expected_wire.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(RdataFieldsTest, constructFromRdataNS) {
    const RdataFields fields_ns((generic::NS(ns_name)));
    constructCommonTestsNS(fields_ns);
}

TEST_F(RdataFieldsTest, constructFromParamsNS) {
    const RdataFields::FieldSpec spec(RdataFields::COMPRESSIBLE_NAME,
                                      sizeof(ns_data));
    const RdataFields fields_ns(&spec, sizeof(spec), ns_data, sizeof(ns_data));
    constructCommonTestsNS(fields_ns);
}

//
// TXT RDATA: multiple fields, lengths vary
//
void
RdataFieldsTest::constructCommonTestsTXT(const RdataFields& fields) {
    // Since all fields are plain data, they are handled as a single data
    // field.
    EXPECT_EQ(sizeof(RdataFields::FieldSpec), fields.getFieldSpecDataSize());
    EXPECT_EQ(1, fields.getFieldCount());
    EXPECT_EQ(RdataFields::DATA, fields.getFieldSpec(0).type);
    EXPECT_EQ(expected_wire.size(), fields.getFieldSpec(0).len);

    fields.toWire(obuffer);
    matchWireData(&expected_wire[0], expected_wire.size(),
                  obuffer.getData(), obuffer.getLength());

    fields.toWire(renderer);
    matchWireData(&expected_wire[0], expected_wire.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(RdataFieldsTest, constructFromRdataTXT) {
    UnitTestUtil::readWireData("rdatafields3.wire", expected_wire);
    InputBuffer ibuffer(&expected_wire[0], expected_wire.size());
    const uint16_t rdlen = ibuffer.readUint16();
    const RdataFields fields(generic::TXT(ibuffer, rdlen));

    // drop the RDLEN part
    expected_wire.erase(expected_wire.begin(), expected_wire.begin() + 2);

    constructCommonTestsTXT(fields);
}

TEST_F(RdataFieldsTest, constructFromParamsTXT) {
    UnitTestUtil::readWireData("rdatafields3.wire", expected_wire);
    expected_wire.erase(expected_wire.begin(), expected_wire.begin() + 2);
    const RdataFields::FieldSpec spec(RdataFields::DATA, expected_wire.size());
    const RdataFields fields(&spec, sizeof(spec), &expected_wire[0],
                             expected_wire.size());
    constructCommonTestsTXT(fields);
}

//
// RRSIG: multiple fields, with an incompressible name
//
void
RdataFieldsTest::constructCommonTestsRRSIG(const RdataFields& fields) {
    // In terms of RdataFields RRSIG RDATA consists of 3 fields:
    // - 18-byte data field (from the "type covered" field to "key tag" field)
    // - an incompressible name field (for the signer's name field).
    //   this is a variable length field.  In this test it's a 13-byte field.
    // - a variable-length data field for the signature.  In this tests
    //   it's a 15-byte field.
    EXPECT_EQ(3 * sizeof(RdataFields::FieldSpec),
              fields.getFieldSpecDataSize());
    EXPECT_EQ(3, fields.getFieldCount());
    EXPECT_EQ(RdataFields::DATA, fields.getFieldSpec(0).type);
    EXPECT_EQ(18, fields.getFieldSpec(0).len);
    EXPECT_EQ(RdataFields::INCOMPRESSIBLE_NAME, fields.getFieldSpec(1).type);
    EXPECT_EQ(13, fields.getFieldSpec(1).len);
    EXPECT_EQ(RdataFields::DATA, fields.getFieldSpec(2).type);
    EXPECT_EQ(15, fields.getFieldSpec(2).len);

    expected_wire.clear();
    UnitTestUtil::readWireData("rdatafields5.wire", expected_wire);
    Name("com").toWire(obuffer);
    obuffer.writeUint16(fields.getDataLength());
    fields.toWire(obuffer);
    other_name.toWire(obuffer);
    matchWireData(&expected_wire[0], expected_wire.size(),
                  obuffer.getData(), obuffer.getLength());

    expected_wire.clear();
    UnitTestUtil::readWireData("rdatafields6.wire", expected_wire);
    Name("com").toWire(renderer);
    renderer.writeUint16(fields.getDataLength());
    fields.toWire(renderer);    // the signer field won't be compressed
    other_name.toWire(renderer); // but will be used as a compression target
    matchWireData(&expected_wire[0], expected_wire.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(RdataFieldsTest, constructFromRdataRRSIG) {
    UnitTestUtil::readWireData("rdatafields4.wire", expected_wire);
    InputBuffer ibuffer(&expected_wire[0], expected_wire.size());
    const uint16_t rdlen = ibuffer.readUint16();
    const RdataFields fields(generic::RRSIG(ibuffer, rdlen));

    // drop the RDLEN part
    expected_wire.erase(expected_wire.begin(), expected_wire.begin() + 2);

    constructCommonTestsRRSIG(fields);
}

TEST_F(RdataFieldsTest, constructFromParamsRRSIG) {
    UnitTestUtil::readWireData("rdatafields4.wire", fields_wire);
    fields_wire.erase(fields_wire.begin(), fields_wire.begin() + 2);

    const RdataFields::FieldSpec specs[] = {
        RdataFields::FieldSpec(RdataFields::DATA, 18),
        RdataFields::FieldSpec(RdataFields::INCOMPRESSIBLE_NAME, 13),
        RdataFields::FieldSpec(RdataFields::DATA, 15)
    };
    const RdataFields fields(specs, sizeof(specs), &fields_wire[0],
                             fields_wire.size());
    constructCommonTestsRRSIG(fields);
}

TEST_F(RdataFieldsTest, convertRdatatoParams) {
    // Confirm we can restore the original data from the serialized data.
    // We use RRSIG as a relatively complicated field structure.
    UnitTestUtil::readWireData("rdatafields4.wire", expected_wire);
    InputBuffer ibuffer(&expected_wire[0], expected_wire.size());
    const uint16_t rdlen = ibuffer.readUint16();
    const RdataFields fields(generic::RRSIG(ibuffer, rdlen));

    expected_wire.erase(expected_wire.begin(), expected_wire.begin() + 2);

    // Copy the data in separate storage
    vector<uint8_t> spec_store(fields.getFieldSpecDataSize());
    void* cp_spec = &spec_store[0];
    memcpy(cp_spec, fields.getFieldSpecData(), spec_store.size());
    vector<uint8_t> data_store(fields.getDataLength());
    memcpy(&data_store[0], fields.getData(), fields.getDataLength());

    // Restore the data in the form of RdataFields
    const RdataFields fields_byparams(cp_spec, fields.getFieldSpecDataSize(),
                                      &data_store[0], fields.getDataLength());

    // Check it's valid
    constructCommonTestsRRSIG(fields_byparams);
}

//
// OPT: an empty RDATA
//
void
RdataFieldsTest::constructCommonTestsOPT(const RdataFields& fields) {
    EXPECT_EQ(0, fields.getFieldSpecDataSize());
    EXPECT_EQ(0, fields.getFieldCount());
    EXPECT_EQ(0, fields.getDataLength());
    EXPECT_EQ((const uint8_t*) NULL, fields.getData());
    fields.toWire(obuffer);
    EXPECT_EQ(0, obuffer.getLength());
    fields.toWire(renderer);
    EXPECT_EQ(0, renderer.getLength());
}

TEST_F(RdataFieldsTest, constructFromRdataOPT) {
    InputBuffer ibuffer(NULL, 0);
    const RdataFields fields(generic::OPT(ibuffer, 0));
    constructCommonTestsOPT(fields);
}

TEST_F(RdataFieldsTest, constructFromParamsOPT) {
    const RdataFields fields(NULL, 0, NULL, 0);
    constructCommonTestsOPT(fields);
}

// Invalid input to the "from parameter" constructor: sum of the field lengths
// is not equal to the data length.
TEST_F(RdataFieldsTest, invalidFieldLength) {
    UnitTestUtil::readWireData("rdatafields4.wire", fields_wire);
    fields_wire.erase(fields_wire.begin(), fields_wire.begin() + 2);

    const RdataFields::FieldSpec specs[] = {
        RdataFields::FieldSpec(RdataFields::DATA, 18),
        RdataFields::FieldSpec(RdataFields::INCOMPRESSIBLE_NAME, 13),
        RdataFields::FieldSpec(RdataFields::DATA, 14)
    };
    // sum of field len < data len
    EXPECT_THROW(RdataFields(specs, 3, &fields_wire[0], fields_wire.size()),
                 isc::InvalidParameter);
    // sum of field len > data len
    EXPECT_THROW(RdataFields(specs, 3, &fields_wire[0],
                             fields_wire.size() - 2),
                 isc::InvalidParameter);
}

// Invalid input to the "from parameter" constructor: NULL vs length mismatch
TEST_F(RdataFieldsTest, mismatchFieldLengthAndData) {
    const unsigned char dummy_data = 0;
    const RdataFields::FieldSpec dummy_spec(RdataFields::DATA, 1);

    EXPECT_THROW(RdataFields(NULL, 1, &dummy_data, 1), isc::InvalidParameter);
    EXPECT_THROW(RdataFields(&dummy_spec, 0, NULL, 0), isc::InvalidParameter);
    EXPECT_THROW(RdataFields(&dummy_spec, 1, NULL, 1), isc::InvalidParameter);
    EXPECT_THROW(RdataFields(NULL, 0, &dummy_data, 0), isc::InvalidParameter);
}

// Bogus input to getFieldSpec()
TEST_F(RdataFieldsTest, getFieldSpecWithBadFieldId) {
    const RdataFields fields_in_a(in::A("192.0.2.1"));
    EXPECT_THROW(fields_in_a.getFieldSpec(1), isc::OutOfRange);
}

// Tests for unexpected methods in RdataFieldComposerTest.  Confirm
// a call to these methods triggers an exception.  Expected methods are
// tested via other tests above.
class DummyRdata : public Rdata {
public:
    enum Mode { CLEAR, SKIP, TRIM };
    explicit DummyRdata(Mode mode) : mode_(mode) {}
    DummyRdata(const DummyRdata& source) : Rdata(), mode_(source.mode_) {}
    virtual ~DummyRdata() {}
    virtual void toWire(AbstractMessageRenderer& renderer) const {
        // call the unexpected method corresponding to the test mode.
        // method parameters don't matter.
        switch (mode_) {
        case CLEAR:
            renderer.clear();
            break;
        case SKIP:
            renderer.skip(2);
            break;
        case TRIM:
            renderer.trim(2);
            break;
        }
    }
    
    // These are defined only to make the compiler happy.  We don't use them
    // for the test.
    virtual string toText() const { return (""); }
    virtual void toWire(OutputBuffer&) const {}
    virtual int compare(const Rdata&) const { return (0); }
private:
    const int mode_;
};

TEST(RdataFieldComposerTest, unusedMethods) {
    EXPECT_THROW(RdataFields(DummyRdata(DummyRdata::CLEAR)), isc::Unexpected);
}
}
