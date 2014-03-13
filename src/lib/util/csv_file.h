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

#ifndef CSV_FILE_H
#define CSV_FILE_H

#include <exceptions/exceptions.h>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>

namespace isc {
namespace util {

/// @brief Exception thrown when an error occurs during CSV file processing.
class CSVFileError : public Exception {
public:
    CSVFileError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Represents a single row of the CSV file.
///
/// The object of this type can create the string holding a collection of the
/// comma separated values, representing a row of the CSV file. It allows to
/// select ANY character as a separator for the values. The default separator
/// is a comma sign.
///
/// The @c CSVRow object can be constructed in two different ways. The first
/// option is that the caller creates an object holding empty values
/// and then adds values one by one. Note that it is possible to either add
/// a string or a number. The number is stringified to the appropriate text
/// representation. When all the values are added, the text representation of
/// the row can be obtained by calling @c CSVRow::render function or output
/// stream operator.
///
/// The @c CSVRow object can be also constructed by parsing the row of the
/// CSV file. In this case, the separator has to be known in advance and
/// passed to the class constructor. Constructor will call the @c CSVRow::parse
/// function internally to tokenize the CSV row and create collection of the
/// values. The class accessors can be then used to retrieve individual
/// values.
///
/// This class is meant to be used by the @c CSVFile class to manipulate
/// the individual rows of the CSV file.
class CSVRow {
public:

    /// @brief Constructor, creates the raw to be used for output.
    ///
    /// Creates CSV row with empty values. The values should be
    /// later set using the @c CSVRow::writeAt functions. When the
    /// @c CSVRow::render is called, the text representation of the
    /// row will be created using a separator character specified
    /// as an argument of this constructor.
    ///
    /// This constructor is exception-free.
    ///
    /// @param cols Number of values in the row.
    /// @param separator Character being a separator between values in the
    /// text representation of the row.
    CSVRow(const size_t cols, const char separator = ',');

    /// @brief Constructor, parses a single row of the CSV file.
    ///
    /// This constructor should be used to parse a single row of the CSV
    /// file. The separator being used for the particular row needs to
    /// be known in advance and specified as an argument of the constructor
    /// if other than default separator is used in the row being parsed.
    /// An example string to be parsed by this function looks as follows:
    /// "foo,bar,foo-bar".
    ///
    /// This constructor is exception-free.
    ///
    /// @param text Text representation of the CSV row.
    /// @param separator Character being used as a separator in a parsed file.
    CSVRow(const std::string& text, const char separator = ',');

    /// @brief Returns number of values in a CSV row.
    size_t getValuesCount() const {
        return (values_.size());
    }

    /// @brief Parse the CSV file row.
    ///
    /// This function parses a string containing CSV values and assigns them
    /// to the @c values_ private container. These values can be retrieved
    /// from the container by calling @c CSVRow::readAt function.
    ///
    /// This function is exception-free.
    ///
    /// @param line String holding a row of comma separated values.
    void parse(const char* line);

    /// @brief Retrieves a value from the internal container.
    ///
    /// @param at Index of the value in the container. The values are indexed
    /// from 0, where 0 corresponds to the left-most value in the CSV file row.
    ///
    /// @return Value at specified index in the text form.
    ///
    /// @throw CSVFileError if the index is out of range. The number of elements
    /// being held by the container can be obtained using
    /// @c CSVRow::getValuesCount.
    std::string readAt(const size_t at) const;

    /// @brief Creates a text representation of the CSV file row.
    ///
    /// This function iterates over all values currently held in the internal
    /// @c values_ container and appends them into a string. The values are
    /// separated using a separator character specified in the constructor.
    ///
    /// This function is exception free.
    ///
    /// @return Text representation of the CSV file row.
    std::string render() const;

    /// @brief Replaces the value at specified index.
    ///
    /// This function is used to set values to be rendered using
    /// @c CSVRow::render function.
    ///
    /// @param at Index of the value to be replaced.
    /// @param value Value to be written given as string.
    ///
    /// @throw CSVFileError if index is out of range.
    void writeAt(const size_t at, const char* value);

    /// @brief Replaces the value at specified index.
    ///
    /// This function is used to set values to be rendered using
    /// @c CSVRow::render function.
    ///
    /// @param at Index of the value to be replaced.
    /// @param value Value to be written given as string.
    ///
    /// @throw CSVFileError if index is out of range.
    void writeAt(const size_t at, const std::string& value);

    /// @brief Replaces the value at specified index.
    ///
    /// This function is used to set values to be rendered using
    /// @c CSVRow::render function.
    ///
    /// @param at Index of the value to be replaced.
    /// @param value Value to be written - typically a number.
    /// @tparam T Type of the value being written.
    ///
    /// @throw CSVFileError if index is out of range.
    template<typename T>
    void writeAt(const size_t at, const T value) {
        checkIndex(at);
        try {
            values_[at] = boost::lexical_cast<std::string>(value);
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(CSVFileError, "unable to stringify the value to be"
                      " written in the CSV file row at position '"
                      << at << "'");
        }
    }

    /// @brief Equality operator.
    ///
    /// Two CSV rows are equal when their string representation is equal. This
    /// includes the order of fields, separator etc.
    ///
    /// @param other Object to compare to.
    bool operator==(const CSVRow& other) const;

