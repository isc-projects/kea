// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <http/date_time.h>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/date_facet.hpp>
#include <boost/date_time/time_facet.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <sstream>

using namespace boost::gregorian;
using namespace boost::local_time;
using namespace boost::posix_time;

namespace isc {
namespace http {

HttpDateTime::HttpDateTime()
    : time_(boost::posix_time::microsec_clock::universal_time()) {
}

HttpDateTime::HttpDateTime(const ptime& t)
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
    try {
        date_time = fromRfc1123(time_string);
        return (date_time);
    } catch (...) {
        ;
    }

    try {
        date_time = fromRfc850(time_string);
        return (date_time);
    } catch (...) {
        ;
    }

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
    time_facet* df(new time_facet(format.c_str()));
    s.imbue(std::locale(s.getloc(), df));
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
    time_input_facet* tif(new time_input_facet(format));
    s.imbue(std::locale(s.getloc(), tif));

    time_zone_ptr zone(new posix_time_zone("GMT"));
    local_date_time ldt = local_microsec_clock::local_time(zone);
    s >> ldt;
    if (s.fail() ||
        (zone_check && (!ldt.zone() || ldt.zone()->std_zone_abbrev() != "GMT"))) {
        isc_throw(HttpTimeConversionError, "unable to parse "
                  << method_name << " time value of '"
                  << time_string << "'");
    }

    return (ldt.local_time());
}


} // namespace http
} // namespace isc
