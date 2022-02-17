// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <pgsql/pgsql_connection.h>
#include <pgsql/pgsql_exchange.h>
#include <pgsql/testutils/pgsql_schema.h>
#include <pgsql/tests/pgsql_basics.h>
#include <testutils/gtest_utils.h>

#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

#include <sstream>
#include <vector>

using namespace isc;
using namespace isc::data;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::util;
using namespace boost::posix_time;
using namespace boost::gregorian;

namespace {

/// @brief Verifies the ability to add various data types to
/// the bind array.
TEST(PsqlBindArray, addDataTest) {

    PsqlBindArray b;

    // Declare a vector to add. Vectors are not currently duplicated
    // So they will go out of scope, unless caller ensures it.
    std::vector<uint8_t> bytes;
    for (int i = 0; i < 10; i++) {
        bytes.push_back(i+1);
    }

    // Declare a string
    std::string not_temp_str("just a string");

    // Now add all the items within a different scope. Everything should
    // still be valid once we exit this scope.
    {
        // Add a const char*
        b.add("booya!");

        // Add the non temporary string
        b.add(not_temp_str);

        // Add a temporary string
        b.addTempString("walah walah washington");

        // Add a one byte int
        uint8_t small_int = 25;
        b.add(small_int);

        // Add a four byte int
        int reg_int = 376;
        b.add(reg_int);

        // Add a eight byte unsigned int
        uint64_t big_int = 48786749032;
        b.add(big_int);

        // Add boolean true and false
        b.add((bool)(1));
        b.add((bool)(0));

        // Add IP addresses
        b.add(isc::asiolink::IOAddress("192.2.15.34"));
        b.add(isc::asiolink::IOAddress("3001::1"));

        // Add the vector
        b.add(bytes);

        // Add an empty string.
        b.add(std::string(""));

        // Add a v4 address.
        asiolink::IOAddress addr4("192.168.1.1");
        b.addInet4(addr4);

        // Add a v6 address.
        asiolink::IOAddress addr6("3001::1");
        b.addInet6(addr6);

        // Add a double.  Not sure how portably reliable this test will be.
        double dbl = 2.0;
        b.add(dbl);

        // Add a JSON.
        ElementPtr elems = Element::fromJSON("{ \"foo\": \"bar\" }");
        b.add(elems);

        // Add a Temporary blob
        std::vector<uint8_t> blob({0x0a,0x0b,0x0,0xc,0xd});
        b.addTempBinary(blob);
    }

    // We've left bind scope, everything should be intact.
    std::string expected =
        "0 : \"booya!\"\n"
        "1 : \"just a string\"\n"
        "2 : \"walah walah washington\"\n"
        "3 : \"25\"\n"
        "4 : \"376\"\n"
        "5 : \"48786749032\"\n"
        "6 : \"TRUE\"\n"
        "7 : \"FALSE\"\n"
        "8 : \"3221360418\"\n"
        "9 : \"3001::1\"\n"
        "10 : 0x0102030405060708090a\n"
        "11 : empty\n"
        "12 : \"192.168.1.1\"\n"
        "13 : \"3001::1\"\n"
        "14 : \"2\"\n"
        "15 : \"{ \"foo\": \"bar\" }\"\n"
        "16 : 0x0a0b000c0d\n";

    EXPECT_EQ(expected, b.toText());
}

/// @brief Verifies the ability to add Triplets to
/// the bind array.
TEST(PsqlBindArray, addTriplet) {

    PsqlBindArray b;

    // Add all the items within a different scope. Everything should
    // still be valid once we exit this scope.
    {
        Triplet<uint32_t> empty;
        Triplet<uint32_t> not_empty(1,2,3);

        // Add triplets to the array.
        b.add(empty);
        b.add(not_empty);
        b.addMin(empty);
        b.addMin(not_empty);
        b.addMax(empty);
        b.addMax(not_empty);
    }

    // We've left bind scope, everything should be intact.
    EXPECT_EQ(6, b.size());

    // Verify contents are correct.
    std::string expected =
        "0 : empty\n"
        "1 : \"2\"\n"
        "2 : empty\n"
        "3 : \"1\"\n"
        "4 : empty\n"
        "5 : \"3\"\n";

    EXPECT_EQ(expected, b.toText());
}

/// @brief Verifies the ability to add Optional strings to
/// the bind array.
TEST(PsqlBindArray, addOptionalString) {

    PsqlBindArray b;

    // Add all the items within a different scope. Everything should
    // still be valid once we exit this scope.
    {
        Optional<std::string> empty;
        Optional<std::string> not_empty("whoopee!");

        // Add strings to the array.
        b.addOptional(empty);
        b.addOptional(not_empty);
    }

    // We've left bind scope, everything should be intact.
    EXPECT_EQ(2, b.size());

    // Verify contents are correct.
    std::string expected =
        "0 : empty\n"
        "1 : \"whoopee!\"\n";

    EXPECT_EQ(expected, b.toText());
}

/// @brief Verifies the ability to add Optional booleans to
/// the bind array.
TEST(PsqlBindArray, addOptionalBool) {

    PsqlBindArray b;

    // Add all the items within a different scope. Everything should
    // still be valid once we exit this scope.
    {
        Optional<bool> empty;
        Optional<bool> am_false(false);
        Optional<bool> am_true(true);

        // Add booleans to the array.
        b.addOptional(empty);
        b.addOptional(am_false);
        b.addOptional(am_true);
    }

    // We've left bind scope, everything should be intact.
    EXPECT_EQ(3, b.size());

    // Verify contents are correct.
    std::string expected =
        "0 : empty\n"
        "1 : \"0\"\n"
        "2 : \"1\"\n";

    EXPECT_EQ(expected, b.toText());
}


/// @brief Verifies the ability to add OptionalIntegers to
/// the bind array.
TEST(PsqlBindArray, addOptionalInteger) {

    PsqlBindArray b;

    // Add all the items within a different scope. Everything should
    // still be valid once we exit this scope.
    {
        Optional<uint32_t> empty;
        Optional<uint32_t> not_empty(123);

        // Add the integers to the array..
        b.addOptional(empty);
        b.addOptional(not_empty);
    }

    // We've left bind scope, everything should be intact.
    EXPECT_EQ(2, b.size());

    // Verify contents are correct.
    std::string expected =
        "0 : empty\n"
        "1 : \"123\"\n";

    EXPECT_EQ(expected, b.toText());
}

/// @brief Verifies the ability to add Optional IPv4 addresses to
/// the bind array.
TEST(PsqlBindArray, addOptionalInet4) {

    PsqlBindArray b;

    // Add all the items within a different scope. Everything should
    // still be valid once we exit this scope.
    {
        Optional<asiolink::IOAddress> empty;
        Optional<asiolink::IOAddress> not_empty(asiolink::IOAddress("192.16.1.1"));

        // Verify we cannot add a v6 address.
        Optional<asiolink::IOAddress> not_v4(asiolink::IOAddress("3001::1"));
        ASSERT_THROW_MSG(b.addOptionalInet4(not_v4), BadValue,
                         "unable to add address to PsqlBindAray"
                         " '3001::1' is not an IPv4 address");

        // Add addresses to bind array.
        b.addOptionalInet4(empty);
        b.addOptionalInet4(not_empty);
    }

    // We've left bind scope, everything should be intact.
    EXPECT_EQ(2, b.size());

    // Verify contents are correct.
    std::string expected =
        "0 : empty\n"
        "1 : \"192.16.1.1\"\n";

    EXPECT_EQ(expected, b.toText());
}

/// @brief Verifies the ability to add optional IPv6 addresses to
/// the bind array.
TEST(PsqlBindArray, addOptionalInet6) {

    PsqlBindArray b;

    // Add all the items within a different scope. Everything should
    // still be valid once we exit this scope.
    {
        Optional<asiolink::IOAddress> empty;
        Optional<asiolink::IOAddress> not_empty(asiolink::IOAddress("3001::1"));

        // Verify we cannot add a v6 address.
        Optional<asiolink::IOAddress> not_v6(asiolink::IOAddress("192.168.1.1"));
        ASSERT_THROW_MSG(b.addOptionalInet6(not_v6), BadValue,
                         "unable to add address to PsqlBindAray"
                         " '192.168.1.1' is not an IPv6 address");

        // Add addresses to bind array.
        b.addOptionalInet6(empty);
        b.addOptionalInet6(not_empty);
    }

    // We've left bind scope, everything should be intact.
    EXPECT_EQ(2, b.size());

    // Verify contents are correct.
    std::string expected =
        "0 : empty\n"
        "1 : \"3001::1\"\n";

    EXPECT_EQ(expected, b.toText());
}

/// @brief Verifies that PgResultSet row and column meta-data is correct
TEST_F(PgSqlBasicsTest, rowColumnBasics) {
    // We fetch the table contents, which at this point should be no rows.
    PgSqlResultPtr r;
    FETCH_ROWS(r, 0);

    // Column meta-data is determined by the select statement and is
    // present whether or not any rows were returned.
    EXPECT_EQ(r->getCols(), NUM_BASIC_COLS);

    // Negative indexes should be out of range.  We test negative values
    // as PostgreSQL functions accept column values as type int.
    EXPECT_THROW(r->colCheck(-1), DbOperationError);

    // Iterate over the column indexes verifying:
    // 1. the column is valid
    // 2. the result set column name matches the expected column name
    for (int i = 0; i < NUM_BASIC_COLS; i++) {
        EXPECT_NO_THROW(r->colCheck(i));
        EXPECT_EQ(r->getColumnLabel(i), expectedColumnName(i));
    }

    // Verify above range column value is detected.
    EXPECT_THROW(r->colCheck(NUM_BASIC_COLS), DbOperationError);

    // Verify the fetching a column label for out of range columns
    // do NOT throw.
    std::string label;
    ASSERT_NO_THROW(label = r->getColumnLabel(-1));
    EXPECT_EQ(label, "Unknown column:-1");
    ASSERT_NO_THROW(label = r->getColumnLabel(NUM_BASIC_COLS));
    std::ostringstream os;
    os << "Unknown column:" << NUM_BASIC_COLS;
    EXPECT_EQ(label, os.str());

    // Verify row count and checking. With an empty result set all values of
    // row are invalid.
    EXPECT_EQ(r->getRows(), 0);
    EXPECT_THROW(r->rowCheck(-1), DbOperationError);
    EXPECT_THROW(r->rowCheck(0), DbOperationError);
    EXPECT_THROW(r->rowCheck(1), DbOperationError);

    // Verify Row-column check will always fail with an empty result set.
    EXPECT_THROW(r->rowColCheck(-1, 1), DbOperationError);
    EXPECT_THROW(r->rowColCheck(0, 1), DbOperationError);
    EXPECT_THROW(r->rowColCheck(1, 1), DbOperationError);

    // Insert three minimal rows.  We don't really care about column content
    // for this test.
    int num_rows = 3;
    for (int i = 0; i < num_rows; i++) {
        RUN_SQL(r, "INSERT INTO basics (bool_col) VALUES ('t')",
                PGRES_COMMAND_OK);
    }

    // Fetch the newly created rows.
    FETCH_ROWS(r, num_rows);

    // Verify we row count and checking
    EXPECT_EQ(r->getRows(), num_rows);
    EXPECT_THROW(r->rowCheck(-1), DbOperationError);

    // Iterate over the row count, verifying that expected rows are valid
    for (int i = 0; i < num_rows; i++) {
        EXPECT_NO_THROW(r->rowCheck(i));
        EXPECT_NO_THROW(r->rowColCheck(i, 0));
    }

    // Verify an above range row is detected.
    EXPECT_THROW(r->rowCheck(num_rows), DbOperationError);
}

/// @brief Verify that we can read and write BOOL columns
TEST_F(PgSqlBasicsTest, boolTest) {
    // Create a prepared statement for inserting bool_col
    const char* st_name = "bool_insert";
    PgSqlTaggedStatement statement[] = {
     {1, { OID_BOOL }, st_name,
      "INSERT INTO BASICS (bool_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    bool bools[] = { true, false };
    PsqlBindArrayPtr bind_array(new PsqlBindArray());
    PgSqlResultPtr r;

    // Insert bool rows
    for (int i = 0; i < 2; ++i) {
        bind_array.reset(new PsqlBindArray());
        bind_array->add(bools[i]);
        RUN_PREP(r,statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, 2);

    // Verify the fetched bool values are what we expect.
    bool fetched_bool;
    int row = 0;
    for ( ; row  < 2; ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, BOOL_COL));

        // Fetch and verify the column value
        fetched_bool = !bools[row];
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, BOOL_COL,
                                                      fetched_bool));
        EXPECT_EQ(fetched_bool, bools[row]);
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, 1, fetched_bool),
                 DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL boolean
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();

