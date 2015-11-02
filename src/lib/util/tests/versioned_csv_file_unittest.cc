// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <util/versioned_csv_file.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <string>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>

namespace {

using namespace isc::util;

/// @brief Test fixture class for testing operations on VersionedCSVFile.
///
/// It implements basic operations on files, such as reading writing
/// file removal and checking presence of the file. This is used by
/// unit tests to verify correctness of the file created by the
/// CSVFile class.
class VersionedCSVFileTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Sets the path to the CSV file used throughout the tests.
    /// The name of the file is test.csv and it is located in the
    /// current build folder.
    ///
    /// It also deletes any dangling files after previous tests.
    VersionedCSVFileTest();

    /// @brief Destructor.
    ///
    /// Deletes the test CSV file if any.
    virtual ~VersionedCSVFileTest();

    /// @brief Prepends the absolute path to the file specified
    /// as an argument.
    ///
    /// @param filename Name of the file.
    /// @return Absolute path to the test file.
    static std::string absolutePath(const std::string& filename);

    /// @brief Check if test file exists on disk.
    bool exists() const;

    /// @brief Reads whole CSV file.
    ///
    /// @return Contents of the file.
    std::string readFile() const;

    /// @brief Removes existing file (if any).
    int removeFile() const;

    /// @brief Creates file with contents.
    ///
    /// @param contents Contents of the file.
    void writeFile(const std::string& contents) const;

    /// @brief Absolute path to the file used in the tests.
    std::string testfile_;

};

VersionedCSVFileTest::VersionedCSVFileTest()
    : testfile_(absolutePath("test.csv")) {
    static_cast<void>(removeFile());
}

VersionedCSVFileTest::~VersionedCSVFileTest() {
    static_cast<void>(removeFile());
}

std::string
VersionedCSVFileTest::absolutePath(const std::string& filename) {
    std::ostringstream s;
    s << TEST_DATA_BUILDDIR << "/" << filename;
    return (s.str());
}

bool
VersionedCSVFileTest::exists() const {
    std::ifstream fs(testfile_.c_str());
    bool ok = fs.good();
    fs.close();
    return (ok);
}

std::string
VersionedCSVFileTest::readFile() const {
    std::ifstream fs(testfile_.c_str());
    if (!fs.is_open()) {
        return ("");
    }
    std::string contents((std::istreambuf_iterator<char>(fs)),
                         std::istreambuf_iterator<char>());
    fs.close();
    return (contents);
}

int
VersionedCSVFileTest::removeFile() const {
    return (remove(testfile_.c_str()));
}

void
VersionedCSVFileTest::writeFile(const std::string& contents) const {
    std::ofstream fs(testfile_.c_str(), std::ofstream::out);
    if (fs.is_open()) {
        fs << contents;
        fs.close();
    }
}

// This test checks that the function which is used to add columns of the
// CSV file works as expected.
TEST_F(VersionedCSVFileTest, addColumn) {
    boost::scoped_ptr<VersionedCSVFile> csv(new VersionedCSVFile(testfile_));

    // Verify that we're not allowed to open it without the schema
    ASSERT_THROW(csv->open(), VersionedCSVFileError);

    // Add two columns.
    ASSERT_NO_THROW(csv->addColumn("animal", "1.0", ""));
    ASSERT_NO_THROW(csv->addColumn("color", "2.0", "blue"));

    // Make sure we can't add duplicates.
    EXPECT_THROW(csv->addColumn("animal", "1.0", ""), CSVFileError);
    EXPECT_THROW(csv->addColumn("color", "2.0", "blue"), CSVFileError);

    // But we should still be able to add unique columns.
    EXPECT_NO_THROW(csv->addColumn("age", "3.0", "21"));

    // Assert that the file is opened, because the rest of the test relies
    // on this.
    ASSERT_NO_THROW(csv->recreate());
    ASSERT_TRUE(exists());

    // Make sure we can't add columns (even unique) when the file is open.
    ASSERT_THROW(csv->addColumn("zoo", "3.0", ""), CSVFileError);

    // Close the file.
    ASSERT_NO_THROW(csv->close());
    // And check that now it is possible to add the column.
    EXPECT_NO_THROW(csv->addColumn("zoo", "3.0", ""));
}

