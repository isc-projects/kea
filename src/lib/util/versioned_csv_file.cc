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

#include <util/versioned_csv_file.h>

namespace isc {
namespace util {

VersionedCSVFile::VersionedCSVFile(const std::string& filename)
    : CSVFile(filename), columns_(0), valid_column_count_(0),
      minimum_valid_columns_(0) {
}

VersionedCSVFile::~VersionedCSVFile() {
}

void
VersionedCSVFile::addColumn(const std::string& name,
                            const std::string& version,
                            const std::string& default_value) {
    CSVFile::addColumn(name);
    columns_.push_back(VersionedColumnPtr(new VersionedColumn(name, version,
                                                              default_value)));
}

void
VersionedCSVFile::setMinimumValidColumns(const std::string& column_name) {
    int index = getColumnIndex(column_name);
    if (index <  0) {
        isc_throw(VersionedCSVFileError,
                  "setMinimumValidColumns: " << column_name << " is defined");
    }

    minimum_valid_columns_ = index + 1;
}

size_t
VersionedCSVFile::getMinimumValidColumns() {
    return (minimum_valid_columns_);
}

void
VersionedCSVFile::open(const bool seek_to_end) {
    if (getColumnCount() == 0) {
        isc_throw(VersionedCSVFileError,
                  "no schema has been defined, cannot open file :"
                  << getFilename());
    }

    CSVFile::open(seek_to_end);
}

bool
VersionedCSVFile::next(CSVRow& row) {
    CSVFile::next(row, true);
    if (row == CSVFile::EMPTY_ROW()) {
        return(true);
    }

    // If we're upgrading, valid_column_count_ will be less than
    // defined column count.  If not they're the equal.  Either way
    // each data row must have valid_column_count_ values or its
    // an invalid row.
    if (row.getValuesCount() < valid_column_count_) {
        std::ostringstream s;
        s << "the size of the row '" << row << "' has too few valid columns "
          << valid_column_count_ << "' of the CSV file '"
          << getFilename() << "'";
        setReadMsg(s.str());
        return (false);
    }

    // If we're upgrading, we need to add in any missing values
    for (size_t index = row.getValuesCount(); index < getColumnCount();
         ++index) {
        row.append(columns_[index]->default_value_);
    }

    return (CSVFile::validate(row));
}

bool
VersionedCSVFile::validateHeader(const CSVRow& header) {
    // @todo does this ever make sense? What would be the point of a versioned
    // file that has no defined columns?
    if (getColumnCount() == 0) {
        return (true);
    }

    // If there are more values in the header than defined columns
    // then the lease file must be from a newer version, so bail out.
    // @todo - we may wish to remove this constraint as it prohibits one
    // from usig a newer schema file with older schema code.
    if (header.getValuesCount() > getColumnCount()) {
        std::ostringstream s;
        s << " - header has " << header.getValuesCount()  << " column(s), "
          << "it should not have more than " << getColumnCount();

        setReadMsg(s.str());
        return (false);
    }

    // Iterate over the number of columns in the header, testing
    // each against the defined column in the same position.
    // If there is a mismatch, bail.
    size_t i = 0;
    for (  ; i < header.getValuesCount(); ++i) {
        if (getColumnName(i) != header.readAt(i)) {
            std::ostringstream s;
            s << " - header contains an invalid column: '"
              << header.readAt(i) << "'";
            setReadMsg(s.str());
            return (false);
        }
    }

    // If we found too few valid columns, then we cannot convert this
    // file.  It's too old, too corrupt, or not a Kea file.
    if (i < minimum_valid_columns_) {
        std::ostringstream s;
        s << " - header has only " << i << " valid column(s), "
          << "it must have at least " << minimum_valid_columns_;
        setReadMsg(s.str());
        return (false);
    }

    // Remember the number of valid columns we found.  When this number
    // is less than the number of defined columns, then we have an older
    // version of the lease file.  We'll need this value to validate
    // and upgrade data rows.
    valid_column_count_ = i;

    return (true);
}

} // end of isc::util namespace
} // end of isc namespace