    // Run the insert with the bind array.
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, 1));
}

/// @brief Verify that we can read and write BYTEA columns
TEST_F(PgSqlBasicsTest, byteaTest) {
    const char* st_name = "bytea_insert";
    PgSqlTaggedStatement statement[] = {
     {1, { OID_BYTEA }, st_name,
      "INSERT INTO BASICS (bytea_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    const uint8_t bytes[] = {
        0x01, 0x02, 0x03, 0x04
    };
    std::vector<uint8_t> vbytes(bytes, bytes + sizeof(bytes));

    // Verify we can insert bytea from a vector
    PsqlBindArrayPtr bind_array(new PsqlBindArray());
    PgSqlResultPtr r;
    bind_array->add(vbytes);
    RUN_PREP(r,statement[0], bind_array, PGRES_COMMAND_OK);

    // Verify we can insert bytea from a buffer.
    bind_array.reset(new PsqlBindArray());
    bind_array->add(bytes, sizeof(bytes));
    RUN_PREP(r,statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows.
    int num_rows = 2;
    FETCH_ROWS(r, num_rows);

    uint8_t fetched_bytes[sizeof(bytes)];
    size_t byte_count;
    int row = 0;
    for ( ; row < num_rows; ++row) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, BYTEA_COL));

        // Extract the data into a correctly sized buffer
        memset(fetched_bytes, 0, sizeof(fetched_bytes));
        ASSERT_NO_THROW(PgSqlExchange::convertFromBytea(*r, row, BYTEA_COL,
                                                        fetched_bytes,
                                                        sizeof(fetched_bytes),
                                                        byte_count));

        // Verify the data is correct
        ASSERT_EQ(byte_count, sizeof(bytes));
        for (int i = 0; i < sizeof(bytes); i++) {
            ASSERT_EQ(bytes[i], fetched_bytes[i]);
        }
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::convertFromBytea(*r, row, BYTEA_COL,
                                                 fetched_bytes,
                                                 sizeof(fetched_bytes),
                                                 byte_count), DbOperationError);

    // Verify that too small of a buffer throws
    ASSERT_THROW(PgSqlExchange::convertFromBytea(*r, 0, BYTEA_COL,
                                                 fetched_bytes,
                                                 sizeof(fetched_bytes) - 1,
                                                 byte_count), DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL for a bytea column
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull(PsqlBindArray::BINARY_FMT);
    RUN_PREP(r,statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, BYTEA_COL));

    // Verify that fetching a NULL bytea, returns 0 byte count
    ASSERT_NO_THROW(PgSqlExchange::convertFromBytea(*r, 0, BYTEA_COL,
                                                    fetched_bytes,
                                                    sizeof(fetched_bytes),
                                                    byte_count));
    EXPECT_EQ(byte_count, 0);
}

