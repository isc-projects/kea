// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <util/csv_file.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <string>

namespace {

using namespace isc::util;

// This test checks that the single data row is parsed.
TEST(CSVRow, parse) {
    CSVRow row0("foo,bar,foo-bar");
    ASSERT_EQ(3, row0.getValuesCount());
    EXPECT_EQ("foo", row0.readAt(0));
    EXPECT_EQ("bar", row0.readAt(1));
    EXPECT_EQ("foo-bar", row0.readAt(2));

    row0.parse("bar,,foo-bar");
    ASSERT_EQ(3, row0.getValuesCount());
    EXPECT_EQ("bar", row0.readAt(0));
    EXPECT_TRUE(row0.readAt(1).empty());
    EXPECT_EQ("foo-bar", row0.readAt(2));

    CSVRow row1("foo-bar|foo|bar|", '|');
    ASSERT_EQ(4, row1.getValuesCount());
    EXPECT_EQ("foo-bar", row1.readAt(0));
    EXPECT_EQ("foo", row1.readAt(1));
    EXPECT_EQ("bar", row1.readAt(2));
    EXPECT_TRUE(row1.readAt(3).empty());

    row1.parse("");
    ASSERT_EQ(1, row1.getValuesCount());
    EXPECT_TRUE(row1.readAt(0).empty());
}

// This test checks that the text representation of the CSV row
// is created correctly.
TEST(CSVRow, render) {
    CSVRow row0(3);
    row0.writeAt(0, "foo");
    row0.writeAt(1, "foo-bar");
    row0.writeAt(2, "bar");

    std::string text;
    ASSERT_NO_THROW(text = row0.render());
    EXPECT_EQ(text, "foo,foo-bar,bar");

    CSVRow row1(4, ';');
    row1.writeAt(0, "foo");
    row1.writeAt(2, "bar");
    row1.writeAt(3, 10);

    ASSERT_NO_THROW(text = row1.render());
    EXPECT_EQ(text, "foo;;bar;10");

    CSVRow row2(0);
    ASSERT_NO_THROW(text = row2.render());
    EXPECT_TRUE(text.empty());
}

// This test checks that the data values can be set for the CSV row.
TEST(CSVRow, writeAt) {
    CSVRow row(3);
    row.writeAt(0, 10);
    row.writeAt(1, "foo");
    row.writeAt(2, "bar");

    EXPECT_EQ("10", row.readAt(0));
    EXPECT_EQ("foo", row.readAt(1));
    EXPECT_EQ("bar", row.readAt(2));

    EXPECT_THROW(row.writeAt(3, 20), CSVFileError);
    EXPECT_THROW(row.writeAt(3, "foo"), CSVFileError);
}

/// @brief Test fixture class for testing operations on CSV file.
///
/// It implements basic operations on files, such as reading writing
/// file removal and checking presence of the file. This is used by
/// unit tests to verify correctness of the file created by the
/// CSVFile class.
class CSVFileTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Sets the path to the CSV file used throughout the tests.
    /// The name of the file is test.csv and it is located in the
    /// current build folder.
    ///
    /// It also deletes any dangling files after previous tests.
    CSVFileTest();

    /// @brief Destructor.
    ///
    /// Deletes the test CSV file if any.
    virtual ~CSVFileTest();

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
    void removeFile() const;

    /// @brief Creates file with contents.
    ///
    /// @param contents Contents of the file.
    void writeFile(const std::string& contents) const;

    std::string testfile_;

};

CSVFileTest::CSVFileTest()
    : testfile_(absolutePath("test.csv")) {
    removeFile();
}

CSVFileTest::~CSVFileTest() {
    removeFile();
}

std::string
CSVFileTest::absolutePath(const std::string& filename) {
    std::ostringstream s;
    s << TEST_DATA_BUILDDIR << "/" << filename;
    return (s.str());
}

bool
CSVFileTest::exists() const {
    std::ifstream fs(testfile_.c_str());
    bool ok = fs.good();
    fs.close();
    return (ok);
}

