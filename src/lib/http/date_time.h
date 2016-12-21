// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
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

class HttpTimeConversionError : public Exception {
public:
    HttpTimeConversionError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

class HttpDateTime {
public:

    HttpDateTime();

    explicit HttpDateTime(const boost::posix_time::ptime& t);

    boost::posix_time::ptime getPtime() const {
        return (time_);
    }

    std::string rfc1123Format() const;

    std::string rfc850Format() const;

    std::string asctimeFormat() const;

    static HttpDateTime fromRfc1123(const std::string& time_string);

    static HttpDateTime fromRfc850(const std::string& time_string);

    static HttpDateTime fromAsctime(const std::string& time_string);

    static HttpDateTime fromAny(const std::string& time_string);

private:

    std::string toString(const std::string& format,
                         const std::string& method_name) const;

    static boost::posix_time::ptime
    fromString(const std::string& time_string, const std::string& format,
               const std::string& method_name, const bool zone_check = true);

    boost::posix_time::ptime time_;

};

} // namespace http
} // namespace isc

#endif
