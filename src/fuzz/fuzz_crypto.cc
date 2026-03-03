// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <config.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <dns/tsig.h>
#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hmac.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <memory>

using namespace isc::dns;
using namespace isc::cryptolink;
using namespace isc::util;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider fdp(data, size);

    std::string secret = fdp.ConsumeRandomLengthString(64);
    std::string tsig_data = fdp.ConsumeRandomLengthString(1024);

    // TSIGContext
    try {
        // Create TSIGContext
        TSIGKey tsigkey("fuzz_key:" + secret);
        TSIGContext ctx(tsigkey);

        // TSIGContext sign
        uint16_t qid = fdp.ConsumeIntegral<uint16_t>();
        ctx.sign(qid, tsig_data.data(), tsig_data.size());

        // Create TSIGRecord
        Name name("fuzz_record");
        TSIGRecord record(name, rdata::any::TSIG(fdp.ConsumeRandomLengthString(1024)));

        ctx.verify(&record, tsig_data.data(), tsig_data.size());
    } catch (const isc::Exception&) {
        // Slient ezceptions
    }

    // HMAC
    try {
        // HMAC Sign
        OutputBuffer hmac(256);
        signHMAC(tsig_data.data(), tsig_data.size(), secret.data(), secret.size(),
            static_cast<HashAlgorithm>(fdp.ConsumeIntegralInRange<int>(0, 6)), hmac);

        // HMAC Verify
        std::string sig = fdp.ConsumeRandomLengthString(256);
        verifyHMAC(tsig_data.data(), tsig_data.size(), secret.data(), secret.size(),
            static_cast<HashAlgorithm>(fdp.ConsumeIntegralInRange<int>(0, 6)),
            sig.data(), sig.size());
    } catch (const isc::Exception&) {
        // Slient ezceptions
    }

    return 0;
}
