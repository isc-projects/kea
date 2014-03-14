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

#include <util/csv_file.h>
#include <fstream>
#include <sstream>

namespace isc {
namespace util {

CSVRow::CSVRow(const size_t cols, const char separator)
    : separator_(separator), values_(cols) {
}

CSVRow::CSVRow(const std::string& text, const char separator)
    : separator_(separator) {
    // Parsing is exception safe, so this will not throw.
    parse(text.c_str());
}

void
CSVRow::parse(const char* line) {
    std::string s(line);
    // The 'pos' value holds the current position in the parsed stream.
    // Normally, it points to the position of one of the the separator
    // characters following the parsed value. For the first value, it
    // has to be set to -1.
    int pos = -1;
    // Position of the first character of the currently parsed value.
    size_t start_pos;
    // Flag which indicates whether parsing should end because last value
    // has been just parsed.
    bool leave = false;
    // Temporary container which holds parsed values. On successful
    // parsing completion, the contents of this container are moved
    // to the container holding values for the row.
    std::vector<std::string> values;

    do {
        // Set the position of the currently parsed value.
        start_pos = pos + 1;
        // Find the first separator, following the character at
        // start_pos.
        pos = s.find(separator_, start_pos);
        // The last value is not followed by a separator, so if
        // we reached the end of line, take reminder of the string
        // and make it a value.
        if (pos == std::string::npos) {
            pos = s.length();
            // Finish parsing as we already parsed the last value.
            leave = true;
        }
        // Store the parsed value.
        values.push_back(s.substr(start_pos, pos - start_pos));
    } while (!leave);

    // Assign new values.
    std::swap(values, values_);
}

std::string
CSVRow::readAt(const size_t at) const {
    checkIndex(at);
    return (values_[at]);
}

std::string
CSVRow::render() const {
    std::ostringstream s;
    for (int i = 0; i < values_.size(); ++i) {
        // Do not put separator before the first value.
        if (i > 0) {
            s << separator_;
        }
        s << values_[i];
    }
    return (s.str());
}

void
CSVRow::writeAt(const size_t at, const char* value) {
    checkIndex(at);
    values_[at] = value;
}

void
CSVRow::writeAt(const size_t at, const std::string& value) {
    writeAt(at, value.c_str());
}

bool
CSVRow::operator==(const CSVRow& other) const {
    return (render() == other.render());
}

bool
CSVRow::operator!=(const CSVRow& other) const {
    return (render() != other.render());
}

std::ostream& operator<<(std::ostream& os, const CSVRow& row) {
    os << row.render();
    return (os);
}

void
CSVRow::checkIndex(const size_t at) const {
    if (at >= values_.size()) {
        isc_throw(CSVFileError, "value index '" << at << "' of the CSV row"
                  " is out of bounds; maximal index is '"
                  << (values_.size() - 1) << "'");
    }
}

CSVFile::CSVFile(const std::string& filename)
    : primary_separator_(','), filename_(filename), fs_(), cols_(0),
      read_msg_() {
}

CSVFile::~CSVFile() {
    close();
}

void
CSVFile::close() {
    // It is allowed to close multiple times. If file has been already closed,
    // this is no-op.
    if (fs_) {
        fs_->close();
        fs_.reset();
    }
}

void
CSVFile::flush() const {
    checkStreamStatus("flush");
    fs_->flush();
}

void
CSVFile::addColumn(const std::string& col_name) {
    if (getColumnIndex(col_name) >= 0) {
        isc_throw(CSVFileError, "attempt to add duplicate column '"
                  << col_name << "'");
    }
    cols_.push_back(col_name);
}

void
CSVFile::append(const CSVRow& row) const {
    checkStreamStatus("append");

    // If a stream is in invalid state, reset the state.
    fs_->clear();

    if (row.getValuesCount() != getColumnCount()) {
        isc_throw(CSVFileError, "number of values in the CSV row '"
                  << row.getValuesCount() << "' doesn't match the number of"
                  " columns in the CSV file '" << getColumnCount() << "'");
    }

    fs_->seekp(0, std::ios_base::end);
    fs_->seekg(0, std::ios_base::end);
    fs_->clear();

    std::string text = row.render();
    *fs_ << text << std::endl;
    if (!fs_->good()) {
        fs_->clear();
        isc_throw(CSVFileError, "failed to write CSV row '"
                  << text << "' to the file '" << filename_ << "'");
    }
}

void
CSVFile::checkStreamStatus(const std::string& operation) const {
    if (!fs_) {
        isc_throw(CSVFileError, "NULL stream pointer when performing '"
                  << operation << "' on file '" << filename_ << "'");

    } else if (!fs_->is_open()) {
        isc_throw(CSVFileError, "closed stream when performing '"
                  << operation << "' on file '" << filename_ << "'");

    }
}

std::ifstream::pos_type
CSVFile::size() const {
    std::ifstream fs(filename_.c_str());
    bool ok = fs.good();
    // If something goes wrong, including that the file doesn't exist,
    // return 0.
    if (!ok) {
        fs.close();
        return (0);
    }
    std::ifstream::pos_type pos;
    try {
        // Seek to the end of file and see where we are. This is a size of
        // the file.
        fs.seekg(0, std::ifstream::end);
        pos = fs.tellg();
        fs.close();
    } catch (const std::exception& ex) {
        return (0);
    }
    return (pos);
}

int
CSVFile::getColumnIndex(const std::string& col_name) const {
    for (int i = 0; i < cols_.size(); ++i) {
        if (cols_[i] == col_name) {
            return (i);
        }
    }
    return (-1);
}

std::string
CSVFile::getColumnName(const size_t col_index) const {
    if (col_index > cols_.size()) {
        isc_throw(isc::OutOfRange, "column index " << col_index << " in the "
                  " CSV file '" << filename_ << "' is out of range; the CSV"
                  " file has only  " << cols_.size() << " columns ");
    }
    return (cols_[col_index]);
}

bool
CSVFile::next(CSVRow& row, const bool skip_validation) {
    // Set somethings as row validation error. Although, we haven't started
    // actual row validation we should get rid of any previously recorded
    // errors so as the caller doesn't interpret them as the current one.
    setReadMsg("validation not started");

    try {
        // Check that stream is "ready" for any IO operations.
        checkStreamStatus("get next row");

    } catch (isc::Exception& ex) {
        setReadMsg(ex.what());
        return (false);
    }

    // If a stream is in invalid state, reset the state.
    fs_->clear();

    // Get exactly one line of the file.
    std::string line;
    std::getline(*fs_, line);
    // If we got empty line because we reached the end of file
    // return an empty row.
    if (line.empty() && fs_->eof()) {
        row = EMPTY_ROW();
        return (true);

    } else if (!fs_->good()) {
        // If we hit an IO error, communicate it to the caller but do NOT close
        // the stream. Caller may try again.
        setReadMsg("error reading a row from CSV file '"
                   + std::string(filename_) + "'");
        return (false);
    }
    // If we read anything, parse it.
    row.parse(line.c_str());

    // And check if it is correct.
    return (skip_validation ? true : validate(row));
}

void
CSVFile::open() {
    // If file doesn't exist or is empty, we have to create our own file.
    if (size() == 0) {
        recreate();

    } else {
        // Try to open existing file, holding some data.
        fs_.reset(new std::fstream(filename_.c_str()));
        // The file may fail to open. For example, because of insufficient
        // persmissions. Although the file is not open we should call close
        // to reset our internal pointer.
        if (!fs_->is_open()) {
            close();
            isc_throw(CSVFileError, "unable to open '" << filename_ << "'");
        }
        // Make sure we are on the beginning of the file, so as we can parse
        // the header.
        fs_->seekg(0);
        if (!fs_->good()) {
            close();
            isc_throw(CSVFileError, "unable to set read pointer in the file '"
                      << filename_ << "'");
        }

        // Read the header.
        CSVRow header;
        if (!next(header, true)) {
            close();
            isc_throw(CSVFileError, "failed to read and parse header of the"
                      " CSV file '" << filename_ << "': "
                      << getReadMsg());
        }

        // Check the header against the columns specified for the CSV file.
        if (!validateHeader(header)) {
            close();
            isc_throw(CSVFileError, "invalid header '" << header
                      << "' in CSV file '" << filename_ << "'");
        }

        // Everything is good, so if we haven't added any columns yet,
        // add them.
        if (getColumnCount() == 0) {
            for (size_t i = 0; i < header.getValuesCount(); ++i) {
                addColumn(header.readAt(i));
            }
        }
    }
}

void
CSVFile::recreate() {
    // There is no sense to create a file is we don't specify columns for it.
    if (getColumnCount() == 0) {
        close();
        isc_throw(CSVFileError, "no columns defined for the newly"
                  " created CSV file '" << filename_ << "'");
    }

    // Close any danglining files.
    close();
    fs_.reset(new std::fstream(filename_.c_str(), std::fstream::out));
    if (!fs_->is_open()) {
        close();
        isc_throw(CSVFileError, "unable to open '" << filename_ << "'");
    }
    // Opened successfuly. Write a header to it.
    try {
        CSVRow header(getColumnCount());
        for (int i = 0; i < getColumnCount(); ++i) {
            header.writeAt(i, getColumnName(i));
        }
        *fs_ << header << std::endl;

    } catch (const std::exception& ex) {
        close();
        isc_throw(CSVFileError, ex.what());
    }

}

bool
CSVFile::validate(const CSVRow& row) {
    setReadMsg("success");
    bool ok = (row.getValuesCount() == getColumnCount());
    if (!ok) {
        std::ostringstream s;
        s << "the size of the row '" << row << "' doesn't match the number of"
            " columns '" << getColumnCount() << "' of the CSV file '"
          << filename_ << "'";
        setReadMsg(s.str());
    }
    return (ok);
}

bool
CSVFile::validateHeader(const CSVRow& header) {
    if (getColumnCount() == 0) {
        return (true);
    }

    if (getColumnCount() != header.getValuesCount()) {
        return (false);
    }

    for (int i = 0; i < getColumnCount(); ++i) {
        if (getColumnName(i) != header.readAt(i)) {
            return (false);
        }
    }
    return (true);
}

} // end of isc::util namespace
} // end of isc namespace
