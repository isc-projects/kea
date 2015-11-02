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

#ifndef VERSIONED_CSV_FILE_H
#define VERSIONED_CSV_FILE_H

#include <util/csv_file.h>

namespace isc {
namespace util {

/// @brief Exception thrown when an error occurs during CSV file processing.
class VersionedCSVFileError : public Exception {
public:
    VersionedCSVFileError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Contains the metadata for a single column in a file.
class VersionedColumn {
public:
    /// @brief Constructor
    ///
    /// @param name Name of the column.
    /// @param version Text representation of the schema version in which
    /// this column first appeared.
    /// @param default_value The value the column should be assigned if it
    /// is not present in a data row. It defaults to an empty string, ""
    VersionedColumn(const std::string& name, const std::string& version,
               const std::string& default_value = "")
        : name_(name), version_(version), default_value_(default_value) {
    };

    /// @brief Destructor
    virtual ~VersionedColumn(){};

    /// @brief Name of the column.
    std::string name_;

    /// @brief Text representation of the schema version in which
    /// this column first appeared.
    std::string version_;

    /// @brief default_value The value the column should be assigned if it
    /// is not present in a data row.
    std::string default_value_;
};

/// @brief Defines a smart pointer to VersionedColumn
typedef boost::shared_ptr<VersionedColumn> VersionedColumnPtr;

/// @brief Implements a CSV file that supports multiple versions of
/// the file's "schema".  This allows files with older schemas to be
/// upgraded to newer schemas as they are being read.  The file's schema
/// is defined through a list of column descriptors, or @ref
/// isc::util::VersionedColumn(s). Each descriptor contains metadata describing
/// the column, consisting of the column's name, the version label in which
/// the column was added to the schema, and a default value to be used if the
/// column is missing from the file.  Note that the column descriptors are
/// defined in the order they occur in the file, when reading a row from left
/// to right.  This also assumes that when new version of the schema evolves,
/// all new columns are added at the end of the row.  In other words, the
/// order of the columns reflects not only the order in which they occur
/// in a row but also the order they were added to the schema.  Conceptually,
/// the entire list of columns defined constitutes the current schema.  Earlier
/// schema versions are therefore subsets of this list.   Creating the schema
/// is done by calling VersionedCSVfile::addColumn() for each column.  Note
/// that the schema must be defined prior to opening the file.
///
/// The first row of the file is always the header row and is a comma-separated
/// list of the names of the column in the file.  This row is used when
/// opening the file via @ref VersionedCSVFile::open(), to identify its schema
/// version so that it may be be read correctly.  This is done by comparing
/// the column found in the header to the columns defined in the schema. The
/// columns must match both by name and the order in which they occur.
///
/// 1. If there are fewer columns in the header than in the schema, the file
/// is presumed to be an earlier schema version and will be upgraded as it is
/// read.  There is an ability to mark a specific column as being the minimum
/// column which must be present, see @ref VersionedCSVFile::
/// setMinimumValidColumns().  If the header does contain match up to this
/// minimum column, the file is presumed to be too old to upgrade and the
/// open will fail.
///
/// 2. If there is a mismatch between a found column name and the column name
/// defined for that position in the row, the file is presumed to be invalid
/// and the open will fail.
///
/// After successfully opening a file,  rows are read one at a time via
/// @ref VersionedCSVFile::next().  Each data row is expected to have at least
/// the same number of columns as were found in the header. Any row which as
/// fewer values is discarded as invalid.  Similarly, any row which is found
/// to have more values than are defined in the schema is discarded as invalid
/// (@todo, consider removing this constraint as it would prohibit reading a
/// newer schema file with an older server).
///
/// When a row is found to have fewer than the defined number of columns,
/// the values for each missing column is filled in with the default value
/// specified by that column's descriptor.  In this manner rows from earlier
/// schemas are upgraded to the current schema.
///
/// It is important to note that upgrading a file does NOT alter the physical
/// file itself.  Rather the conversion occurs after the raw data has been read
/// but before it is passed to caller.
///
/// Also note that there is currently no support for writing out a file in
/// anything other than the current schema.
class VersionedCSVFile : public CSVFile {
public:

