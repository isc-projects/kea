// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <http/http_header.h>
#include <util/strutil.h>
#include <boost/lexical_cast.hpp>

namespace isc {
namespace http {

HttpHeader::HttpHeader(const std::string& header_name,
                       const std::string& header_value)
    : header_name_(header_name), header_value_(header_value) {
}

uint64_t
HttpHeader::getUint64Value() const {
    try {
        return (boost::lexical_cast<uint64_t>(header_value_));

    } catch (const boost::bad_lexical_cast& ex) {
        isc_throw(BadValue, header_name_ << " HTTP header value "
                  << header_value_ << " is not a valid number");
    }
}

std::string
HttpHeader::getLowerCaseName() const {
    std::string ln = header_name_;
    util::str::lowercase(ln);
    return (ln);
}

std::string
HttpHeader::getLowerCaseValue() const {
    std::string lc = header_value_;
    util::str::lowercase(lc);
    return (lc);
}

bool
HttpHeader::isValueEqual(const std::string& v) const {
    std::string lcv = v;
    util::str::lowercase(lcv);
    return (lcv == getLowerCaseValue());
}


} // end of namespace isc::http
} // end of namespace isc