/// @brief Verify that we can read and write BIGINT columns
TEST_F(PgSqlBasicsTest, bigIntTest) {
    // Create a prepared statement for inserting BIGINT
    const char* st_name = "bigint_insert";
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_INT8 }, st_name,
          "INSERT INTO BASICS (bigint_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Build our reference list of reference values
    std::vector<int64_t> ints;
    ints.push_back(-1);
    ints.push_back(0);
    ints.push_back(0x7fffffffffffffff);
    ints.push_back(0xffffffffffffffff);

    // Insert a row for each reference value
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    for (int i = 0; i < ints.size(); ++i) {
        bind_array.reset(new PsqlBindArray());
        bind_array->add(ints[i]);
        RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, ints.size());

    // Iterate over the rows, verifying each value against its reference
    int64_t fetched_int;
    int row = 0;
    for ( ; row  < ints.size(); ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, BIGINT_COL));

        // Fetch and verify the column value
        fetched_int = 777;
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, BIGINT_COL,
                                                      fetched_int));
        EXPECT_EQ(fetched_int, ints[row]);
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, BIGINT_COL,
                                               fetched_int), DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, BIGINT_COL));
}

/// @brief Verify that we can read and write SMALLINT columns
TEST_F(PgSqlBasicsTest, smallIntTest) {
    // Create a prepared statement for inserting a SMALLINT
    const char* st_name = "smallint_insert";
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_INT2 }, st_name,
          "INSERT INTO BASICS (smallint_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Build our reference list of reference values
    std::vector<int16_t>ints;
    ints.push_back(-1);
    ints.push_back(0);
    ints.push_back(0x7fff);
    ints.push_back(0xffff);

    // Insert a row for each reference value
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    for (int i = 0; i < ints.size(); ++i) {
        bind_array.reset(new PsqlBindArray());
        bind_array->add(ints[i]);
        RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, ints.size());

    // Iterate over the rows, verifying each value against its reference
    int16_t fetched_int;
    int row = 0;
    for ( ; row  < ints.size(); ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, SMALLINT_COL));

        // Fetch and verify the column value
        fetched_int = 777;
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, SMALLINT_COL,
                                                      fetched_int));
        EXPECT_EQ(fetched_int, ints[row]);
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, SMALLINT_COL,
                                               fetched_int),
                 DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, SMALLINT_COL));
}