// Verifies the basic ability to upgrade valid files. 
// It starts with a version 1.0 file and updates
// it through two schema evolutions.
TEST_F(VersionedCSVFileTest, upgradeOlderVersions) {

    // Create version 1.0 schema  CSV file 
    writeFile("animal\n"
              "cat\n"
              "lion\n"
              "dog\n");

    // Create our versioned file, with two columns, one for each
    // schema version
    boost::scoped_ptr<VersionedCSVFile> csv(new VersionedCSVFile(testfile_));
    ASSERT_NO_THROW(csv->addColumn("animal", "1.0", ""));
    ASSERT_NO_THROW(csv->addColumn("color", "2.0", "blue"));

    // Header should pass validation and allow the open to succeed.
    ASSERT_NO_THROW(csv->open());

    // First row is correct.
    CSVRow row;
    ASSERT_TRUE(csv->next(row));
    EXPECT_EQ("cat", row.readAt(0));
    EXPECT_EQ("blue", row.readAt(1));

    // Second row is correct.
    ASSERT_TRUE(csv->next(row));
    EXPECT_EQ("lion", row.readAt(0));
    EXPECT_EQ("blue", row.readAt(1));

    // Third row is correct.
    ASSERT_TRUE(csv->next(row));
    EXPECT_EQ("dog", row.readAt(0));
    EXPECT_EQ("blue", row.readAt(1));

    // Now, let's try to append something to this file.
    CSVRow row_write(2);
    row_write.writeAt(0, "bird");
    row_write.writeAt(1, "yellow");
    ASSERT_NO_THROW(csv->append(row_write));

    // Close the file
    ASSERT_NO_THROW(csv->flush());
    ASSERT_NO_THROW(csv->close());


    // Check the the file contents are correct.
    EXPECT_EQ("animal\n"
              "cat\n"
              "lion\n"
              "dog\n"
              "bird,yellow\n",
              readFile());

    // Create a third schema by adding a column
    ASSERT_NO_THROW(csv->addColumn("age", "3.0", "21"));
    ASSERT_EQ(3, csv->getColumnCount());

    // Header should pass validation and allow the open to succeed
    ASSERT_NO_THROW(csv->open());
    ASSERT_EQ(3, csv->getColumnCount());

    // First row is correct.
    ASSERT_TRUE(csv->next(row));
    EXPECT_EQ("cat", row.readAt(0));
    EXPECT_EQ("blue", row.readAt(1));
    EXPECT_EQ("21", row.readAt(2));

    // Second row is correct.
    ASSERT_TRUE(csv->next(row));
    EXPECT_EQ("lion", row.readAt(0));
    EXPECT_EQ("blue", row.readAt(1));
    EXPECT_EQ("21", row.readAt(2));

    // Third row is correct.
    ASSERT_TRUE(csv->next(row));
    EXPECT_EQ("dog", row.readAt(0));
    EXPECT_EQ("blue", row.readAt(1));
    EXPECT_EQ("21", row.readAt(2));

    ASSERT_EQ(3, csv->getColumnCount());

    // Fourth row is correct.
    if (!csv->next(row)) {
        std::cout << "row error is : " << 
           csv->getReadMsg() << std::endl; 
    
    }

    EXPECT_EQ("bird", row.readAt(0));
    EXPECT_EQ("yellow", row.readAt(1));
    EXPECT_EQ("21", row.readAt(2));
}

