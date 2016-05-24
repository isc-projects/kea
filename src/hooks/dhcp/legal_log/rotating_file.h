// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef ROTATING_FILE_H
#define ROTATING_FILE_H

/// @file rotating_file.h Defines the class, RotatingFile, which implements
/// an appending text file that rotates to a new file on a daily basis.

#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <fstream>
#include <string>

namespace isc {
namespace legal_log {

/// @brief Thrown if a RotatingFile encounters an error.
class RotatingFileError : public isc::Exception {
public:
    RotatingFileError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};

/// @brief RotatingFile implements an appending text file which rotates
/// to a new file on a daily basis.  The physical file name(s) are
/// deteremined as follows:
///
/// Forms the current file name from:
///
///    <path>/<base_name>.<date>.txt
///
/// where:
/// - <b>path</b> - is the pathname supplied via the constructor. The path
/// must exist and be writable by the process
///
/// - <b>base_name</b> - an arbitrary text label supplied via the constructor
///
/// - <b>date</b> - is the system date, at the time the file is opened, in local
/// time.  The format of the value is CCYYMMDD (century,year,month,day)
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
/// The class implements virtual methods in facilitate unit testing.
class RotatingFile {
public:
    /// @brief Constructor
    ///
    /// Create a RotatingFile for the given file name without opening the file.
    /// @param path Directory in which file(s) will be created
    /// @param base_name Base file name to use when creating files
    ///
    /// @throw RotatingFileError if given file name is empty.
    RotatingFile(const std::string& path, const std::string& base_name);

    /// @brief Destructor.
    ////
    /// The destructor does call the close method.
    virtual ~RotatingFile();

    /// @brief Opens the current file for writing.
    ///
    /// Forms the current file name from:
    ///
    ///    <path_>/<base_name_>.<CCYYMMDD>.txt
    ///
    /// where CCYYMMDD is the current date in local time,
    ///
    /// and opens the file for appending. If the file does not exist
    /// it is created.  If the file is already open, the method simply
    /// returns.
    ///
    /// @throw RotatingFileError if the file cannot be opened.
    virtual void open();

    /// @brief Closes the underlying file.
    ///
    /// Method is exception safe.
    virtual void close();

    /// @brief Rotates the file if necessary
    ///
    /// The system date (no time component) is latter than the current file date
    /// (i.e. day boundary has been crossed), the the current physical file is
    /// closed and replaced with a newly created and open file.
    virtual void rotate();

    /// @brief Returns true if the file is open.
    ///
    /// @return True if the physical file is open, false otherwise.
    virtual bool isOpen() const;

    /// @brief Appends a string to the current file
    ///
    /// Invokes rotate() and then attempts to add the new line
    /// followed by EOL to the end of the file. The content of
    /// new line will be:
    ///
    ///     <timestamp>\b<text><EOL>
    ///
    /// where:
    /// -<b>timestamp<\b> - current local date and time as given by the
    /// strftime format "%Y-%m-%d %H:%M:%S %Z"
    ///
    /// -<b>text<\b> - text supplied by the parameter
    ///
    /// -<b>EOL<\b> - the character(s) generated std::endl
    ///
    /// @param text String to append
    ///
    /// @throw RotatingFileError if the write fails
    virtual void writeln(const std::string& text);

protected:
    /// @brief Returns the current local date
    /// This is exposed primarily to simplify testing.
    virtual boost::gregorian::date today() const;

    /// @brief Returns the current system time
    /// This is exposed primarily to simplify testing.
    virtual time_t now() const;

public:
    /// @brief Returns the current date and time as string
    ///
    /// Returns the current local date and time as a string based on the
    /// given format.  Maximum length of the result is 128 bytes.
    ///
    /// @param format Desired format for the string. Permissable formatting is
    /// that supported by strftime.  The default is: "%Y-%m-%d %H:%M:%S %Z"
    ///
    /// @return std::string containg the formatted current date and time
    /// @throw RotatingFileError if the result string is larger than 128 bytes.
    virtual std::string getNowString(const std::string&
                                     format="%Y-%m-%d %H:%M:%S %Z") const;

    /// @brief Returns the current file name
    std::string getFileName() const {
        return (file_name_);
    }

    /// @brief Returns the date of the current file
    boost::gregorian::date getFileDay() const {
        return (file_day_);
    }

    /// @brief Creates seconds into a text string of days, hours, minutes
    /// and seconds
    ///
    /// The output string will have the following format:
    ///
    ///    {<d> day(s) }<h> hrs <m> min <s> secs
    /// Examples:
    ///
    ///     0 hrs 0 min 30 secs
    ///     2 hrs 11 min 50 secs
    ///     1 day 1 hrs 0 min 0 secs
    ///     60 days 0 hrs 0 min 10 secs
    ///
    /// @param secs Number of seconds to convert
    /// @return String containing the duration text
    static std::string genDurationString(const uint32_t secs);

    /// @brief Creates a string of hex digit pairs from a vector of bytes
    ///
    /// @param bytes Vector of bytes to convert
    /// @param delimiter String to use a delimiter, defaults to ":"
    ///
    /// @return std::string containing the hex output
    static std::string vectorHexDump(const std::vector<uint8_t>& bytes,
                                     const std::string& delimiter = ":");
private:
    /// @brief Directory in which the file(s) will be created
    std::string path_;

    /// @brief Base name of the file
    std::string base_name_;

    /// @brief Date of current file
    boost::gregorian::date file_day_;

    /// @brief Full name of the current file
    std::string file_name_;

    /// @brief Output file stream.
    std::ofstream file_;
};

/// @brief Defines a smart pointer to a RotatingFile.
typedef boost::shared_ptr<RotatingFile> RotatingFilePtr;

} // namespace legal_log
} // namespace isc

#endif
