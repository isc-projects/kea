// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include "helper_func.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <unistd.h>

namespace fs = std::filesystem;

using namespace isc::data;

namespace fuzz {
    std::string writeTempConfig(bool isV4) {
        return writeTempFile(isV4? JSON_CONFIG4 : JSON_CONFIG6);
    }

    std::string writeTempLease(bool isV4) {
        if (isV4) {
            return writeTempFile(LEASE4, "", "/tmp/kea-leases4.csv");
        } else {
            return writeTempFile(LEASE6, "", "/tmp/kea-leases6.csv");
        }
    }

    std::string writeTempUserFile() {
        return writeTempFile(USER, "", "/tmp/users.txt");
    }

    std::string writeTempFile(const std::string& payload, const char* suffix, const std::string& explicit_path) {
        std::string path = explicit_path;
        if (explicit_path.empty()) {
            const long r = std::rand();
            const pid_t pid = ::getpid();
            path = std::string("/tmp/kea_fuzz_") + std::to_string(pid) +
                   "_" + std::to_string(r) + "." + (suffix ? suffix : "tmp");
        }

        std::ofstream ofs(path.c_str(), std::ios::binary);
        if (ofs.good()) {
            ofs.write(payload.data(), static_cast<std::streamsize>(payload.size()));
            ofs.close();
            return path;
        }
        return std::string();
    }

    void deleteTempFile(std::string file_path) {
        if (fs::exists(file_path)) {
            try {
                fs::remove(file_path);
            } catch (...) {
                // Slient exceptions
            }
        }
    }

    isc::data::ElementPtr parseJSON(const std::string& s) {
        try {
            return Element::fromJSON(s);
        } catch (...) {
            return Element::createMap();
        }
    }
}