    /// @brief Constructor.
    ///
    /// @param filename CSV file name.
    VersionedCSVFile(const std::string& filename);

    /// @brief Destructor
    virtual ~VersionedCSVFile();

    /// @brief Adds metadata for a single column to the schema.
    ///
    /// This method appends a new column description to the file's schema.
    /// Note this does not cause anything to be written to the physical file.
    /// The name of the column will be placed in the CSV header when new file
    /// is created by calling @c recreate or @c open function.
    ///
    /// @param name Name of the column.
    /// @param version  Text representation of the schema version in which
    /// this column first appeared.
    /// @param default_value value the missing column should be given during
    /// an upgrade.  It defaults to an empty string, ""
    ///
    /// @throw CSVFileError if a column with the specified name exists.
    void addColumn(const std::string& col_name, const std::string& version,
                   const std::string& default_value = "");

    /// @brief Sets the minimum number of valid columns based on a given column
    ///
    /// @param column_name Name of the column which positionally represents
    /// the minimum columns which must be present in a file and to be
    /// considered valid.
    void setMinimumValidColumns(const std::string& column_name);

    /// @brief Returns the minimum number of columns which must be present
    /// for the file to be considered valid.
    size_t getMinimumValidColumns();

    /// @brief Opens existing file or creates a new one.
    ///
    /// This function will try to open existing file if this file has size
    /// greater than 0. If the file doesn't exist or has size of 0, the
    /// file is recreated. If the existing file has been opened, the header
    /// is parsed and and validated against the schema.
    /// By default, the data pointer in the file is set to the beginning of
    /// the first data row. In order to retrieve the row contents the @c next
    /// function should be called. If a @c seek_to_end parameter is set to
    /// true, the file will be opened and the internal pointer will be set
    /// to the end of file.
    ///
    /// @param seek_to_end A boolean value which indicates if the intput and
    /// output file pointer should be set at the end of file.
    ///
    /// @throw VersionedCSVFileError if schema has not been defined,
    /// CSVFileError when IO operation fails, or header fails to validate.
    virtual void open(const bool seek_to_end = false);

    /// @brief Reads next row from the file file.
    ///
    /// This function will return the @c CSVRow object representing a
    /// parsed row if parsing is successful. If the end of file has been
    /// reached, the empty row is returned (a row containing no values).
    ///
    /// 1. If the row has fewer values than were found in the header it is
    /// discarded as invalid.
    ///
    /// 2. If the row is found to have more values than are defined in the
    /// schema it is discarded as invalid
    ///
    /// When a valid row has fewer than the defined number of columns, the
    /// values for each missing column is filled in with the default value
    /// specified by that column's descriptor.
    ///
    /// @param [out] row Object receiving the parsed CSV file.
    /// @param skip_validation Do not perform validation.
    ///
    /// @return true if row has been read and validated; false if validation
    /// failed.
    bool next(CSVRow& row);

protected:

    /// @brief Validates the header of a VersionedCSVFile
    ///
    /// This function is called internally when the reading in an existing
    /// file.  It parses the header row of the file, comparing each value
    /// in succession against the defined list of columns.  If the header
    /// contains too few matching columns (i.e. less than @c
    /// minimum_valid_columns_) or too many (more than the number of defined
    /// columns), the file is presumed to be either too old, too new, or too
    /// corrupt to process.  Otherwise it retains the number of valid columns
    /// found and deems the header valid.
    ///
    /// @param header A row holding a header.
    /// @return true if header matches the columns; false otherwise.
    virtual bool validateHeader(const CSVRow& header);

private:
    /// @brief Holds the collection of column descriptors
    std::vector<VersionedColumnPtr> columns_;

    /// @brief Number of valid columns present in input file. If this is less
    /// than the number of columns defined, this implies the input file is
    /// from an earlier version of the code.
    size_t valid_column_count_;

    /// @brief Minimum number of valid columns an input file must contain.
    /// If an input file does not meet this number it cannot be upgraded.
    size_t minimum_valid_columns_;
};


} // namespace isc::util
} // namespace isc

#endif // VERSIONED_CSV_FILE_H
