// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <util/csv_file.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fstream>
#include <sstream>

namespace isc {
namespace util {

CSVRow::CSVRow(const size_t cols, const char separator)
    : separator_(1, separator), values_(cols) {
}

CSVRow::CSVRow(const std::string& text, const char separator)
    : separator_(1, separator) {
    // Parsing is exception safe, so this will not throw.
    parse(text);
}

void
CSVRow::parse(const std::string& line) {
    // Tokenize the string using a specified separator. Disable compression,
    // so as the two consecutive separators mark an empty value.
    boost::split(values_, line, boost::is_any_of(separator_),
                 boost::algorithm::token_compress_off);
}

std::string
CSVRow::readAt(const size_t at) const {
    checkIndex(at);
    return (values_[at]);
}

std::string
CSVRow::render() const {
    std::ostringstream s;
    for (size_t i = 0; i < values_.size(); ++i) {
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
CSVRow::trim(const size_t count) {
    checkIndex(count);
    values_.resize(values_.size() - count);
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
    : filename_(filename), fs_(), cols_(0), read_msg_() {
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

bool
CSVFile::exists() const {
    std::ifstream fs(filename_.c_str());
    const bool file_exists = fs.good();
    fs.close();
    return (file_exists);
}

void
CSVFile::flush() const {
    checkStreamStatusAndReset("flush");
    fs_->flush();
}

void
CSVFile::addColumn(const std::string& col_name) {
    // It is not allowed to add a new column when file is open.
    if (fs_) {
        isc_throw(CSVFileError, "attempt to add a column '" << col_name
                  << "' while the file '" << getFilename()
                  << "' is open");
    }
    addColumnInternal(col_name);
}

void
CSVFile::addColumnInternal(const std::string& col_name) {
    if (getColumnIndex(col_name) >= 0) {
        isc_throw(CSVFileError, "attempt to add duplicate column '"
                  << col_name << "'");
    }
    cols_.push_back(col_name);
}

void
CSVFile::append(const CSVRow& row) const {
    checkStreamStatusAndReset("append");

    if (row.getValuesCount() != getColumnCount()) {
        isc_throw(CSVFileError, "number of values in the CSV row '"
                  << row.getValuesCount() << "' doesn't match the number of"
                  " columns in the CSV file '" << getColumnCount() << "'");
    }

    /// @todo Apparently, seekp and seekg are interchangeable. A call to seekp
    /// results in moving the input pointer too. This is ok for now. It means
    /// that when the append() is called, the read pointer is moved to the EOF.
    /// For the current use cases we only read a file and then append a new
    /// content. If we come up with the scenarios when read and write is
    /// needed at the same time, we may revisit this: perhaps remember the
    /// old pointer. Also, for safety, we call both functions so as we are
    /// sure that both pointers are moved.
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
CSVFile::checkStreamStatusAndReset(const std::string& operation) const {
    if (!fs_) {
        isc_throw(CSVFileError, "NULL stream pointer when performing '"
                  << operation << "' on file '" << filename_ << "'");

    } else if (!fs_->is_open()) {
        fs_->clear();
        isc_throw(CSVFileError, "closed stream when performing '"
                  << operation << "' on file '" << filename_ << "'");

    } else {
        fs_->clear();
    }
}

std::streampos
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
    } catch (const std::exception&) {
        return (0);
    }
    return (pos);
}

int
CSVFile::getColumnIndex(const std::string& col_name) const {
    for (size_t i = 0; i < cols_.size(); ++i) {
        if (cols_[i] == col_name) {
            return (static_cast<int>(i));
        }
    }
    return (-1);
}

std::string
CSVFile::getColumnName(const size_t col_index) const {
    if (col_index >= cols_.size()) {
        isc_throw(isc::OutOfRange, "column index " << col_index << " in the "
                  " CSV file '" << filename_ << "' is out of range; the CSV"
                  " file has only  " << cols_.size() << " columns ");
    }
    return (cols_[col_index]);
}

bool
CSVFile::next(CSVRow& row, const bool skip_validation) {
    // Set something as row validation error. Although, we haven't started
    // actual row validation we should get rid of any previously recorded
    // errors so as the caller doesn't interpret them as the current one.
    setReadMsg("validation not started");

    try {
        // Check that stream is "ready" for any IO operations.
        checkStreamStatusAndReset("get next row");

    } catch (isc::Exception& ex) {
        setReadMsg(ex.what());
        return (false);
    }

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
    row.parse(line);

    // And check if it is correct.
    return (skip_validation ? true : validate(row));
}

void
CSVFile::open(const bool seek_to_end) {
    // If file doesn't exist or is empty, we have to create our own file.
    if (size() == static_cast<std::streampos>(0)) {
        recreate();

    } else {
        // Try to open existing file, holding some data.
        fs_.reset(new std::fstream(filename_.c_str()));

        // Catch exceptions so as we can close the file if error occurs.
        try {
            // The file may fail to open. For example, because of insufficient
            // permissions. Although the file is not open we should call close
            // to reset our internal pointer.
            if (!fs_->is_open()) {
                isc_throw(CSVFileError, "unable to open '" << filename_ << "'");
            }
            // Make sure we are on the beginning of the file, so as we
            // can parse the header.
            fs_->seekg(0);
            if (!fs_->good()) {
                isc_throw(CSVFileError, "unable to set read pointer in the file '"
                          << filename_ << "'");
            }

            // Read the header.
            CSVRow header;
            if (!next(header, true)) {
                isc_throw(CSVFileError, "failed to read and parse header of the"
                          " CSV file '" << filename_ << "': "
                          << getReadMsg());
            }

            // Check the header against the columns specified for the CSV file.
            if (!validateHeader(header)) {
                isc_throw(CSVFileError, "invalid header '" << header
                          << "' in CSV file '" << filename_ << "': "
                          << getReadMsg());
            }

            // Everything is good, so if we haven't added any columns yet,
            // add them.
            if (getColumnCount() == 0) {
                for (size_t i = 0; i < header.getValuesCount(); ++i) {
                    addColumnInternal(header.readAt(i));
                }
            }

            // If caller requested that the pointer is set at the end of file,
            // move both read and write pointer.
            if (seek_to_end) {
                fs_->seekp(0, std::ios_base::end);
                fs_->seekg(0, std::ios_base::end);
                if (!fs_->good()) {
                    isc_throw(CSVFileError, "unable to move to the end of"
                              " CSV file '" << filename_ << "'");
                }
                fs_->clear();
            }

        } catch (const std::exception&) {
            close();
            throw;
        }
    }
}

void
CSVFile::recreate() {
    // There is no sense creating a file if we don't specify columns for it.
    if (getColumnCount() == 0) {
        close();
        isc_throw(CSVFileError, "no columns defined for the newly"
                  " created CSV file '" << filename_ << "'");
    }

    // Close any dangling files.
    close();
    fs_.reset(new std::fstream(filename_.c_str(), std::fstream::out));
    if (!fs_->is_open()) {
        close();
        isc_throw(CSVFileError, "unable to open '" << filename_ << "'");
    }
    // Opened successfully. Write a header to it.
    try {
        CSVRow header(getColumnCount());
        for (size_t i = 0; i < getColumnCount(); ++i) {
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

    for (size_t i = 0; i < getColumnCount(); ++i) {
        if (getColumnName(i) != header.readAt(i)) {
            return (false);
        }
    }
    return (true);
}

} // end of isc::util namespace
} // end of isc namespace
