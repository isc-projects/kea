// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <config.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <dns/name.h>
#include <dns/tsig.h>
#include <dns/rdata.h>

#include <gss_tsig_context.h>
#include <gss_tsig_key.h>
#include <tkey_exchange.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <memory>

using namespace isc;
using namespace isc::dns;
using namespace isc::gss_tsig;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider fdp(data, size);

    // Prepare basic key crypto information
    std::string key_name = fdp.ConsumeRandomLengthString(64);
    if (key_name.empty()) key_name = "fuzz-key";
    std::string tsig_rdata_txt = fdp.ConsumeRandomLengthString(1024);
    std::string owner_txt = fdp.ConsumeRandomLengthString(128);
    const uint16_t qid = fdp.ConsumeIntegral<uint16_t>();
    const bool do_chunked = fdp.ConsumeBool();

    // Target correct key sign and verify
    try {
        std::vector<uint8_t> payload = fdp.ConsumeBytes<uint8_t>(fdp.ConsumeIntegralInRange<size_t>(0, 2048));
        GssTsigKey key(key_name, payload);
        GssTsigContext ctx(key);

        std::string wire = fdp.ConsumeRandomLengthString(2048);
        ctx.sign(qid, wire.data(), wire.size());

        Name owner_name(owner_txt.empty() ? "fuzz." : owner_txt.c_str());
        rdata::any::TSIG tsig_rdata(tsig_rdata_txt);
        TSIGRecord record(owner_name, tsig_rdata);

        ctx.verify(&record, wire.data(), wire.size());
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    // Target key exchange
    try {
        auto val = fdp.ConsumeIntegralInRange<int>(-5, 10);
        TKeyExchange::statusToText(static_cast<TKeyExchange::Status>(val));
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    return 0;
}
