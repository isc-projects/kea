// Copyright (C) 2016-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ROTATING_FILE_H
#define ROTATING_FILE_H

#include <dhcpsrv/legal_log_mgr_factory.h>

#include <mutex>

/// @file rotating_file.h Defines the class, RotatingFile, which implements
/// an appending text file that rotates to a new file on a daily basis.

namespace isc {
namespace legal_log {

/// @brief RotatingFile implements an appending text file which rotates
/// to a new file on a daily basis.  The physical file name(s) are
/// determined as follows:
///
/// Forms the current file name from:
///
///    "<path>/<base_name>.<date>.txt"
///
/// where:
/// - @b path - is the pathname supplied via the constructor. The path
/// must exist and be writable by the process
///
/// - @b base_name - an arbitrary text label supplied via the constructor
///
/// - @b date - is the system date, at the time the file is opened, in local
/// time.  The format of the value is CCYYMMDD (century,year,month,day) or
/// TXXXXXXXXXXXXXXXXXXXX (XXXXXXXXXXXXXXXXXXXX is the time in seconds since
/// epoch)
///
/// Prior to each write, the system date is compared to the current file date
/// to determine if rotation is necessary (i.e. day boundary has been crossed
/// since the last write).  If so, the current file is closed, and the new
/// file is created.
///
/// Content is added to the file by passing the desired line text into
/// the method, writeln().  This method prepends the content  with the current
/// date and time and appends an EOL.
///
/// The class implements virtual methods in facilitate unit testing
/// and derives from @c LegalLogMgr abstract class.
class RotatingFile : public isc::dhcp::LegalLogMgr {
public:

    /// @brief Time unit type used to rotate file.
    enum class TimeUnit {
        Second,
        Day,
        Month,
        Year
    };

