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
      minimum_valid_columns_(0), input_header_count_(0),
      input_schema_state_(CURRENT) {
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
VersionedCSVFile::getMinimumValidColumns() const {
    return (minimum_valid_columns_);
}

size_t
VersionedCSVFile::getValidColumnCount() const {
    return (valid_column_count_);
}

size_t
VersionedCSVFile::getInputHeaderCount() const {
    return (input_header_count_);
}

void
VersionedCSVFile::open(const bool seek_to_end) {
    if (getColumnCount() == 0) {
        isc_throw(VersionedCSVFileError,
                  "no schema has been defined, cannot open CSV file :"
                  << getFilename());
    }

    CSVFile::open(seek_to_end);
}

void
VersionedCSVFile::recreate() {
    if (getColumnCount() == 0) {
        isc_throw(VersionedCSVFileError,
                  "no schema has been defined, cannot create CSV file :"
                  << getFilename());
    }

    CSVFile::recreate();
    // For new files they always match.
    input_header_count_ = valid_column_count_ = getColumnCount();
}

VersionedCSVFile::InputSchemaState
VersionedCSVFile::getInputSchemaState() const {
    return (input_schema_state_);
}

bool
VersionedCSVFile::needsConversion() const {
    return (input_schema_state_ != CURRENT);
}

std::string
VersionedCSVFile::getInputSchemaVersion() const {
    if (getValidColumnCount() > 0) {
        return (getVersionedColumn(getValidColumnCount() - 1)->version_);
    }

    return ("undefined");
}

std::string
VersionedCSVFile::getSchemaVersion() const {
    if (getColumnCount() > 0) {
        return (getVersionedColumn(getColumnCount() - 1)->version_);
    }

    return ("undefined");
}

const VersionedColumnPtr&
VersionedCSVFile::getVersionedColumn(const size_t index) const {
    if (index >= getColumnCount()) {
        isc_throw(isc::OutOfRange, "versioned column index " << index
                  << " out of range;  CSV file : " << getFilename()
                  << " only has " << getColumnCount() << " columns ");
    }

    return (columns_[index]);
}

bool
VersionedCSVFile::next(CSVRow& row) {
    setReadMsg("success");
    // Use base class to physical read the row, but skip its row
    // validation
    CSVFile::next(row, true);
    if (row == CSVFile::EMPTY_ROW()) {
        return(true);
    }

    bool row_valid = true;
    switch(getInputSchemaState()) {
        case CURRENT:
            // All rows must match than the current schema
            if (row.getValuesCount() != getColumnCount()) {
                columnCountError(row, "must match current schema");
                row_valid = false;
            }
            break;

        case NEEDS_UPGRADE:
            // The input header met the minimum column count but
            // is less than the current schema so:
            // Rows must not be shorter than the valid column count
            // and not longer than the current schema
            if (row.getValuesCount() < getValidColumnCount()) {
                columnCountError(row, "too few columns to upgrade");
                row_valid = false;
            } else if (row.getValuesCount() > getColumnCount()) {
                columnCountError(row, "too many columns to upgrade");
                row_valid = false;
            } else {
                // Add any missing values
                for (size_t index = row.getValuesCount();
                     index < getColumnCount(); ++index) {
                    row.append(columns_[index]->default_value_);
                }
            }
            break;

        case NEEDS_DOWNGRADE:
            // The input header exceeded current schema so:
            // Rows may be as long as input header but not shorter than
            // the the current schema
            if (row.getValuesCount() < getColumnCount()) {
                columnCountError(row, "too few columns to downgrade");
            } else if (row.getValuesCount() > getInputHeaderCount()) {
                columnCountError(row, "too many columns to downgrade");
            } else {
                // Toss any the extra columns
                row.trim(row.getValuesCount() - getColumnCount());
            }
            break;
    }

    return (row_valid);
}

void
VersionedCSVFile::columnCountError(const CSVRow& row,
                                  const std::string& reason) {
    std::ostringstream s;
    s <<  "Invalid number of columns: "
      << row.getValuesCount()  << " in row: '" << row
      << "', file: '" << getFilename() << "' : " << reason;
      setReadMsg(s.str());
}

bool
VersionedCSVFile::validateHeader(const CSVRow& header) {
    if (getColumnCount() == 0) {
        isc_throw(VersionedCSVFileError,
                  "cannot validate header, no schema has been defined");
    }

    input_header_count_ = header.getValuesCount();

    // Iterate over the number of columns in the header, testing
    // each against the defined column in the same position.
    // If there is a mismatch, bail.
    size_t i = 0;
    for (  ; i < getInputHeaderCount() && i < getColumnCount(); ++i) {
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
    if (i < getMinimumValidColumns()) {
        std::ostringstream s;
        s << " - header has only " << i << " valid column(s), "
          << "it must have at least " << getMinimumValidColumns();
        setReadMsg(s.str());
        return (false);
    }

    // Remember the number of valid columns we found.  When this number
    // is less than the number of defined columns, then we have an older
    // version of the lease file.  We'll need this value to validate
    // and upgrade data rows.
    valid_column_count_ = i;

    if (getValidColumnCount() < getColumnCount()) {
        input_schema_state_ = NEEDS_UPGRADE;
    } else if (getInputHeaderCount() > getColumnCount()) {
        // If there are more values in the header than defined columns
        // then, we'll drop the extra.  This allows someone to attempt to
        // downgrade if need be.
        input_schema_state_ = NEEDS_DOWNGRADE;
        std::ostringstream s;
        s << " - header has " << getInputHeaderCount() - getColumnCount()
          << " extra column(s), these will be ignored";
        setReadMsg(s.str());
    }

    return (true);
}

} // end of isc::util namespace
} // end of isc namespace
