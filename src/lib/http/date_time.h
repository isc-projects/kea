// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_DATE_TIME_H
#define HTTP_DATE_TIME_H

#include <exceptions/exceptions.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

namespace isc {
namespace http {

/// @brief Exception thrown when there is an error during time conversion.
///
/// The most common reason for this exception is that the unsupported time
/// format was used as an input to the time parsing functions.
class HttpTimeConversionError : public Exception {
public:
    HttpTimeConversionError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief This class parses and generates time values used in HTTP.
///
/// The HTTP protocol have historically allowed 3 different date/time formats
/// (see https://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html). These are:
/// - Sun, 06 Nov 1994 08:49:37 GMT
/// - Sunday, 06-Nov-94 08:49:37 GMT
/// - Sun Nov  6 08:49:37 1994
///
/// The first format is preferred but implementations must also support
/// remaining two obsolete formats for compatibility. This class implements
/// parsers and generators for all three formats. It uses @c boost::posix_time
/// to represent time and date. It uses @c boost::date_time::time_facet
/// and @c boost::date_time::time_input_facet to generate and parse the
/// timestamps.
class HttpDateTime {
public:

    /// @brief Default constructor.
    ///
    /// Sets current universal time as time value.
    /// Time resolution is to seconds (i.e no fractional seconds).
    HttpDateTime();

    /// @brief Construct from @c boost::posix_time::ptime object.
    ///
    /// @param t time value to be set.
    explicit HttpDateTime(const boost::posix_time::ptime& t);

    /// @brief Returns time encapsulated by this class.
    ///
    /// @return @c boost::posix_time::ptime value encapsulated by the instance
    /// of this class.
    boost::posix_time::ptime getPtime() const {
        return (time_);
    }

    /// @brief Returns time value formatted as specified in RFC 1123.
    ///
    /// @return A string containing time value formatted as
    /// Sun, 06 Nov 1994 08:49:37 GMT.
    std::string rfc1123Format() const;

    /// @brief Returns time value formatted as specified in RFC 850.
    ///
    /// @return A string containing time value formatted as
    /// Sunday, 06-Nov-94 08:49:37 GMT.
    std::string rfc850Format() const;

    /// @brief Returns time value formatted as output of ANSI C's
    /// asctime().
    ///
    /// @return A string containing time value formatted as
    /// Sun Nov  6 08:49:37 1994.
    std::string asctimeFormat() const;

    /// @brief Creates an instance from a string containing time value
    /// formatted as specified in RFC 1123.
    ///
    /// @param time_string Input string holding formatted time value.
    /// @return Instance of @ref HttpDateTime.
    /// @throw HttpTimeConversionError if provided timestamp has invalid
    /// format.
    static HttpDateTime fromRfc1123(const std::string& time_string);

    /// @brief Creates an instance from a string containing time value
    /// formatted as specified in RFC 850.
    ///
    /// @param time_string Input string holding formatted time value.
    /// @return Instance of @ref HttpDateTime.
    /// @throw HttpTimeConversionError if provided timestamp has invalid
    /// format.
    static HttpDateTime fromRfc850(const std::string& time_string);

    /// @brief Creates an instance from a string containing time value
    /// formatted as output from asctime() function.
    ///
    /// @param time_string Input string holding formatted time value.
    /// @return Instance of @ref HttpDateTime.
    /// @throw HttpTimeConversionError if provided timestamp has invalid
    /// format.
    static HttpDateTime fromAsctime(const std::string& time_string);

    /// @brief Creates an instance from a string containing time value
    /// formatted in one of the supported formats.
    ///
    /// This method will detect the format of the time value and parse it.
    /// It tries parsing the value in the following order:
    /// - a format specified in RFC 1123,
    /// - a format specified in RFC 850,
    /// - a format of asctime output.
    ///
    /// @param time_string Input string holding formatted time value.
    /// @return Instance of @ref HttpDateTime.
    /// @throw HttpTimeConversionError if provided value doesn't match any
    /// of the supported formats.
    static HttpDateTime fromAny(const std::string& time_string);

private:

    /// @brief Generic method formatting a time value to a specified format.
    ////
    /// @param format Time format as accepted by the
    /// @c boost::date_time::time_facet.
    std::string toString(const std::string& format,
                         const std::string& method_name) const;

    /// @brief Generic method parsing time value and converting it to the
    /// instance of @c boost::posix_time::ptime.
    ///
    /// @param time_string Input string holding formatted time value.
    /// @param format Time format as accepted by the
    /// @c boost::date_time::time_input_facet.
    /// @param method_name Name of the expected format to appear in the error
    /// message if parsing fails, e.g. RFC 1123, RFC 850 or asctime.
    /// @param zone_check Indicates if the time zone name should be validated
    /// during parsing. This should be set to false for the formats which
    /// lack time zones (e.g. asctime).
    ///
    /// @return Instance of the @ref boost::posix_time::ptime created from the
    /// input string.
    /// @throw HttpTimeConversionError if provided value doesn't match the
    /// specified format.
    static boost::posix_time::ptime
    fromString(const std::string& time_string, const std::string& format,
               const std::string& method_name, const bool zone_check = true);

    /// @brief Time value encapsulated by this class instance.
    boost::posix_time::ptime time_;

};

} // namespace http
} // namespace isc

#endif