/// @brief Verify that we can read and write INT columns
TEST_F(PgSqlBasicsTest, intTest) {
    // Create a prepared statement for inserting an  INT
    const char* st_name = "int_insert";
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_INT4 }, st_name,
          "INSERT INTO BASICS (int_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Build our reference list of reference values
    std::vector<int32_t> ints;
    ints.push_back(-1);
    ints.push_back(0);
    ints.push_back(0x7fffffff);
    ints.push_back(0xffffffff);

    // Insert a row for each reference value
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    for (int i = 0; i < ints.size(); ++i) {
        bind_array.reset(new PsqlBindArray());
        bind_array->add(ints[i]);
        RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, ints.size());

    // Iterate over the rows, verifying each value against its reference
    int32_t fetched_int;
    int row = 0;
    for ( ; row  < ints.size(); ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, INT_COL));

        // Fetch and verify the column value
        fetched_int = 777;
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, INT_COL,
                                                      fetched_int));
        EXPECT_EQ(fetched_int, ints[row]);
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, INT_COL, fetched_int),
                 DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, INT_COL));
}

/// @brief Verify that we use the methods used for testing:
/// amNull(), getInteger<T>(), getType()
TEST_F(PgSqlBasicsTest, get) {
    PsqlBindArray bind_array;

    // The array itself is empty, its first column is not null
    EXPECT_THROW(bind_array.amNull(), OutOfRange);
    EXPECT_THROW(bind_array.getInteger<uint32_t>(), OutOfRange);
    EXPECT_THROW(bind_array.getType(), OutOfRange);

    // Now try again with proper values.
    bind_array.add(123); // This will be converted to "123" string.
    bind_array.addNull();
    bind_array.add("sagittarius");
    EXPECT_FALSE(bind_array.amNull(0)); // first column is not null
    EXPECT_TRUE(bind_array.amNull(1)); // second column is null
    EXPECT_FALSE(bind_array.amNull(2)); // third column is not null

    EXPECT_EQ(123, bind_array.getInteger<uint32_t>(0)); // first column is 123
    EXPECT_THROW(bind_array.getInteger<uint32_t>(1), BadValue);
    EXPECT_THROW(bind_array.getInteger<uint32_t>(2), boost::bad_lexical_cast);

    EXPECT_EQ(PsqlBindArray::TEXT_FMT, bind_array.getType(0));
    EXPECT_EQ(PsqlBindArray::TEXT_FMT, bind_array.getType(1));
    EXPECT_EQ(PsqlBindArray::TEXT_FMT, bind_array.getType(2));
}

/// @brief Verify that we can read and write TEXT columns
TEST_F(PgSqlBasicsTest, textTest) {
    // Create a prepared statement for inserting TEXT
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_TEXT }, "text_insert",
          "INSERT INTO BASICS (text_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Our reference string.
    std::string ref_string = "This is a text string";

    // Insert the reference from std::string
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    bind_array.reset(new PsqlBindArray());
    bind_array->add(ref_string);
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Insert the reference from a buffer
    bind_array.reset(new PsqlBindArray());
    bind_array->add(ref_string.c_str());
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, 2);

    // Iterate over the rows, verifying the value against the reference
    std::string fetched_str;
    int row = 0;
    for ( ; row  < 2; ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, TEXT_COL));

        // Fetch and verify the column value
        fetched_str = "";
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, TEXT_COL,
                                                      fetched_str));
        EXPECT_EQ(fetched_str, ref_string);
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, TEXT_COL, fetched_str),
                 DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, TEXT_COL));
}

