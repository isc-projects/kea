// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

extern "C" {

extern std::string KEA_FUZZ_DIR;
extern std::string KEA_LFC;

bool
DoInitialization();

int
LLVMFuzzerInitialize();

int
LLVMFuzzerTearDown();

int
LLVMFuzzerTestOneInput(uint8_t const* data, size_t size);

void
writeToFile(std::string const& file, std::string const& content);

bool
byteStreamToPacketData(uint8_t const* data, size_t size, std::vector<uint8_t>& byte_stream);

}  // extern "C"