TEST_F(VersionedCSVFileTest, minimumValidColumn) {
    // Create version 1.0 schema  CSV file 
    writeFile("animal\n"
              "cat\n"
              "lion\n"
              "dog\n");

    // Create our versioned file, with three columns, one for each
    // schema version
    boost::scoped_ptr<VersionedCSVFile> csv(new VersionedCSVFile(testfile_));
    ASSERT_NO_THROW(csv->addColumn("animal", "1.0", ""));
    ASSERT_NO_THROW(csv->addColumn("color", "2.0", "blue"));
    ASSERT_NO_THROW(csv->addColumn("age", "3.0", "21"));

    // Verify we can't set minimum columns with a non-existant column
    EXPECT_THROW(csv->setMinimumValidColumns("bogus"), VersionedCSVFileError);

    // Set the minimum number of columns to "color"
    csv->setMinimumValidColumns("color");
    EXPECT_EQ(2, csv->getMinimumValidColumns());

    // Header validation should fail, too few columns
    ASSERT_THROW(csv->open(), CSVFileError);

    // Set the minimum number of columns to 1.  File should parse now.
    csv->setMinimumValidColumns("animal");
    EXPECT_EQ(1, csv->getMinimumValidColumns());
    ASSERT_NO_THROW(csv->open());

    // First row is correct.
    CSVRow row;
    ASSERT_TRUE(csv->next(row));
    EXPECT_EQ("cat", row.readAt(0));
    EXPECT_EQ("blue", row.readAt(1));
    EXPECT_EQ("21", row.readAt(2));

    ASSERT_TRUE(csv->next(row));
    EXPECT_EQ("lion", row.readAt(0));
    EXPECT_EQ("blue", row.readAt(1));
    EXPECT_EQ("21", row.readAt(2));

    ASSERT_TRUE(csv->next(row));
    EXPECT_EQ("dog", row.readAt(0));
    EXPECT_EQ("blue", row.readAt(1));
    EXPECT_EQ("21", row.readAt(2));
}

TEST_F(VersionedCSVFileTest, invalidHeaderColumn) {

    // Create version 2.0 schema  CSV file 
    writeFile("animal,colour\n"
              "cat,red\n"
              "lion,green\n");

    // Create our versioned file, with three columns, one for each
    // schema version
    boost::scoped_ptr<VersionedCSVFile> csv(new VersionedCSVFile(testfile_));
    ASSERT_NO_THROW(csv->addColumn("animal", "1.0", ""));
    ASSERT_NO_THROW(csv->addColumn("color", "2.0", "blue"));

    // Header validation should fail, we have an invalid column
    ASSERT_THROW(csv->open(), CSVFileError);
}

TEST_F(VersionedCSVFileTest, tooManyHeaderColumns) {

    // Create version 2.0 schema  CSV file 
    writeFile("animal,color,age\n,"
              "cat,red\n"
              "lion,green\n");

    // Create our versioned file, with three columns, one for each
    // schema version
    boost::scoped_ptr<VersionedCSVFile> csv(new VersionedCSVFile(testfile_));
    ASSERT_NO_THROW(csv->addColumn("animal", "1.0", ""));
    ASSERT_NO_THROW(csv->addColumn("color", "2.0", "blue"));

    // Header validation should fail, we have too many columns 
    ASSERT_THROW(csv->open(), CSVFileError);
}


TEST_F(VersionedCSVFileTest, rowChecking) {
    // Create version 2.0 schema CSV file with a
    // - valid header 
    // - row 0 has too many values
    // - row 1 is valid
    // - row 3 is too few values
    writeFile("animal,color\n"
              "cat,red,bogus_row_value\n"
              "lion,green\n"
              "too_few\n");

    // Create our versioned file, with two columns, one for each
    // schema version
    boost::scoped_ptr<VersionedCSVFile> csv(new VersionedCSVFile(testfile_));
    csv->addColumn("animal", "1.0", "");
    csv->addColumn("color", "2.0", "blue");

    // Header validation should pass, so we can open
    ASSERT_NO_THROW(csv->open());

    CSVRow row;
    // First row has too many
    EXPECT_FALSE(csv->next(row));

    // Second row is valid
    ASSERT_TRUE(csv->next(row));
    EXPECT_EQ("lion", row.readAt(0));
    EXPECT_EQ("green", row.readAt(1));

    // Third row has too few
    EXPECT_FALSE(csv->next(row));
}

} // end of anonymous namespace