/// @brief Verify that we can read and write VARCHAR columns
TEST_F(PgSqlBasicsTest, varcharTest) {
    // Create a prepared statement for inserting a VARCHAR
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_VARCHAR }, "varchar_insert",
          "INSERT INTO BASICS (varchar_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Our reference string.
    std::string ref_string = "This is a varchar string";

    // Insert the reference from std::string
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    bind_array.reset(new PsqlBindArray());
    bind_array->add(ref_string);
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Insert the reference from a buffer
    bind_array.reset(new PsqlBindArray());
    bind_array->add(ref_string.c_str());
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, 2);

    // Iterate over the rows, verifying the value against the reference
    std::string fetched_str;
    int row = 0;
    for ( ; row  < 2; ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, VARCHAR_COL));

        // Fetch and verify the column value
        fetched_str = "";
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, VARCHAR_COL,
                                                      fetched_str));
        EXPECT_EQ(fetched_str, ref_string);
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, VARCHAR_COL,
                                               fetched_str), DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, VARCHAR_COL));
}

/// @brief Verify that we can read and write TIMESTAMP columns
TEST_F(PgSqlBasicsTest, timeStampTest) {
    // Create a prepared statement for inserting a TIMESTAMP
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_TIMESTAMP }, "timestamp_insert",
          "INSERT INTO BASICS (timestamp_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Build our list of reference times
    time_t now;
    time(&now);
    std::vector<time_t> times;
    times.push_back(now);
    times.push_back(DatabaseConnection::MAX_DB_TIME);
    // Note on a 32-bit OS this value is really -1. PosgreSQL will store it
    // and return it intact.
    times.push_back(0xFFFFFFFF);

    // Insert a row for each reference value
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    std::string time_str;
    for (int i = 0; i < times.size(); ++i) {
        // Timestamps are inserted as strings so convert them first
        ASSERT_NO_THROW(time_str =
                        PgSqlExchange::convertToDatabaseTime(times[i]));

        // Add it to the bind array and insert it
        bind_array.reset(new PsqlBindArray());
        bind_array->add(time_str);
        RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Insert a row with ref time plus one day
    times.push_back(now + 24*3600);
    ASSERT_NO_THROW(time_str =
                    PgSqlExchange::convertToDatabaseTime(times[0], 24*3600));

    bind_array.reset(new PsqlBindArray());
    bind_array->add(time_str);
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, times.size());

    // Iterate over the rows, verifying the value against its reference
    std::string fetched_str;
    int row = 0;
    for ( ; row  < times.size(); ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, TIMESTAMP_COL));

        // Fetch and verify the column value
        fetched_str = "";
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, TIMESTAMP_COL,
                                                      fetched_str));

        time_t fetched_time;
        ASSERT_NO_THROW(fetched_time =
                        PgSqlExchange::convertFromDatabaseTime(fetched_str));
        EXPECT_EQ(fetched_time, times[row]) << " row: " << row;
    }

    // While we here, verify that bad row throws
    ASSERT_THROW(PgSqlExchange::getColumnValue(*r, row, TIMESTAMP_COL,
                                               fetched_str), DbOperationError);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted rows
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, TIMESTAMP_COL));

    // Verify exceeding max time throws
    ASSERT_THROW(PgSqlExchange::convertToDatabaseTime(times[0],
                                                      DatabaseConnection::
                                                      MAX_DB_TIME), BadValue);
}

/// @brief Verify that we can read and write ptime using TIMESTAMP columns.
TEST_F(PgSqlBasicsTest, ptimeTimestamp) {
    // Create a prepared statement for inserting a TIMESTAMP
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_TIMESTAMP }, "timestamp_insert",
          "INSERT INTO BASICS (localtime_col) values ($1)" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Create an empty array.
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Make sure we catch values that are too big.
    time_duration duration = hours(10) + minutes(14) + seconds(15);
    ptime day_too_far(date(2038, Jan, 21), duration);
    ASSERT_THROW_MSG(bind_array->addTimestamp(day_too_far), BadValue,
                     "Time value is too large: 2147681655");

    // Now add reasonable day, US National Ice Cream day.
    ptime nice_day(date(2021, Jul, 18), duration);
    bind_array->addTimestamp(nice_day);

    PgSqlResultPtr r;
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Timestamp column should not be null.
    ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, 0, LOCALTIME_COL));

    // Convert fetched value into a ptime.
    ptime fetched_time;
    ASSERT_NO_THROW_LOG(PgSqlExchange::getColumnValue(*r, 0, LOCALTIME_COL,
                        fetched_time));

    ASSERT_EQ(fetched_time, nice_day);
}

/// @brief Verifies the ability to insert a string into
/// the bind array.
TEST(PsqlBindArray, insertString) {
    PsqlBindArray b;

    // Make a non-temporary string to insert.
    std::string one("one");

    // Add all the items within a different scope. Everything should
    // still be valid once we exit this scope.
    {
        // Make sure you can "insert" at the front of an empty array.
        b.insert("two", 0);

        // Add a binding.
        b.add("four");

        // Verify an out of range index throws.
        ASSERT_THROW_MSG(b.insert(std::string("too far"), 5), OutOfRange,
                         "PsqlBindArray::insert - index: 5, "
                         "is larger than the array size: 2");

        // Insert a non-temporary string at the front.
        b.insert(one, 0);

        // Insert a temporary string.
        b.insert("three", 2);

        // Add another one.
        b.add("five");
    }

    // We've left bind scope, everything should be intact.
    EXPECT_EQ(5, b.size());

    // Verify contents are correct.
    std::string expected =
        "0 : \"one\"\n"
        "1 : \"two\"\n"
        "2 : \"three\"\n"
        "3 : \"four\"\n"
        "4 : \"five\"\n";

    EXPECT_EQ(expected, b.toText());
}

