// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

// Checks whether writeAt() and append() can be mixed together.
TEST(CSVRow, append) {
    CSVRow row(3);

    EXPECT_EQ(3, row.getValuesCount());

    row.writeAt(0, "alpha");
    ASSERT_NO_THROW(row.append("delta"));
    EXPECT_EQ(4, row.getValuesCount());
    row.writeAt(1, "beta");
    row.writeAt(2, "gamma");
    ASSERT_NO_THROW(row.append("epsilon"));
    EXPECT_EQ(5, row.getValuesCount());

    std::string text;
    ASSERT_NO_THROW(text = row.render());
    EXPECT_EQ("alpha,beta,gamma,delta,epsilon", text);
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
    int removeFile() const;

    /// @brief Creates file with contents.
    ///
    /// @param contents Contents of the file.
    void writeFile(const std::string& contents) const;

    /// @brief Absolute path to the file used in the tests.
    std::string testfile_;

};

CSVFileTest::CSVFileTest()
    : testfile_(absolutePath("test.csv")) {
    static_cast<void>(removeFile());
}

CSVFileTest::~CSVFileTest() {
    static_cast<void>(removeFile());
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

int
CSVFileTest::removeFile() const {
    return (remove(testfile_.c_str()));
}

void
CSVFileTest::writeFile(const std::string& contents) const {
    std::ofstream fs(testfile_.c_str(), std::ofstream::out);
    if (fs.is_open()) {
        fs << contents;
        fs.close();
    }
}

// This test checks that the function which is used to add columns of the
// CSV file works as expected.
TEST_F(CSVFileTest, addColumn) {
    boost::scoped_ptr<CSVFile> csv(new CSVFile(testfile_));
    // Add two columns.
    ASSERT_NO_THROW(csv->addColumn("animal"));
    ASSERT_NO_THROW(csv->addColumn("color"));
    // Make sure we can't add duplicates.
    EXPECT_THROW(csv->addColumn("animal"), CSVFileError);
    EXPECT_THROW(csv->addColumn("color"), CSVFileError);
    // But we should still be able to add unique columns.
    EXPECT_NO_THROW(csv->addColumn("age"));
    EXPECT_NO_THROW(csv->addColumn("comments"));
    // Assert that the file is opened, because the rest of the test relies
    // on this.
    ASSERT_NO_THROW(csv->recreate());
    ASSERT_TRUE(exists());

    // Make sure we can't add columns (even unique) when the file is open.
    ASSERT_THROW(csv->addColumn("zoo"), CSVFileError);
    // Close the file.
    ASSERT_NO_THROW(csv->close());
    // And check that now it is possible to add the column.
    EXPECT_NO_THROW(csv->addColumn("zoo"));
}

// This test checks that the appropriate file name is initialized.
TEST_F(CSVFileTest, getFilename) {
    CSVFile csv(testfile_);
    EXPECT_EQ(testfile_, csv.getFilename());
}

// This test checks that the file can be opened,  its whole content is
// parsed correctly and data may be appended. It also checks that empty
// row is returned when EOF is reached.
TEST_F(CSVFileTest, openReadAllWrite) {
    // Create a new CSV file that contains a header and two data rows.
    writeFile("animal,age,color\n"
              "cat,10,white\n"
              "lion,15,yellow\n");

    // Open this file and check that the header is parsed.
    boost::scoped_ptr<CSVFile> csv(new CSVFile(testfile_));
    ASSERT_NO_THROW(csv->open());
    ASSERT_EQ(3, csv->getColumnCount());
    EXPECT_EQ("animal", csv->getColumnName(0));
    EXPECT_EQ("age", csv->getColumnName(1));
    EXPECT_EQ("color", csv->getColumnName(2));

    // Read first row.
    CSVRow row;
    ASSERT_TRUE(csv->next(row));
    ASSERT_EQ(3, row.getValuesCount());
    EXPECT_EQ("cat", row.readAt(0));
    EXPECT_EQ("10", row.readAt(1));
    EXPECT_EQ("white", row.readAt(2));

    // Read second row.
    ASSERT_TRUE(csv->next(row));
    ASSERT_EQ(3, row.getValuesCount());
    EXPECT_EQ("lion", row.readAt(0));
    EXPECT_EQ("15", row.readAt(1));
    EXPECT_EQ("yellow", row.readAt(2));

    // There is no 3rd row, so the empty one should be returned.
    ASSERT_TRUE(csv->next(row));
    EXPECT_EQ(CSVFile::EMPTY_ROW(), row);

    // It should be fine to read again, but again empty row should be returned.
    ASSERT_TRUE(csv->next(row));
    EXPECT_EQ(CSVFile::EMPTY_ROW(), row);

    // Now, let's try to append something to this file.
    CSVRow row_write(3);
    row_write.writeAt(0, "dog");
    row_write.writeAt(1, 2);
    row_write.writeAt(2, "blue");
    ASSERT_NO_THROW(csv->append(row_write));

    // Close the file.
    ASSERT_NO_THROW(csv->flush());
    csv->close();

    // Check the the file contents are correct.
    EXPECT_EQ("animal,age,color\n"
              "cat,10,white\n"
              "lion,15,yellow\n"
              "dog,2,blue\n",
              readFile());

    // Any attempt to read from the file or write to it should now fail.
    EXPECT_FALSE(csv->next(row));
    EXPECT_THROW(csv->append(row_write), CSVFileError);

    CSVRow row_write2(3);
    row_write2.writeAt(0, "bird");
    row_write2.writeAt(1, 3);
    row_write2.writeAt(2, "purple");

    // Reopen the file, seek to the end of file so as we can append
    // some more data.
    ASSERT_NO_THROW(csv->open(true));
    // The file pointer should be at the end of file, so an attempt
    //  to read should result in an empty row.
    ASSERT_TRUE(csv->next(row));
    EXPECT_EQ(CSVFile::EMPTY_ROW(), row);
    // We should be able to append new data.
    ASSERT_NO_THROW(csv->append(row_write2));
    ASSERT_NO_THROW(csv->flush());
    csv->close();
    // Check that new data has been appended.
    EXPECT_EQ("animal,age,color\n"
              "cat,10,white\n"
              "lion,15,yellow\n"
              "dog,2,blue\n"
              "bird,3,purple\n",
              readFile());
}

// This test checks that contents may be appended to a file which hasn't
// been fully parsed/read.
TEST_F(CSVFileTest, openReadPartialWrite) {
    // Create a CSV file with two rows in it.
    writeFile("animal,age,color\n"
              "cat,10,white\n"
              "lion,15,yellow\n");

    // Open this file.
    boost::scoped_ptr<CSVFile> csv(new CSVFile(testfile_));
    ASSERT_NO_THROW(csv->open());

    // Read the first row.
    CSVRow row0(0);
    ASSERT_NO_THROW(csv->next(row0));
    ASSERT_EQ(3, row0.getValuesCount());
    EXPECT_EQ("cat", row0.readAt(0));
    EXPECT_EQ("10", row0.readAt(1));
    EXPECT_EQ("white", row0.readAt(2));

    // There is still second row to be read. But, it should be possible to
    // skip reading it and append new row to the end of file.
    CSVRow row_write(3);
    row_write.writeAt(0, "dog");
    row_write.writeAt(1, 2);
    row_write.writeAt(2, "blue");
    ASSERT_NO_THROW(csv->append(row_write));

    // At this point, the file pointer is at the end of file, so reading
    // should return empty row.
    CSVRow row1(0);
    ASSERT_NO_THROW(csv->next(row1));
    EXPECT_EQ(CSVFile::EMPTY_ROW(), row1);

    // Close the file.
    ASSERT_NO_THROW(csv->flush());
    csv->close();

    // Check that there are two initial lines and one new there.
    EXPECT_EQ("animal,age,color\n"
              "cat,10,white\n"
              "lion,15,yellow\n"
              "dog,2,blue\n",
              readFile());

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

    ASSERT_NO_THROW(csv->flush());
    csv->close();

    EXPECT_EQ("animal,color,age,comments\n"
              "dog,grey,3,nice one\n"
              "cat,black,2,\n",
              readFile());
}

// This test checks that the error is reported when the size of the row being
// read doesn't match the number of columns of the CSV file.
TEST_F(CSVFileTest, validate) {
    // Create CSV file with 2 invalid rows in it: one too long, one too short.
    // Apart from that, there are two valid columns that should be read
    // successfully.
    writeFile("animal,age,color\n"
              "cat,10,white\n"
              "lion,15,yellow,black\n"
              "dog,3,green\n"
              "elephant,11\n");

    boost::scoped_ptr<CSVFile> csv(new CSVFile(testfile_));
    ASSERT_NO_THROW(csv->open());
    // First row is correct.
    CSVRow row0;
    ASSERT_TRUE(csv->next(row0));
    EXPECT_EQ("cat", row0.readAt(0));
    EXPECT_EQ("10", row0.readAt(1));
    EXPECT_EQ("white", row0.readAt(2));
    EXPECT_EQ("success", csv->getReadMsg());
    // This row is too long.
    CSVRow row1;
    EXPECT_FALSE(csv->next(row1));
    EXPECT_NE("success", csv->getReadMsg());
    // This row is correct.
    CSVRow row2;
    ASSERT_TRUE(csv->next(row2));
    EXPECT_EQ("dog", row2.readAt(0));
    EXPECT_EQ("3", row2.readAt(1));
    EXPECT_EQ("green", row2.readAt(2));
    EXPECT_EQ("success", csv->getReadMsg());
    // This row is too short.
    CSVRow row3;
    EXPECT_FALSE(csv->next(row3));
    EXPECT_NE("success", csv->getReadMsg());
}

// Test test checks that exception is thrown when the header of the CSV file
// parsed, doesn't match the columns specified.
TEST_F(CSVFileTest, validateHeader) {
    // Create CSV file with 3 columns.
    writeFile("animal,age,color\n"
              "cat,10,white\n"
              "lion,15,yellow,black\n");

    // Invalid order of columns.
    boost::scoped_ptr<CSVFile> csv(new CSVFile(testfile_));
    csv->addColumn("color");
    csv->addColumn("animal");
    csv->addColumn("age");
    EXPECT_THROW(csv->open(), CSVFileError);

    // Too many columns.
    csv.reset(new CSVFile(testfile_));
    csv->addColumn("animal");
    csv->addColumn("age");
    csv->addColumn("color");
    csv->addColumn("notes");
    EXPECT_THROW(csv->open(), CSVFileError);

    // Too few columns.
    csv.reset(new CSVFile(testfile_));
    csv->addColumn("animal");
    csv->addColumn("age");
    EXPECT_THROW(csv->open(), CSVFileError);
}

// This test checks that the exists method of the CSVFile class properly
// checks that the file exists.
TEST_F(CSVFileTest, exists) {
    // Create a new CSV file that contains a header and two data rows.
    writeFile("animal,age,color\n"
              "cat,10,white\n"
              "lion,15,yellow\n");

    boost::scoped_ptr<CSVFile> csv(new CSVFile(testfile_));
    // The CSVFile class should return true even if the file hasn't been
    // opened.
    EXPECT_TRUE(csv->exists());
    // Now open the file and make sure it still returns true.
    ASSERT_NO_THROW(csv->open());
    EXPECT_TRUE(csv->exists());

    // Close the file and remove it.
    csv->close();
    EXPECT_EQ(0, removeFile());

    // The file should not exist.
    EXPECT_FALSE(csv->exists());
}


} // end of anonymous namespace