    /// @brief Unequality operator.
    ///
    /// Two CSV rows are unequal when their string representation is unequal.
    /// This includes the order of fields, separator etc.
    ///
    /// @param other Object to compare to.
    bool operator!=(const CSVRow& other) const;

private:

    /// @brief Check if the specified index of the value is in range.
    ///
    /// This function is used interally by other functions.
    ///
    /// @param at Value index.
    /// @throw CSVFileError if specified index is not in range.
    void checkIndex(const size_t at) const;

    /// @brief Separator character specifed in the constructor.
    char separator_;

    /// @brief Internal container holding values that belong to the row.
    std::vector<std::string> values_;
};

/// @brief Overrides standard output stream operator for @c CSVRow object.
///
/// The resulting string of characters is the same as the one returned by
/// @c CSVRow::render function.
///
/// @param os Output stream.
/// @param row Object representing a CSV file row.
std::ostream& operator<<(std::ostream& os, const CSVRow& row);

/// @brief Provides input/output access to CSV files.
///
/// This class provides basic methods to access (parse) and create CSV files.
/// The file is identified by its name qualified with the absolute path.
/// The name of the file is passed to the constructor. Constructor doesn't
/// open/create a file, but simply records a file name specified by a caller.
///
/// There are two functions that can be used to open a file:
/// - @c open - opens an existing file; if the file doesn't exist it creates it,
/// - @c recreate - removes existing file and creates a new one.
///
/// When the file is opened its header file is parsed and column names are
/// idenetified. At this point it is already possible to get the list of the
/// column names using appropriate accessors. The data rows are not parsed
/// at this time. The row parsing is triggered by calling @c next function.
/// The result of parsing a row is stored in the @c CSVRow object passed as
/// a parameter.
///
/// When the new file is created (when @c recreate is called), the CSV header is
/// immediately written into it. The header consists of the column names
/// specified with the @c addColumn function. The subsequent rows are written
/// into this file by calling @c append.
class CSVFile {
public:

    /// @brief Constructor.
    ///
    /// @param filename CSV file name.
    CSVFile(const std::string& filename);

    /// @brief Destructor
    virtual ~CSVFile();

    /// @brief Adds new column name.
    ///
    /// This column adds a new column but doesn't write it to the file yet.
    /// The name of the column will be placed in the CSV header when new file
    /// is created by calling @c recreate or @c open function.
    ///
    /// @param col_name Name of the column.
    ///
    /// @throw CSVFileError if a column with the specified name exists.
    void addColumn(const std::string& col_name);

    /// @brief Writes the CSV row into the file.
    ///
    /// @param Object representing a CSV file row.
    ///
    /// @throw CSVFileError When error occured during IO operation or if the
    /// size of the row doesn't match the number of columns.
    void append(const CSVRow& row) const;

    /// @brief Closes the CSV file.
    void close();

    /// @brief Returns the number of columns in the file.
    size_t getColumnCount() const {
        return (cols_.size());
    }

    /// @brief Returns the index of the column having specified name.
    ///
    /// This function is exception safe.
    ///
    /// @param col_name Name of the column.
    /// @return Index of the column or negative value if the column doesn't
    /// exist.
    int getColumnIndex(const std::string& col_name) const;

    /// @brief Returns the name of the column.
    ///
    /// @param col_index Index of the column.
    ///
    /// @return Name of the column.
    /// @throw CSVFileError if the specified index is out of range.
    std::string getColumnName(const size_t col_index) const;

    /// @brief Reads next row from CSV file.
    ///
    /// This function will return the @c CSVRow object representing a
    /// parsed row if parsing is successful. If the end of file has been
    /// reached, the empty row is returned (a row containing no values).
    ///
    /// @param [out] row Object receiving the parsed CSV file.
    void next(CSVRow& row);

    /// @brief Opens existing file or creates a new one.
    ///
    /// This function will try to open existing file if this file has size
    /// greater than 0. If the file doesn't exist or has size of 0, the
    /// file is recreated. If the existing file has been opened, the header
    /// is parsed and column names are initialized in the @c CSVFile object.
    /// The data pointer in the file is set to the beginning of the first
    /// row. In order to retrieve the row contents the @c next function should
    /// be called.
    ///
    /// @throw CSVFileError when IO operation fails.
    void open();

    /// @brief Creates a new CSV file.
    ///
    /// The file creation will fail if there are no columns specified.
    /// Otherwise, this function will write the header to the file.
    /// In order to write rows to opened file, the @c append function
    /// should be called.
    void recreate();

    /// @brief Represents empty row.
    static CSVRow EMPTY_ROW() {
        static CSVRow row(0);
        return (row);
    }

private:

    /// @brief Returns size of the CSV file.
    std::ifstream::pos_type size() const;

    /// @brief Separator used by CSV file.
    char primary_separator_;

    /// @brief CSV file name.
    std::string filename_;

    /// @brief Holds a pointer to the file stream.
    boost::shared_ptr<std::fstream> fs_;

    /// @brief Holds CSV file columns.
    std::vector<std::string> cols_;
};

} // namespace isc::util
} // namespace isc

#endif // CSV_FILE_H