/// @brief Verifies the ability to pop bindings off
/// the end of a bind array.
TEST(PsqlBindArray, popBackTest) {
    PsqlBindArray b;

    // Popping on an empty array should throw.
    ASSERT_THROW_MSG(b.popBack(), OutOfRange,
                     "PsqlBindArray::pop_back - array empty");

    // Add five integers.
    for (int i = 1; i < 6; ++i) {
        b.add(i);
    }

    // Verify size.
    EXPECT_EQ(b.size(), 5);

    // Pop one off.
    ASSERT_NO_THROW_LOG(b.popBack());

    // Verify size.
    EXPECT_EQ(b.size(), 4);

    // Pop another one off.
    ASSERT_NO_THROW_LOG(b.popBack());

    // Verify size.
    EXPECT_EQ(b.size(), 3);

    // This is what we should have left.
    std::string expected =
        "0 : \"1\"\n"
        "1 : \"2\"\n"
        "2 : \"3\"\n";

    EXPECT_EQ(expected, b.toText());
}

/// @brief Verify that we can read and write IPv4 addresses
/// using INET columns.
TEST_F(PgSqlBasicsTest, inetTest4) {
    // Create a prepared statement for inserting an IPv4 address
    const char* st_name = "inet4_insert";
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_TEXT }, st_name,
          "INSERT INTO BASICS (inet4_col) values (cast($1 as inet))" },
        { 1, { OID_TEXT }, "check_where",
          "select * from BASICS where inet4_col = cast($1 as inet)" }
    };

    ASSERT_NO_THROW_LOG(conn_->prepareStatement(statement[0]));
    ASSERT_NO_THROW_LOG(conn_->prepareStatement(statement[1]));

    // Build our reference list of reference values
    std::vector<asiolink::IOAddress>inets;
    inets.push_back(asiolink::IOAddress("0.0.0.0"));
    inets.push_back(asiolink::IOAddress("192.168.1.9"));
    inets.push_back(asiolink::IOAddress("192.168.1.1"));

    // Insert a row for each reference value
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    for (int i = 0; i < inets.size(); ++i) {
        bind_array.reset(new PsqlBindArray());
        bind_array->addInet4(inets[i]);
        RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, inets.size());

    // Iterate over the rows, verifying each value against its reference
    int row = 0;
    asiolink::IOAddress fetched_inet("0.0.0.0");
    for ( ; row  < inets.size(); ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, INET4_COL));

        // Fetch and verify the column value
        ASSERT_NO_THROW(fetched_inet = PgSqlExchange::getInetValue4(*r, row, INET4_COL));
        EXPECT_EQ(fetched_inet, inets[row]);
    }

    // Verify that casting from string to inet works in where clauses.
    r.reset();
    bind_array.reset(new PsqlBindArray());
    bind_array->addInet4(inets[1]);
    RUN_PREP(r, statement[1], bind_array, PGRES_TUPLES_OK);
    ASSERT_EQ(r->getRows(),1);
    ASSERT_NO_THROW(fetched_inet = PgSqlExchange::getInetValue4(*r, 0, INET4_COL));
    EXPECT_EQ(fetched_inet, inets[1]);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, INET4_COL));
}

/// @brief Verify that we can read and write IPv6 addresses
/// using INET columns.
TEST_F(PgSqlBasicsTest, inetTest6) {
    // Create a prepared statement for inserting an IPv6 address
    const char* st_name = "inet6_insert";
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_TEXT }, st_name,
          "INSERT INTO BASICS (inet6_col) values (cast($1 as inet))" },
        { 1, { OID_TEXT }, "check_where",
          "select * from BASICS where inet6_col = cast($1 as inet)" }
    };

    ASSERT_NO_THROW_LOG(conn_->prepareStatement(statement[0]));
    ASSERT_NO_THROW_LOG(conn_->prepareStatement(statement[1]));

    // Build our reference list of reference values
    std::vector<asiolink::IOAddress>inets;
    inets.push_back(asiolink::IOAddress("::"));
    inets.push_back(asiolink::IOAddress("3001::1"));

    // Insert a row for each reference value
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    for (int i = 0; i < inets.size(); ++i) {
        bind_array.reset(new PsqlBindArray());
        bind_array->addInet6(inets[i]);
        RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, inets.size());

    // Iterate over the rows, verifying each value against its reference
    int row = 0;
    asiolink::IOAddress fetched_inet("::");
    for ( ; row  < inets.size(); ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, INET6_COL));

        // Fetch and verify the column value
        ASSERT_NO_THROW(fetched_inet = PgSqlExchange::getInetValue6(*r, row, INET6_COL));
        EXPECT_EQ(fetched_inet, inets[row]);
    }

    // Verify that casting from string to inet works in where clauses.
    r.reset();
    bind_array.reset(new PsqlBindArray());
    bind_array->addInet6(inets[1]);
    RUN_PREP(r, statement[1], bind_array, PGRES_TUPLES_OK);
    ASSERT_EQ(r->getRows(),1);
    ASSERT_NO_THROW(fetched_inet = PgSqlExchange::getInetValue6(*r, 0, INET6_COL));
    EXPECT_EQ(fetched_inet, inets[1]);

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, INET6_COL));
}

