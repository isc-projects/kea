// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <config.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <cc/json_feed.h>
#include <cc/simple_parser.h>
#include <asiolink/io_address.h>

#include <string>
#include <vector>

using namespace isc;
using namespace isc::data;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider fdp(data, size);

    ElementPtr elem;

    std::string val1 = fdp.ConsumeRandomLengthString(8);
    std::string val2 = fdp.ConsumeRandomLengthString(8);
    Element::types type1 = static_cast<Element::types>(fdp.ConsumeIntegralInRange<int>(0, 8));
    Element::types type2 = static_cast<Element::types>(fdp.ConsumeIntegralInRange<int>(0, 8));

    SimpleRequiredKeywords required;
    required.push_back(val1);
    required.push_back(val2);

    SimpleKeywords keywords;
    keywords[val1] = type1;
    keywords[val2] = type2;

    ParamsList params;
    params.push_back(val1);
    params.push_back(val2);

    const std::string payload = fdp.ConsumeRemainingBytesAsString();

    // Target JSONFeed with random data
    try {
        config::JSONFeed feed;
        feed.initModel();
        feed.postBuffer(payload.c_str(), payload.length());
        feed.poll();
        feed.needData();
        feed.feedOk();
        feed.getProcessedText();
        feed.toElement();
        feed.getErrorMessage();
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    // Try parse payload to Element pointer
    try {
        elem = Element::fromJSON(payload);
    } catch (...) {
        // Early exit for invalid json
        return 0;
    }

    // Target parseIntTriplet
    try {
        SimpleParser parser;
        parser.parseIntTriplet(elem, val1);
        parser.parseIntTriplet(elem, val2);
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    // Target checkRequired
    try {
        SimpleParser::checkRequired(required, elem);
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    // Target checkKeywords
    try {
        SimpleParser::checkKeywords(keywords, elem);
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    // Target deriveParams
    try {
        SimpleParser::deriveParams(elem, Element::createMap(), params);
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    return 0;
}
