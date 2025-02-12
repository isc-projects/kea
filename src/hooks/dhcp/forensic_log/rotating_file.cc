// Copyright (C) 2016-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/process_spawn.h>
#include <legal_log_log.h>
#include <backend_store.h>
#include <rotating_file.h>
#include <util/multi_threading_mgr.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <errno.h>
#include <iostream>
#include <set>
#include <sstream>
#include <time.h>
#include <dirent.h>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace legal_log {

RotatingFile::RotatingFile(const std::string& path,
                           const std::string& base_name,
                           const TimeUnit unit,
                           const uint32_t count,
                           const std::string& prerotate,
                           const std::string& postrotate)
    : path_(path), base_name_(base_name), time_unit_(unit), count_(count),
      file_name_(), file_(), prerotate_(prerotate), postrotate_(postrotate),
      timestamp_(0), mutex_() {

    if (path_.empty()) {
        isc_throw(BackendStoreError, "path cannot be blank");
    }

    if (base_name_.empty()) {
        isc_throw(BackendStoreError, "file name cannot be blank");
    }

    if (!prerotate.empty()) {
        try {
            ProcessSpawn process(ProcessSpawn::ASYNC, prerotate);
        } catch (const isc::Exception& ex) {
            isc_throw(BackendStoreError, "Invalid 'prerotate' parameter: " << ex.what());
        }
    }

    if (!postrotate.empty()) {
        try {
            ProcessSpawn process(ProcessSpawn::ASYNC, postrotate);
        } catch (const isc::Exception& ex) {
            isc_throw(BackendStoreError, "Invalid 'postrotate' parameter: " << ex.what());
        }
    }
}

RotatingFile::~RotatingFile() {
    close();
};

std::string
RotatingFile::getYearMonthDay(const struct tm& time_info) {
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%Y%m%d", &time_info);
    return (std::string(buffer));
}

void
RotatingFile::updateFileNameAndTimestamp(struct tm& time_info, bool use_existing) {
    std::ostringstream stream;
    std::string name = base_name_ + ".";

    stream << path_ << "/";

    if (time_unit_ == TimeUnit::Second) {
        time_t timestamp = mktime(&time_info);
        std::ostringstream name_stream;
        name_stream << std::right << std::setfill('0') << std::setw(20)
                    << static_cast<uint64_t>(timestamp);
        name += "T";
        name += name_stream.str();
    } else {
        name += getYearMonthDay(time_info);
    }

    stream << name << ".txt";

    file_name_ = stream.str();

    if (use_existing) {
        useExistingFiles(time_info);
    }
}

void
RotatingFile::useExistingFiles(struct tm& time_info) {
    DIR* dir = opendir(path_.c_str());
    if (!dir) {
        return;
    }

    std::unique_ptr<DIR, void(*)(DIR*)> defer(dir, [](DIR* d) { closedir(d); });

    // Set of sorted files by name.
    std::set<std::string> files;

    // Add only files of interest that could be used to append logging data.
    for (struct dirent* dent = readdir(dir); dent; dent = readdir(dir)) {
        std::string name(dent->d_name);
        // Supported file formats are: 'base-name.YYYYMMDD.txt' and
        // 'base-name.TXXXXXXXXXXXXXXXXXXXX.txt'.
        if ((name.size() != (base_name_.size() + sizeof(".YYYYMMDD.txt") - 1)) &&
            (name.size() != (base_name_.size() + sizeof(".TXXXXXXXXXXXXXXXXXXXX.txt") - 1))) {
            continue;
        }

        // Skip non .txt files.
        if (name.substr(name.size() - 4) != ".txt") {
            continue;
        }

        std::string file = name.substr(0, name.size() - 4);

        // Skip files that are not beginning with base name.
        if (base_name_ != file.substr(0, base_name_.size())) {
            continue;
        }

        file = file.substr(base_name_.size() + 1);
        uint32_t tag_size = sizeof("YYYYMMDD") - 1;
        uint32_t index = 0;
        if (time_unit_ == TimeUnit::Second) {
            if (file.at(0) != 'T') {
                continue;
            }
            tag_size = sizeof("TXXXXXXXXXXXXXXXXXXXX") - 1;
            index = 1;
        }
        if (file.size() != tag_size) {
            continue;
        }
        for (; index < tag_size; ++index) {
            if (!std::isdigit(file.at(index))) {
                break;
            }
        }
        if (index != tag_size) {
            continue;
        }
        files.insert(file);
    }

    if (!files.size()) {
        return;
    }

    std::string file = *files.rbegin();

    if (time_unit_ == TimeUnit::Second) {
        time_t file_timestamp;
        try {
            file_timestamp = static_cast<time_t>(boost::lexical_cast<uint64_t>(file.substr(1)));
        } catch (...) {
            return;
        }
        time_t current_timestamp = mktime(&time_info);
        if (current_timestamp < (file_timestamp + count_)) {
            localtime_r(&file_timestamp, &time_info);
        } else {
            file.clear();
        }
    } else {
        boost::gregorian::date file_date;
        try {
            file_date = boost::gregorian::from_undelimited_string(file);
        } catch (...) {
            return;
        }
        boost::gregorian::date current_date = boost::gregorian::date_from_tm(time_info);
        if (time_unit_ == TimeUnit::Day) {
            boost::gregorian::date_duration dd(count_);
            if (current_date < (file_date + dd)) {
                time_info = boost::gregorian::to_tm(file_date);
            } else {
                file.clear();
            }
        } else if (time_unit_ == TimeUnit::Month) {
            boost::gregorian::months mm(count_);
            if (current_date < (file_date + mm)) {
                time_info = boost::gregorian::to_tm(file_date);
            } else {
                file.clear();
            }
        } else if (time_unit_ == TimeUnit::Year) {
            boost::gregorian::years yy(count_);
            if (current_date < (file_date + yy)) {
                time_info = boost::gregorian::to_tm(file_date);
            } else {
                file.clear();
            }
        }
    }
    if (!file.empty()) {
        file_name_ = path_ + "/" + base_name_ + "." + file + ".txt";
    }
}