std::string
CSVFileTest::readFile() const {
    std::ifstream fs(testfile_.c_str());
    if (!fs.is_open()) {
        return ("");
    }
    std::string contents((std::istreambuf_iterator<char>(fs)),
                         std::istreambuf_iterator<char>());
    fs.close();
    return (contents);
}

void
CSVFileTest::removeFile() const {
    remove(testfile_.c_str());
}

void
CSVFileTest::writeFile(const std::string& contents) const {
    std::ofstream fs(testfile_.c_str(), std::ofstream::out);
    if (fs.is_open()) {
        fs << contents;
        fs.close();
    }
}

// This test checks that the file can be opened and its content
// parsed correctly. It also checks that empty row is returned
// when EOF is reached.
TEST_F(CSVFileTest, open) {
    writeFile("animal,age,color\n"
              "cat,10,white\n"
              "lion,15,yellow\n");
    boost::scoped_ptr<CSVFile> csv(new CSVFile(testfile_));
    ASSERT_NO_THROW(csv->open());
    ASSERT_EQ(3, csv->getColumnCount());
    EXPECT_EQ("animal", csv->getColumnName(0));
    EXPECT_EQ("age", csv->getColumnName(1));
    EXPECT_EQ("color", csv->getColumnName(2));

    CSVRow row(0);
    ASSERT_NO_THROW(csv->next(row));
    ASSERT_EQ(3, row.getValuesCount());
    EXPECT_EQ("cat", row.readAt(0));
    EXPECT_EQ("10", row.readAt(1));
    EXPECT_EQ("white", row.readAt(2));

    ASSERT_NO_THROW(csv->next(row));
    ASSERT_EQ(3, row.getValuesCount());
    EXPECT_EQ("lion", row.readAt(0));
    EXPECT_EQ("15", row.readAt(1));
    EXPECT_EQ("yellow", row.readAt(2));

    ASSERT_NO_THROW(csv->next(row));
    EXPECT_EQ(CSVFile::EMPTY_ROW(), row);
}

// This test checks that a file can be used both for reading
// and writing. When content is appended to the end of file,
// an attempt to read results in empty row returned.
TEST_F(CSVFileTest, openReadWrite) {
    writeFile("animal,age,color\n"
              "cat,10,white\n"
              "lion,15,yellow\n");
    boost::scoped_ptr<CSVFile> csv(new CSVFile(testfile_));
    ASSERT_NO_THROW(csv->open());

    CSVRow row0(0);
    ASSERT_NO_THROW(csv->next(row0));
    ASSERT_EQ(3, row0.getValuesCount());
    EXPECT_EQ("cat", row0.readAt(0));
    EXPECT_EQ("10", row0.readAt(1));
    EXPECT_EQ("white", row0.readAt(2));

    CSVRow row_write(3);
    row_write.writeAt(0, "dog");
    row_write.writeAt(1, 2);
    row_write.writeAt(2, "blue");
    ASSERT_NO_THROW(csv->append(row_write));

    CSVRow row1(0);
    ASSERT_NO_THROW(csv->next(row1));
    EXPECT_EQ(CSVFile::EMPTY_ROW(), row1);
}

// This test checks that the new CSV file is created and header
// is written to it. It also checks that data rows can be
// appended to it.
TEST_F(CSVFileTest, recreate) {
    boost::scoped_ptr<CSVFile> csv(new CSVFile(testfile_));
    csv->addColumn("animal");
    csv->addColumn("color");
    csv->addColumn("age");
    csv->addColumn("comments");
    ASSERT_NO_THROW(csv->recreate());
    ASSERT_TRUE(exists());

    CSVRow row0(4);
    row0.writeAt(0, "dog");
    row0.writeAt(1, "grey");
    row0.writeAt(2, 3);
    row0.writeAt(3, "nice one");
    ASSERT_NO_THROW(csv->append(row0));

    CSVRow row1(4);
    row1.writeAt(0, "cat");
    row1.writeAt(1, "black");
    row1.writeAt(2, 2);
    ASSERT_NO_THROW(csv->append(row1));

    EXPECT_EQ("animal,color,age,comments\n"
              "dog,grey,3,nice one\n"
              "cat,black,2,\n",
              readFile());
}


} // end of anonymous namespace