    /// @brief Constructor.
    ///
    /// Create a RotatingFile for the given file name without opening the file.
    /// The file will be rotated after a specific time interval has passed since
    /// the log file was created or opened. If the time unit used is day, month
    /// or year, the file will be rotated at the beginning of the respective
    /// 'count' number of days, months or years (when the write function call
    /// detects that the day, month or year has changed).
    ///
    /// @note The supported parameters are:
    /// - logfile parameters:
    ///       - path
    ///       - base-name
    ///       - time-unit - one of: second, day, month, year
    ///       - prerotate
    ///       - postrotate
    ///       - count
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the manager configuration.
    ///
    /// @throw LegalLogMgrError if given file name is empty.
    RotatingFile(const isc::db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor.
    ///
    /// The destructor does call the close method.
    virtual ~RotatingFile();

    /// @brief Parse file specification and create forensic log backend.
    ///
    /// It supports the following parameters via the Hook Library Parameter
    /// mechanism:
    ///
    /// @b path - Directory in which the legal file(s) will be written.
    /// The default value is "<prefix>/var/log/kea". The directory must exist.
    ///
    /// @b base-name - An arbitrary value which is used in conjunction
    /// with current system date to form the current legal file name.
    /// It defaults to "kea-legal".
    ///
    /// Legal file names will have the form:
    ///
    ///     <path>/<base-name>.<CCYYMMDD>.txt
    ///     <path>/<base-name>.<TXXXXXXXXXXXXXXXXXXXX>.txt
    ///
    /// @b time-unit - The time unit used to rotate the log file. Valid values are:
    /// "second", "day", "month", or "year". It defaults to "day".
    ///
    /// @b count - The number of time units that need to pass until the log file is rotated.
    /// It can be any positive number, or 0, which disables log rotation. It defaults to 1.
    ///
    /// @b prerotate - An external executable or script called with the name of the file that
    /// will be closed. Kea does not wait for the process to finish.
    ///
    /// @b postrotate - An external executable or script called with the name of the file that
    /// was opened. Kea does not wait for the process to finish.
    ///
    /// @param parameters The library parameters.
    void apply(const isc::db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Opens the current file for writing.
    ///
    /// Forms the current file name if using seconds as time units:
    ///
    ///    "<path_>/<base_name_>.<TXXXXXXXXXXXXXXXXXXXX>.txt"
    ///
    /// where XXXXXXXXXXXXXXXXXXXX is the time in seconds since epoch,
    ///
    /// or if using days, months, years as time units:
    ///
    ///    "<path_>/<base_name_>.<CCYYMMDD>.txt"
    ///
    /// where CCYYMMDD is the current date in local time,
    ///
    /// and opens the file for appending. If the file does not exist
    /// it is created.  If the file is already open, the method simply
    /// returns.
    ///
    /// @throw LegalLogMgrError if the file cannot be opened.
    virtual void open();

    /// @brief Closes the underlying file.
    ///
    /// Method is exception safe.
    virtual void close();

    /// @brief Appends a string to the current file.
    ///
    /// Invokes rotate() and then attempts to add the new line
    /// followed by EOL to the end of the file. The content of
    /// new line will be:
    ///
    ///     "<timestamp>SP<text><EOL>"
    ///
    /// where:
    /// - @b timestamp - current local date and time as given by the
    /// strftime format "%Y-%m-%d %H:%M:%S %Z"
    ///
    /// - @b text - text supplied by the parameter
    ///
    /// - @b EOL - the character(s) generated std::endl
    ///
    /// @param addr Address or prefix (ignored).
    /// @param text String to append.
    ///
    /// @throw LegalLogMgrError if the write fails.
    virtual void writeln(const std::string& text, const std::string& addr);

    /// @brief Return backend type.
    ///
    /// Returns the type of the backend (e.g. "mysql", "logfile" etc.).
    ///
    /// @return Type of the backend.
    virtual std::string getType() const {
        return (std::string("logfile"));
    }

    /// @brief Returns the current file name.
    ///
    /// @return The file name.
    std::string getFileName() const {
        return (file_name_);
    }

    /// @brief Returns the file base name.
    ///
    /// @return The file base name.
    std::string getBaseName() const {
        return (base_name_);
    }

    /// @brief Returns the file path.
    ///
    /// @return The file path.
    std::string getPath() const {
        return (path_);
    }

    /// @brief Build the year-month-day string from a date.
    ///
    /// @param time_info The time info to be converted to string.
    /// @return the YYYYMMDD string.
    static std::string getYearMonthDay(const struct tm& time_info);

    /// @brief Function which updates the file name and internal timestamp from
    /// previously created file name (if it can still be used).
    ///
    /// @param time_info The current time info that should be used for the new
    /// name if previous files can not be reused.
    /// @param use_existing Flag which indicates if the name should be updated
    /// with previously created file name if the file can still be used.
    void updateFileNameAndTimestamp(struct tm& time_info, bool use_existing);

protected:

    /// @brief Open file using specified timestamp.
    ///
    /// @param time_info The current time info used to open log rotate file.
    /// @param use_existing Flag which indicates if the name should be updated
    /// with previously created file name if the file can still be used.
    virtual void openInternal(struct tm& time_info, bool use_existing);

    /// @brief Update file name with previously created file.
    ///
    /// @param time_info The current time info used to open log rotate file.
    void useExistingFiles(struct tm& time_info);

    /// @brief Rotates the file if necessary.
    ///
    /// The system date (no time component) is latter than the current file date
    /// (i.e. day boundary has been crossed), then the current physical file is
    /// closed and replaced with a newly created and open file.
    virtual void rotate();

    /// @brief Returns true if the file is open.
    ///
    /// @return True if the physical file is open, false otherwise.
    virtual bool isOpen() const;

private:
    /// @brief Appends a string to the current file.
    ///
    /// The caller must hold the mutex.
    ///
    /// @param text String to append.
    ///
    /// @throw LegalLogMgrError if the write fails.
    void writelnInternal(const std::string& text);

    /// @brief Directory in which the file(s) will be created.
    std::string path_;

    /// @brief Base name of the file.
    std::string base_name_;

    /// @brief The time unit used to rotate file.
    TimeUnit time_unit_;

    /// @brief The number of time units used to rotate the file.
    ///
    /// @node 0 means disable log file rotate.
    uint32_t count_;

    /// @brief Full name of the current file.
    std::string file_name_;

    /// @brief Output file stream.
    std::ofstream file_;

    /// @brief The prerotate script to call.
    std::string prerotate_;

    /// @brief The postrotate script to call.
    std::string postrotate_;

    /// @brief The timestamp used to check if the file should be rotated.
    time_t timestamp_;

    /// @brief Mutex to protect output.
    std::mutex mutex_;

public:
    /// @brief Factory class method.
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    ///
    /// @return The Rotating File Store Backend.
    static isc::dhcp::LegalLogMgrPtr
    factory(const isc::db::DatabaseConnection::ParameterMap& parameters);
};

/// @brief Initialization structure used to register and deregister RotateFile Forensic Log Mgr.
struct RotatingFileInit {
    // Constructor registers
    RotatingFileInit() {
        isc::dhcp::LegalLogMgrFactory::registerBackendFactory("logfile", RotatingFile::factory);
    }

    // Destructor deregisters
    ~RotatingFileInit() {
        isc::dhcp::LegalLogMgrFactory::unregisterBackendFactory("logfile");
    }
};

} // namespace legal_log
} // namespace isc

#endif