/// @brief Verify that we can read and write floats
TEST_F(PgSqlBasicsTest, floatTest) {
    // Create a prepared statement for inserting a FLOAT
    const char* st_name = "float_insert";
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_TEXT }, st_name,
          "INSERT INTO BASICS (float_col) values (cast($1 as float))" }
    };

    ASSERT_NO_THROW(conn_->prepareStatement(statement[0]));

    // Build our reference list of reference values
    std::vector<double>floats;
    floats.push_back(1.345);
    floats.push_back(200);

    // Insert a row for each reference value
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    for (int i = 0; i < floats.size(); ++i) {
        bind_array.reset(new PsqlBindArray());
        bind_array->add(floats[i]);
        RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, floats.size());

    // Iterate over the rows, verifying each value against its reference
    int row = 0;
    for ( ; row  < floats.size(); ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, FLOAT_COL));

        // Fetch and verify the column value
        double fetched_float;
        ASSERT_NO_THROW(PgSqlExchange::getColumnValue(*r, row, FLOAT_COL, fetched_float));
        EXPECT_EQ(fetched_float, floats[row]);
    }

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, FLOAT_COL));
}

/// @brief Verify that we can read and write JSON columns.
TEST_F(PgSqlBasicsTest, jsonTest) {
    // Create a prepared statement for inserting a JSON
    const char* st_name = "json_insert";
    PgSqlTaggedStatement statement[] = {
        { 1, { OID_TEXT }, st_name,
          "INSERT INTO BASICS (json_col) values (cast($1 as json))" }
    };

    ASSERT_NO_THROW_LOG(conn_->prepareStatement(statement[0]));

    // Build our reference list of reference values
    std::vector<ElementPtr>elem_ptrs;
    ASSERT_NO_THROW_LOG(elem_ptrs.push_back(Element::fromJSON("{ \"one\":1 }")));
    ASSERT_NO_THROW_LOG(elem_ptrs.push_back(Element::fromJSON("{ \"two\":\"two\" }")));

    // Insert a row for each reference value
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    for (int i = 0; i < elem_ptrs.size(); ++i) {
        bind_array.reset(new PsqlBindArray());
        bind_array->add(elem_ptrs[i]);
        RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, elem_ptrs.size());

    // Iterate over the rows, verifying each value against its reference
    int row = 0;
    for ( ; row  < elem_ptrs.size(); ++row ) {
        // Verify the column is not null.
        ASSERT_FALSE(PgSqlExchange::isColumnNull(*r, row, JSON_COL));

        // Fetch and verify the column value
        ElementPtr fetched_ptr;
        ASSERT_NO_THROW_LOG(PgSqlExchange::getColumnValue(*r, row, JSON_COL, fetched_ptr));
        EXPECT_TRUE(fetched_ptr->equals(*(elem_ptrs[row])));
    }

    // Clean out the table
    WIPE_ROWS(r);

    // Verify we can insert a NULL value.
    bind_array.reset(new PsqlBindArray());
    bind_array->addNull();
    RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Verify the column is null.
    ASSERT_TRUE(PgSqlExchange::isColumnNull(*r, 0, JSON_COL));
}

/// @brief Verify that we can read and write integer Triplets.
TEST_F(PgSqlBasicsTest, tripleTest) {
    // Create a prepared statement for inserting a Triplet
    const char* st_name = "triplets_insert";
    PgSqlTaggedStatement statement[] = {
        { 3, { OID_INT4, OID_INT4, OID_INT4 }, st_name,
          "INSERT INTO BASICS (int_col, min_int_col, max_int_col) values ($1, $2, $3)" }
    };

    ASSERT_NO_THROW_LOG(conn_->prepareStatement(statement[0]));

    // Build our reference list of reference values
    std::vector<Triplet<uint32_t>> triplets;
    triplets.push_back(Triplet<uint32_t>());          // def column is null
    triplets.push_back(Triplet<uint32_t>(10));        // only default column
    triplets.push_back(Triplet<uint32_t>(5,10,15));   // all three columns
    triplets.push_back(Triplet<uint32_t>(10,10,15));  // min column is null
    triplets.push_back(Triplet<uint32_t>(5,10,10));   // max column is null

    // Insert a row for each reference value
    PsqlBindArrayPtr bind_array;
    PgSqlResultPtr r;
    for (auto triplet : triplets) {
        bind_array.reset(new PsqlBindArray());
        bind_array->add(triplet);
        bind_array->addMin(triplet);
        bind_array->addMax(triplet);
        RUN_PREP(r, statement[0], bind_array, PGRES_COMMAND_OK);
    }

    // Fetch the newly inserted rows.
    FETCH_ROWS(r, triplets.size());

    // Iterate over the rows, verifying each value against its reference
    int row = 0;
    for (auto expected : triplets) {
        Triplet<uint32_t> fetched;
        // First we test making a triplet only with default value column.
        ASSERT_NO_THROW_LOG(fetched = PgSqlExchange::getTripletValue(*r, row, INT_COL));
        if (expected.unspecified()) {
            EXPECT_TRUE(fetched.unspecified());
        } else {
            EXPECT_FALSE(fetched.unspecified());
            EXPECT_EQ(fetched.get(), expected.get());
        }

        // Now test making a triplet with all three columns.
        ASSERT_NO_THROW_LOG(
            fetched = PgSqlExchange::getTripletValue(*r, row,
                                                     INT_COL, MIN_INT_COL, MAX_INT_COL));
        if (expected.unspecified()) {
            EXPECT_TRUE(fetched.unspecified());
        } else {
            EXPECT_FALSE(fetched.unspecified());
            EXPECT_EQ(fetched.get(), expected.get());
            EXPECT_EQ(fetched.getMin(), expected.getMin());
            EXPECT_EQ(fetched.getMax(), expected.getMax());
        }

        ++row;
    }

    // Clean out the table
    WIPE_ROWS(r);
}

