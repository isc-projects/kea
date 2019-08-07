// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/date_time.h>
#include <boost/date_time/time_facet.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <locale>
#include <sstream>

using namespace boost::local_time;
using namespace boost::posix_time;

namespace isc {
namespace http {

HttpDateTime::HttpDateTime()
    : time_(boost::posix_time::second_clock::universal_time()) {
}

HttpDateTime::HttpDateTime(const boost::posix_time::ptime& t)
    : time_(t) {
}

std::string
HttpDateTime::rfc1123Format() const {
    return (toString("%a, %d %b %Y %H:%M:%S GMT", "RFC 1123"));
}

std::string
HttpDateTime::rfc850Format() const {
    return (toString("%A, %d-%b-%y %H:%M:%S GMT", "RFC 850"));
}

std::string
HttpDateTime::asctimeFormat() const {
    return (toString("%a %b %e %H:%M:%S %Y", "asctime"));
}

HttpDateTime
HttpDateTime::fromRfc1123(const std::string& time_string) {
    return (HttpDateTime(fromString(time_string,
                                    "%a, %d %b %Y %H:%M:%S %ZP",
                                    "RFC 1123")));
}

HttpDateTime
HttpDateTime::fromRfc850(const std::string& time_string) {
    return (HttpDateTime(fromString(time_string,
                                    "%A, %d-%b-%y %H:%M:%S %ZP",
                                    "RFC 850")));
}

HttpDateTime
HttpDateTime::fromAsctime(const std::string& time_string) {
    // The asctime() puts space instead of leading 0 in days of
    // month. The %e # formatter of time_input_facet doesn't deal
    // with this. To deal with this, we make a copy of the string
    // holding formatted time and replace a space preceding day
    // number with 0. Thanks to this workaround we can use the
    // %d formatter which seems to work fine. This has a side
    // effect of accepting timestamps such as Sun Nov 06 08:49:37 1994,
    // but it should be ok to be liberal in this case.
    std::string time_string_copy(time_string);
    boost::replace_all(time_string_copy, "  ", " 0");
    return (HttpDateTime(fromString(time_string_copy,
                                    "%a %b %d %H:%M:%S %Y",
                                    "asctime",
                                    false)));
}

HttpDateTime
HttpDateTime::fromAny(const std::string& time_string) {
    HttpDateTime date_time;
    // Try to parse as a timestamp specified in RFC 1123 format.
    try {
        date_time = fromRfc1123(time_string);
        return (date_time);
    } catch (...) {
        // Ignore errors, simply try different format.
    }

    // Try to parse as a timestamp specified in RFC 850 format.
    try {
        date_time = fromRfc850(time_string);
        return (date_time);
    } catch (...) {
        // Ignore errors, simply try different format.
    }

    // Try to parse as a timestamp output by asctime() function.
    try {
        date_time = fromAsctime(time_string);
    } catch (...) {
        isc_throw(HttpTimeConversionError,
                  "unsupported time format of the '" << time_string
                  << "'");
    }

    return (date_time);

}

std::string
HttpDateTime::toString(const std::string& format,
                       const std::string& method_name) const {
    std::ostringstream s;
    // Create raw pointer. The output stream will take responsibility for
    // deleting the object.
    time_facet* df(new time_facet(format.c_str()));
    s.imbue(std::locale(std::locale::classic(), df));

    // Convert time value to a string.
    s << time_;
    if (s.fail()) {
        isc_throw(HttpTimeConversionError, "unable to convert "
                  << "time value of '" << time_ << "'"
                  << " to " << method_name << " format");
    }
    return (s.str());
}


ptime
HttpDateTime::fromString(const std::string& time_string,
                         const std::string& format,
                         const std::string& method_name,
                         const bool zone_check) {
    std::istringstream s(time_string);
    // Create raw pointer. The input stream will take responsibility for
    // deleting the object.
    time_input_facet* tif(new time_input_facet(format));
    s.imbue(std::locale(std::locale::classic(), tif));

    time_zone_ptr zone(new posix_time_zone("GMT"));
    local_date_time ldt = local_microsec_clock::local_time(zone);

    // Parse the time value. The stream will not automatically detect whether
    // the zone is GMT. We need to check it on our own.
    s >> ldt;
    if (s.fail() ||
        (zone_check && (!ldt.zone() ||
                        ldt.zone()->std_zone_abbrev() != "GMT"))) {
        isc_throw(HttpTimeConversionError, "unable to parse "
                  << method_name << " time value of '"
                  << time_string << "'");
    }

    return (ldt.local_time());
}


} // namespace http
} // namespace isc
