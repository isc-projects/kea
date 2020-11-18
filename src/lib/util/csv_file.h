// Copyright (C) 2014-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
/// comma separated values, representing a row of the CSV file. It allows the
/// selection of any character as a separator for the values. The default
/// separator is the comma symbol.
///
/// The @c CSVRow object can be constructed in two different ways. The first
/// option is that the caller creates an object holding empty values
/// and then adds values one by one. Note that it is possible to either add
/// a string or a number. The number is converted to the appropriate text
/// representation. When all the values are added, the text representation of
/// the row can be obtained by calling @c CSVRow::render function or output
/// stream operator.
///
/// The @c CSVRow object can be also constructed by parsing a row of a CSV
/// file. In this case, the separator has to be known in advance and passed to
/// the class constructor. The constructor will call the @c CSVRow::parse
/// function internally to tokenize the CSV row and create the collection of
/// values. The class accessors can be then used to retrieve individual values.
///
/// This class is meant to be used by the @c CSVFile class to manipulate
/// individual rows of the CSV file.
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
    /// @param separator Character used as a separator between values in the
    /// text representation of the row.
    CSVRow(const size_t cols = 0, const char separator = ',');

    /// @brief Constructor, parses a single row of the CSV file.
    ///
    /// This constructor should be used to parse a single row of the CSV
    /// file. The separator being used for the particular row needs to
    /// be known in advance and specified as an argument of the constructor
    /// if other than the default separator is used in the row being parsed.
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
    void parse(const std::string& line);

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

    /// @brief Retrieves a value from the internal container, free of escaped
    /// characters.
    ///
    /// Returns a copy of the internal container value at the given index
    /// which has had all escaped characters replaced with their unescaped
    /// values. Escaped characters embedded using the following format:
    ///
    /// This function fetches the value at the given index and passes it
    /// into CSVRow::unescapeCharacters which replaces any escaped special
    /// characters with their unescaped form.
    ///
    /// @param at Index of the value in the container. The values are indexed
    /// from 0, where 0 corresponds to the left-most value in the CSV file row.
    ///
    /// @return Value at specified index in the text form.
    ///
    /// @throw CSVFileError if the index is out of range. The number of elements
    /// being held by the container can be obtained using
    /// @c CSVRow::getValuesCount.
    std::string readAtEscaped(const size_t at) const;

    /// @brief Trims a given number of elements from the end of a row
    ///
    /// @param count number of elements to trim
    ///
    /// @throw CSVFileError if the number to trim is larger than
    /// then the number of elements
    void trim(const size_t count);

    /// @brief Retrieves a value from the internal container.
    ///
    /// This method is reads a value from the internal container and converts
    /// this value to the type specified as a template parameter. Internally
    /// it uses @c boost::lexical_cast.
    ///
    /// @param at Index of the value in the container. The values are indexed
    /// from 0, where 0 corresponds to the left-most value in the CSV file row.
    /// @tparam T type of the value to convert to.
    ///
    /// @return Converted value.
    ///
    /// @throw CSVFileError if the index is out of range or if the
    /// @c boost::bad_lexical_cast is thrown by the @c boost::lexical_cast.
    template<typename T>
    T readAndConvertAt(const size_t at) const {
        T cast_value;
        try {
            cast_value = boost::lexical_cast<T>(readAt(at).c_str());

        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(CSVFileError, ex.what());
        }
        return (cast_value);
    }

    /// @brief Creates a text representation of the CSV file row.
    ///
    /// This function iterates over all values currently held in the internal
    /// @c values_ container and appends them to a string. The values are
    /// separated using the separator character specified in the constructor.
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
    void writeAt(const size_t at, const std::string& value) {
        writeAt(at, value.c_str());
    }

    /// @brief Replaces the value at the specified index with a value that has
    /// had special characters escaped
    ///
    /// This function first calls @c CSVRow::escapeCharacters to replace
    /// special characters with their escaped form.  It then sets the value
    /// to be rendered using @c CSVRow::render function.
    ///
    /// @param at Index of the value to be replaced.
    /// @param value Value to be written given as string.
    ///
    /// @throw CSVFileError if index is out of range.
    void writeAtEscaped(const size_t at, const std::string& value);

    /// @brief Appends the value as a new column.
    ///
    /// @param value Value to be written.
    /// @tparam T Type of the value being written.
    template<typename T>
    void append(const T value) {
        try {
            values_.push_back(boost::lexical_cast<std::string>(value));
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(CSVFileError, "unable to stringify the value to be "
                      "appended to the CSV file row.");
        }
    }

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
    bool operator==(const CSVRow& other) const {
        return (render() == other.render());
    }

    /// @brief Unequality operator.
    ///
    /// Two CSV rows are unequal when their string representation is unequal.
    /// This includes the order of fields, separator etc.
    ///
    /// @param other Object to compare to.
    bool operator!=(const CSVRow& other) const {
        return (render() != other.render());
    }

    /// @brief Returns a copy of a string with special characters escaped
    ///
    /// @param orig_str string which may contain characters that require
    /// escaping.
    /// @param characters list of characters which require escaping.
    ///
    /// The escaped characters will use the following format:
    ///
    /// @verbatim
    /// &#x{xx}
    /// @endverbatim
    ///
    /// where {xx} is the two digit hexadecimal ASCII value of the character
    /// escaped. A comma, for example is:
    ///
    /// &\#x2c
    ///
    /// @return A copy of the original string with special characters escaped.
    static std::string escapeCharacters(const std::string& orig_str,
                                        const std::string& characters);

    /// @brief Returns a copy of a string with special characters unescaped
    ///
    /// This function reverses the escaping of characters done by @c
    /// CSVRow::escapeCharacters.
    ///
    /// @param escaped_str string which may contain escaped characters.
    ///
    /// @return A string free of escaped characters
    static std::string unescapeCharacters(const std::string& escaped_str);

