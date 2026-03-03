// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <config.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <exceptions/exceptions.h>
#include <util/str.h>
#include <util/csv_file.h>
#include <util/encode/utf8.h>
#include <util/boost_time_utils.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <string>
#include <vector>
#include <cstddef>

using namespace boost::posix_time;
using namespace isc::util;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider fdp(data, size);

    const bool isEscape = fdp.ConsumeBool();
    const std::string delim = fdp.ConsumeBytesAsString(1);
    const std::string payload = fdp.ConsumeRemainingBytesAsString();

    std::vector<uint8_t> out;

    // Target str tokens
    try {
        str::tokens(payload, delim, isEscape);
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    // Target str quotedStringToBinary
    try {
        str::quotedStringToBinary(payload);
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    // Target str decodeFormattedHexString
    try {
        str::decodeFormattedHexString(payload, out);
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    // Target str decodeColonSeparatedHexString
    try {
        str::decodeColonSeparatedHexString(payload, out);
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    // Target str decodeSeparatedHexString
    try {
        str::decodeSeparatedHexString(payload, delim, out);
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    // Target str trim
    try {
        str::trim(payload);
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    // Target str lowercase/uppercase
    try {
        std::string temp = payload;
        str::lowercase(temp);
        str::uppercase(temp);
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    // Target CSVRow
    try {
        CSVRow row(payload, delim[0]);
        for (int i = 0; i < row.getValuesCount(); i++) {
            row.readAt(i);
            row.readAtEscaped(i);
        }
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    // Target encodeUtf8
    try {
        encode::encodeUtf8(payload);
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    // Prepare posix_time object
    ptime pt;
    try {
        pt = time_from_string(payload);
    } catch (...) {
        // Failed for time_from_string, try from_iso_extended_string
        try {
            pt = from_iso_extended_string(payload);
        } catch (...) {
            // Failed to create posix_time object, early exit
            return 0;
        }
    }

    // Target ptimeToText
    try {
        ptimeToText(pt);
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    // Target durationToText
    try {
        time_duration td = pt.time_of_day();
        isc::util::durationToText(td);
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    return 0;
}

