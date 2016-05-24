// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <legal_log_log.h>
#include <rotating_file.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <errno.h>
#include <iostream>
#include <sstream>
#include <time.h>

namespace isc {
namespace legal_log {

RotatingFile::RotatingFile(const std::string& path, const std::string& base_name)
    : path_(path), base_name_(base_name), file_day_(), file_name_(), file_() {

    if (path_.empty()) {
        isc_throw(RotatingFileError, "path cannot be blank");
    }

    if (base_name_.empty()) {
        isc_throw(RotatingFileError, "file name cannot be blank");
    }
}

RotatingFile::~RotatingFile(){
    close();
};

boost::gregorian::date
RotatingFile::today() const {
    return (boost::gregorian::day_clock::local_day());
}

time_t
RotatingFile::now() const {
    time_t curtime;
    return (time(&curtime));
}

std::string
RotatingFile::getNowString(const std::string& format) const {
    // Get a text representation of the current time.
    char buffer[128];
    time_t curtime = now();
    struct tm* timeinfo;
    timeinfo = localtime(&curtime);

    if (!strftime(buffer, sizeof(buffer), format.c_str(), timeinfo)) {
        isc_throw(RotatingFileError,
                    "Timestamp format format: " << format
                    << " result is too long, maximum allowed: "
                    << sizeof(buffer));
    }
    return (std::string(buffer));
}

void
RotatingFile::open() {
    if (isOpen()) {
        return;
    }

    // Construct the file name
    file_day_ = today();
    boost::gregorian::date::ymd_type ymd = file_day_.year_month_day();
    std::ostringstream stream;

    stream << path_ << "/" << base_name_ << "." << ymd.year
           << std::right << std::setfill('0') << std::setw(2)
           << ymd.month.as_number()
           << ymd.day << ".txt";

    file_name_ = stream.str();

    // Open the file
    file_.open(file_name_.c_str(), std::ofstream::app);
    int sav_error = errno;
    if (!file_.is_open()) {
        isc_throw(RotatingFileError, "cannot open file:" << file_name_
                                  << " reason: " << strerror(sav_error));
    }

    LOG_INFO(legal_log_logger, LEGAL_LOG_FILE_OPENED)
             .arg(file_name_);
}

void
RotatingFile::rotate() {
    if (file_day_ < today()) {
        close();
    }

    // If we're already open, no harm, no foul
    open();
}

void
RotatingFile::writeln(const std::string& text) {
    // Call rotate in case we've crossed days since we last wrote.
    rotate();

    file_ << getNowString() << " " << text << std::endl;
    int sav_error = errno;
    if (!file_.good()) {
        isc_throw(RotatingFileError, "error writing to file:" << file_name_
                                 << " reason: " << strerror(sav_error));
    }
}

bool
RotatingFile::isOpen() const {
    return (file_.is_open());
}

void
RotatingFile::close() {
    try {
        if (file_.is_open()) {
            LOG_INFO(legal_log_logger, LEGAL_LOG_FILE_CLOSED)
                     .arg(file_name_);
            file_.close();
        }
    } catch (const std::exception& ex) {
        // Highly unlikely to occur but let's at least spit out an error.
        // Beyond that we swallow it for tidiness.
        LOG_ERROR(legal_log_logger, LEGAL_LOG_FILE_CLOSE_ERROR)
                  .arg(file_name_).arg(ex.what());
    }
}

std::string
RotatingFile::genDurationString(const uint32_t secs) {
    // Because Kea handles lease lifetimes as uint32_t and supports
    // a value of 0xFFFFFFFF (infinite lifetime), we don't use things like
    // boost:posix_time::time_duration as they work on longs.  Therefore
    // we'll figure it out ourselves.  Besides, the math ain't that hard.
    uint32_t seconds = secs % 60;
    uint32_t remainder = secs / 60;
    uint32_t minutes = remainder % 60;
    remainder /= 60;
    uint32_t hours = remainder % 24;
    uint32_t days = remainder / 24;

    std::ostringstream os;
    // Only spit out days if we have em.
    if (days) {
        os << days << " days ";
    }

    os << hours << " hrs "
        << minutes << " mins "
        << seconds << " secs";

    return (os.str());
}

std::string
RotatingFile::vectorHexDump(const std::vector<uint8_t>& bytes,
                         const std::string& delimiter) {
    std::stringstream tmp;
    tmp << std::hex;
    bool delim = false;
    for (std::vector<uint8_t>::const_iterator it = bytes.begin();
         it != bytes.end(); ++it) {
        if (delim) {
            tmp << delimiter;
        }
        tmp << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(*it);
        delim = true;
    }
    return (tmp.str());
}

} // namespace legal_log
} // namespace isc