private:

    /// @brief Check if the specified index of the value is in range.
    ///
    /// This function is used internally by other functions.
    ///
    /// @param at Value index.
    /// @throw CSVFileError if specified index is not in range.
    void checkIndex(const size_t at) const;

    /// @brief Separator character specified in the constructor.
    ///
    /// @note Separator is held as a string object (one character long),
    /// because the boost::is_any_of algorithm requires a string, not a
    /// char value. If we held the separator as a char, we would need to
    /// convert it to string on every call to @c CSVRow::parse.
    std::string separator_;

    /// @brief Internal container holding values that belong to the row.
    std::vector<std::string> values_;

    /// @brief Prefix used to escape special characters.
    static const std::string escape_tag;
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
/// identified. At this point it is already possible to get the list of the
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
    /// @param row Object representing a CSV file row.
    ///
    /// @throw CSVFileError When error occurred during IO operation or if the
    /// size of the row doesn't match the number of columns.
    void append(const CSVRow& row) const;

    /// @brief Closes the CSV file.
    void close();

    /// @brief Checks if the CSV file exists and can be opened for reading.
    ///
    /// This method doesn't check if the existing file has a correct file
    /// format.
    ///
    /// @return true if file exists, false otherwise.
    bool exists() const;

    /// @brief Flushes a file.
    void flush() const;

    /// @brief Returns the number of columns in the file.
    size_t getColumnCount() const {
        return (cols_.size());
    }

    /// @brief Returns the path to the CSV file.
    std::string getFilename() const {
        return (filename_);
    }

    /// @brief Returns the description of the last error returned by the
    /// @c CSVFile::next function.
    ///
    /// @return Description of the last error during row validation.
    std::string getReadMsg() const {
        return (read_msg_);
    }

    /// @brief Returns the index of the column having specified name.
    ///
    /// This function is exception safe.
    ///
    /// @param col_name Name of the column.
    /// @return Index of the column.
    /// @throw OutOfRange if column with such name doesn't exist.
    size_t getColumnIndex(const std::string& col_name) const;

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
    /// @param skip_validation Do not perform validation.
    ///
    /// @return true if row has been read and validated; false if validation
    /// failed.
    bool next(CSVRow& row, const bool skip_validation = false);

    /// @brief Opens existing file or creates a new one.
    ///
    /// This function will try to open existing file if this file has size
    /// greater than 0. If the file doesn't exist or has size of 0, the
    /// file is recreated. If the existing file has been opened, the header
    /// is parsed and column names are initialized in the @c CSVFile object.
    /// By default, the data pointer in the file is set to the beginning of
    /// the first row. In order to retrieve the row contents the @c next
    /// function should be called. If a @c seek_to_end parameter is set to
    /// true, the file will be opened and the internal pointer will be set
    /// to the end of file.
    ///
    /// @param seek_to_end A boolean value which indicates if the input and
    /// output file pointer should be set at the end of file.
    ///
    /// @throw CSVFileError when IO operation fails.

    virtual void open(const bool seek_to_end = false);

    /// @brief Creates a new CSV file.
    ///
    /// The file creation will fail if there are no columns specified.
    /// Otherwise, this function will write the header to the file.
    /// In order to write rows to opened file, the @c append function
    /// should be called.
    virtual void recreate();

    /// @brief Sets error message after row validation.
    ///
    /// The @c CSVFile::validate function is responsible for setting the
    /// error message after validation of the row read from the CSV file.
    /// It will use this function to set this message. Note, that the
    /// @c validate function can set a message after successful validation
    /// too. Such message could say "success", or something similar.
    ///
    /// @param read_msg Error message to be set.
    void setReadMsg(const std::string& read_msg) {
        read_msg_ = read_msg;
    }

    /// @brief Represents empty row.
    static CSVRow EMPTY_ROW() {
        static CSVRow row(0);
        return (row);
    }