void
RotatingFile::open() {
    if (isOpen() || MultiThreadingMgr::instance().isTestMode()) {
        return;
    }

    struct tm current_time_info = currentTimeInfo();
    openInternal(current_time_info, true);
}

void
RotatingFile::openInternal(struct tm& time_info, bool use_existing) {
    updateFileNameAndTimestamp(time_info, use_existing);
    // Open the file
    file_.open(file_name_.c_str(), std::ofstream::app);
    int sav_error = errno;
    if (!file_.is_open()) {
        isc_throw(BackendStoreError, "cannot open file:" << file_name_
                  << " reason: " << strerror(sav_error));
    }

    // Store the timestamp for the new open file
    timestamp_ = mktime(&time_info);

    LOG_INFO(legal_log_logger, LEGAL_LOG_STORE_OPENED)
             .arg(file_name_);
}

void
RotatingFile::rotate() {
    if (isOpen() && !count_) {
        return;
    }

    bool rotate_file = false;

    // Time info used for old timestamp
    struct tm time_info;
    localtime_r(&timestamp_, &time_info);

    // Time info used for new timestamp
    struct tm current_time_info = currentTimeInfo();

    // New timestamp
    time_t timestamp = mktime(&current_time_info);

    // Date used for old timestamp
    boost::gregorian::date old_date = boost::gregorian::date_from_tm(time_info);

    // Date used for new timestamp
    boost::gregorian::date new_date = boost::gregorian::date_from_tm(current_time_info);

    if (!isOpen()) {
        rotate_file = true;
    } else if (time_unit_ == TimeUnit::Second) {
        if (count_ <= (timestamp - timestamp_)) {
            rotate_file = true;
        }
    } else if (time_unit_ == TimeUnit::Day) {
        boost::gregorian::date_duration dd(count_);
        if ((old_date + dd) <= new_date) {
            rotate_file = true;
        }
    } else if (time_unit_ == TimeUnit::Month) {
        boost::gregorian::months mm(count_);
        if ((old_date + mm) <= new_date) {
            rotate_file = true;
        }
    } else if (time_unit_ == TimeUnit::Year) {
        boost::gregorian::years yy(count_);
        if ((old_date + yy) <= new_date) {
            rotate_file = true;
        }
    }

    if (rotate_file) {
        close();

        if (!prerotate_.empty()) {
            ProcessArgs args;
            args.push_back(getFileName());
            ProcessSpawn process(ProcessSpawn::ASYNC, prerotate_, args);
            process.spawn(true);
        }

        openInternal(current_time_info, false);

        if (!postrotate_.empty()) {
            ProcessArgs args;
            args.push_back(getFileName());
            ProcessSpawn process(ProcessSpawn::ASYNC, postrotate_, args);
            process.spawn(true);
        }
    }
}

void
RotatingFile::writeln(const std::string& text, const std::string&) {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(mutex_);
        writelnInternal(text);
    } else {
        writelnInternal(text);
    }
}

void
RotatingFile::writelnInternal(const std::string& text) {
    if (text.empty()) {
        return;
    }

    // Call rotate in case we've crossed days since we last wrote.
    rotate();

    std::string timestamp = getNowString();
    std::stringstream ss(text);
    for (std::string line; std::getline(ss, line, '\n');) {
        file_ << timestamp << " " << line << std::endl;
    }
    int sav_error = errno;
    if (!file_.good()) {
        isc_throw(BackendStoreError, "error writing to file:" << file_name_
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
            LOG_INFO(legal_log_logger, LEGAL_LOG_STORE_CLOSED)
                     .arg(file_name_);
            file_.flush();
            file_.close();
        }
    } catch (const std::exception& ex) {
        // Highly unlikely to occur but let's at least spit out an error.
        // Beyond that we swallow it for tidiness.
        LOG_ERROR(legal_log_logger, LEGAL_LOG_STORE_CLOSE_ERROR)
                  .arg(file_name_).arg(ex.what());
    }
}

} // namespace legal_log
} // namespace isc
