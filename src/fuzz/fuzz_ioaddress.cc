// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <cstddef>
#include <cstdint>
#include <string>

#include <asiolink/io_address.h>
#include <asiolink/io_error.h>

using isc::asiolink::IOAddress;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::string s(reinterpret_cast<const char*>(data), size);

  try {
    IOAddress addr(s);
    addr.toText();
    addr.isV4();
    addr.isV6();
    addr.getFamily();
    addr.toBytes();

    std::vector<uint8_t> bytes = addr.toBytes();
    IOAddress::fromBytes(addr.getFamily(), &bytes[0]);
  } catch (const std::exception&) {
    // Catch exceptions
  }

  return 0;
}