protected:

    /// @brief Adds a column regardless if the file is open or not.
    ///
    /// This function adds as new column to the collection. It is meant to be
    /// called internally by the methods of the base class and derived classes.
    /// It must not be used in the public scope. The @c CSVFile::addColumn
    /// must be used in the public scope instead, because it prevents addition
    /// of the new column when the file is open.
    ///
    /// @param col_name Name of the column.
    ///
    /// @throw CSVFileError if a column with the specified name exists.
    void addColumnInternal(const std::string& col_name);

    /// @brief Validate the row read from a file.
    ///
    /// This function implements a basic validation for the row read from the
    /// CSV file. It is virtual so as it may be customized in derived classes.
    ///
    /// This default implementation checks that the number of values in the
    /// row corresponds to the number of columns specified for this file.
    ///
    /// If row validation fails, the error message is noted and can be retrieved
    /// using @c CSVFile::getReadMsg. The function which overrides this
    /// base implementation is responsible for setting the error message using
    /// @c CSVFile::setReadMsg.
    ///
    /// @param row A row to be validated.
    ///
    /// @return true if the column is valid; false otherwise.
    virtual bool validate(const CSVRow& row);

protected:

    /// @brief This function validates the header of the CSV file.
    ///
    /// If there are any columns added to the @c CSVFile object, it will
    /// compare that they exactly match (including order) the header read
    /// from the file.
    ///
    /// This function is called internally by @ref CSVFile::open. Derived classes
    /// may add extra validation steps.
    ///
    /// @param header A row holding a header.
    /// @return true if header matches the columns; false otherwise.
    virtual bool validateHeader(const CSVRow& header);

private:
    /// @brief Sanity check if stream is open.
    ///
    /// Checks if the file stream is open so as IO operations can be performed
    /// on it. This is internally called by the public class members to prevent
    /// them from performing IO operations on invalid stream and using NULL
    /// pointer to a stream. The @c clear() method is called on the stream
    /// after the status has been checked.
    ///
    /// @throw CSVFileError if stream is closed or pointer to it is NULL.
    void checkStreamStatusAndReset(const std::string& operation) const;

    /// @brief Returns size of the CSV file.
    std::streampos size() const;

    /// @brief CSV file name.
    std::string filename_;

    /// @brief Holds a pointer to the file stream.
    boost::shared_ptr<std::fstream> fs_;

    /// @brief Holds CSV file columns.
    std::vector<std::string> cols_;

    /// @brief Holds last error during row reading or validation.
    std::string read_msg_;
};

} // namespace isc::util
} // namespace isc

#endif // CSV_FILE_H