/// @brief Verify PgResultRowWorker operations.
TEST_F(PgSqlBasicsTest, resultRowWorker) {
    // Create a prepared statement for inserting multiple types
    const char* st_name = "row_insert";
    PgSqlTaggedStatement statement[] = {
        { 14,
          {
            OID_BOOL,
            OID_BYTEA,
            OID_INT8,
            OID_INT2,
            OID_INT4,
            OID_TEXT,
            OID_TIMESTAMP,
            OID_TEXT,
            OID_TEXT,
            OID_TEXT,
            OID_TEXT,
            OID_INT4,
            OID_INT4,
          }, st_name,
          "INSERT INTO BASICS ("
          " bool_col, "
          " bytea_col, "
          " bigint_col, "
          " smallint_col, "
          " int_col, "
          " text_col, "
          " localtime_col, "
          " varchar_col, "
          " inet4_col, "
          " float_col, "
          " json_col, "
          " min_int_col, "
          " max_int_col, "
          " inet6_col) "
          " VALUES ($1, $2, $3, $4, $5, $6, $7, $8, cast($9 as inet), "
          "         cast($10 as float), cast($11 as json), $12, $13, $14)"
        }
    };

    ASSERT_NO_THROW_LOG(conn_->prepareStatement(statement[0]));

    // Create a bind array of input values.
    PsqlBindArrayPtr b(new PsqlBindArray());

    bool exp_bool(true);
    b->add(exp_bool);

    std::vector<uint8_t> exp_bytes({0x01, 0x02, 0x03, 0x04});
    b->add(exp_bytes);

    uint64_t exp_bigint = 9876;
    b->add(exp_bigint);

    uint16_t exp_smallint = 12;
    b->add(exp_smallint);

    uint32_t exp_int = 345;
    b->add(exp_int);

    std::string exp_text = "just some string";
    b->add(exp_text);

    time_duration duration = hours(7) + minutes(45) + seconds(9);
    ptime exp_timestamp(date(2021, Jul, 18), duration);
    b->addTimestamp(exp_timestamp);

    const char* exp_varchar = "really just a string";
    b->add(exp_varchar);

    asiolink::IOAddress exp_inet4("192.168.1.35");
    b->addInet4(exp_inet4);

    double exp_double(2.5);
    b->add(exp_double);

    ElementPtr exp_elems = Element::fromJSON("{ \"foo\": \"bar\" }");
    b->add(exp_elems);

    uint32_t exp_min = 100;
    b->add(exp_min);

    uint32_t exp_max = 500;
    b->add(exp_max);

    asiolink::IOAddress exp_inet6("3001::77");
    b->addInet6(exp_inet6);

    PgSqlResultPtr r;
    RUN_PREP(r, statement[0], b, PGRES_COMMAND_OK);

    // Fetch the newly inserted row.
    FETCH_ROWS(r, 1);

    // Create a row worker.
    PgSqlResultRowWorkerPtr worker;

    // Creating the row worker for the first (and only) row should succeed.
    ASSERT_NO_THROW_LOG(worker.reset(new PgSqlResultRowWorker(*r, 0)));

    // Now let's test all the getters.
    EXPECT_EQ(exp_bool, worker->getBool(BOOL_COL));

    std::vector<uint8_t> fetched_bytes;
    ASSERT_NO_THROW_LOG(worker->getBytes(BYTEA_COL, fetched_bytes));
    EXPECT_EQ(exp_bytes, fetched_bytes);

    EXPECT_EQ(exp_bigint, worker->getBigInt(BIGINT_COL));
    EXPECT_EQ(exp_smallint, worker->getSmallInt(SMALLINT_COL));
    EXPECT_EQ(exp_int, worker->getInt(INT_COL));
    EXPECT_EQ(exp_text, worker->getString(TEXT_COL));
    EXPECT_EQ(exp_timestamp, worker->getTimestamp(LOCALTIME_COL));
    EXPECT_EQ(exp_varchar, worker->getString(VARCHAR_COL));
    EXPECT_EQ(exp_inet4, worker->getInet4(INET4_COL));
    EXPECT_EQ(exp_double, worker->getDouble(FLOAT_COL));
    EXPECT_EQ(*exp_elems, *(worker->getJSON(JSON_COL)));
    EXPECT_EQ(exp_min, worker->getInt(MIN_INT_COL));
    EXPECT_EQ(exp_max, worker->getInt(MAX_INT_COL));
    EXPECT_EQ(exp_inet6, worker->getInet6(INET6_COL));

    // Get a triplet using int_col as the sole value.
    Triplet<uint32_t>fetched_triplet = worker->getTriplet(INT_COL);
    EXPECT_EQ(exp_int, fetched_triplet.get());

    // Get a triplet using int_col, min_col, and max_col values.
    fetched_triplet = worker->getTriplet(INT_COL, MIN_INT_COL, MAX_INT_COL);
    EXPECT_EQ(exp_int, fetched_triplet.get());
    EXPECT_EQ(exp_min, fetched_triplet.getMin());
    EXPECT_EQ(exp_max, fetched_triplet.getMax());

    // Attempting to access an invalid row should throw.
    ASSERT_THROW_MSG(worker.reset(new PgSqlResultRowWorker(*r, 1)),
                     DbOperationError, "row: 1, out of range: 0..1");
}

} // namespace
