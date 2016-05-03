// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <legal_log_log.h>
#include <legal_file.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <errno.h>
#include <iostream>
#include <sstream>
#include <time.h>

namespace isc {
namespace legal_log {

LegalFile::LegalFile(const std::string& path, const std::string& base_name)
    : path_(path), base_name_(base_name), file_day_(), file_name_(), file_() {

    if (path_.empty()) {
        isc_throw(LegalFileError, "path cannot be blank");
    }

    if (base_name_.empty()) {
        isc_throw(LegalFileError, "file name cannot be blank");
    }
}

LegalFile::~LegalFile(){
    close();
};

boost::gregorian::date
LegalFile::today() {
    return (boost::gregorian::day_clock::local_day());
}

time_t
LegalFile::now() {
    time_t curtime;
    return(time(&curtime));
}

std::string
LegalFile::getNowString(const std::string& format) {
    // Get a text representation of the current time.
    char buffer[128];
    time_t curtime = now();
    struct tm* timeinfo;
    timeinfo = localtime(&curtime);

    if (!strftime(buffer, sizeof(buffer), format.c_str(), timeinfo)) {
        isc_throw(LegalFileError,
                    "Timestamp format format: " << format
                    << " result is too long, maximum allowed: "
                    << sizeof(buffer));
    }
    return (std::string(buffer));
}

void
LegalFile::open() {
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
        isc_throw(LegalFileError, "cannot open file:" << file_name_
                                  << " reason: " << strerror(sav_error));
    }

    LOG_INFO(legal_log_logger, LEGAL_LOG_HOOK_FILE_OPENED)
             .arg(file_name_);
}

void
LegalFile::rotate() {
    if (file_day_ < today()) {
        close();
    }

    // If we're already open, no harm, no foul
    open();
}

void
LegalFile::writeln(const std::string& text) {
    // Call rotate in case we've crossed days since we last wrote.
    rotate();

    file_ << getNowString() << " " << text << std::endl;
    int sav_error = errno;
    if (!file_.good()) {
        isc_throw(LegalFileError, "error writing to file:" << file_name_
                                 << " reason: " << strerror(sav_error));
    }
}

bool
LegalFile::isOpen() const {
    return (file_.is_open());
}

void
LegalFile::close() {
    try {
        if (file_.is_open()) {
            LOG_INFO(legal_log_logger, LEGAL_LOG_HOOK_FILE_CLOSED)
                     .arg(file_name_);
            file_.close();
        }
    } catch (const std::exception& ex) {
        // Highly unlikely to occur but let's at least spit out an error.
        // Beyond that we swallow it for tidiness.
        LOG_ERROR(legal_log_logger, LEGAL_LOG_HOOK_FILE_CLOSE_ERROR)
                  .arg(file_name_).arg(ex.what());
    }
}

std::string
LegalFile::genDurationString(uint32_t secs) {
    // In case Kea decides to support the notion of infinite lease
    // we'll emit it as such.
    if (secs == 0xFFFFFFFF) {
        return ("infinite duration");
    }

    // Because Kea handles lease lifetimes as uint32_t, we can't use things
    // boost:posix_time::time_duration as they work on longs.  Therefore
    // we'll figure it out ourselves.  Besides, the math ain't that hard.
    uint32_t seconds = secs % 60;
    secs /= 60;
    uint32_t minutes = secs % 60;
    secs /= 60;
    uint32_t hours = secs % 24;
    uint32_t days = secs / 24;

    std::ostringstream os;
    // Only spit out days if we have em.
    if (days) {
        os << days << (days > 1 ? " days " : " day ");
    }

    os << hours << " hrs "
        << minutes << " min "
        << seconds << " secs";

    return (os.str());
}

} // namespace legal_log
} // namespace isc
