// Copyright (C) 2024-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/filesystem.h>
#include <fuzz.h>

#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <vector>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace isc;
using namespace isc::util::file;
using namespace std;

int
main(int, char* argv[]) {
    int const return_code(LLVMFuzzerInitialize());
    assert(return_code == 0);

    // Determine some paths.
    Path const this_binary(argv[0]);
    string ancestor_path(this_binary.parentPath());
    string const filename(this_binary.filename());
    stringstream ss;
    ss << ancestor_path << "/input/" << filename;
    Path const p(ss.str());

    // Print start header.
    if (isatty(fileno(stdin))) {
        cout << "\033[92m[ RUN      ]\033[0m " << filename << endl;
    } else {
        cout << "[ RUN      ] " << filename << endl;
    }

    int exit_code(0);
    string directory(p.str());
    if (exists(directory)) {
        // Recursively take all regular files as input.
        list<string> files;

        struct dirent *dp;
        DIR *dfd(opendir(directory.c_str()));
        if (!dfd) {
            isc_throw(Unexpected, "opendir failed " << directory << ": " << strerror(errno));
        }
        std::unique_ptr<DIR, void(*)(DIR*)> defer(dfd, [](DIR* d) { closedir(d); });
        while ((dp = readdir(dfd)) != nullptr) {
            string file(dp->d_name);
            if (file == "." || file == "..") {
                continue;
            }
            string entry(directory + '/' + dp->d_name);

            if (!isFile(entry)) {
                continue;
            }

            // Save file names.
            files.push_back(entry);
        }

        // Sort the file names so that the order is the same each time.
        files.sort();

        for (string& f : files) {
            // Read content from file.
            ifstream file(f, ios::binary);

            if (!file.is_open()) {
                cerr << "ERROR: could not open file " << f << endl;
                return 1;
            }

            // Get the file size.
            file.seekg(0, std::ios::end);
            streampos const bytes(file.tellg());
            file.seekg(0, std::ios::beg);

            // Read the entire file into a vector.
            vector<uint8_t> buffer(bytes);
            file.read(reinterpret_cast<char*>(buffer.data()), bytes);

            file.close();

            // Fuzz.
            f.replace(f.find(ancestor_path), ancestor_path.size() + 1, string());
            cout << "Fuzzing with " << bytes << " byte" << (bytes == 1 ? string() : "s") << " read from "
                 << f << "..." << endl;
            exit_code |= LLVMFuzzerTestOneInput(buffer.data(), bytes);
        }
    } else {
        // Read input from stdin.
        cout << "Waiting on input..." << endl;
        vector<uint8_t> buffer(65536);
        size_t const bytes(fread(&buffer[0], sizeof(buffer[0]), buffer.size(), stdin));

        // Fuzz.
        cout << "Fuzzing with " << bytes << " byte" << (bytes == 1 ? "" : "s")
             << " read from stdin..." << endl;
        exit_code |= LLVMFuzzerTestOneInput(buffer.data(), bytes);
    }

    // Tear down the setup.
    LLVMFuzzerTearDown();

    // Print end header.
    string const result(exit_code == 0 ? "       OK " : "  FAILED  ");
    if (isatty(fileno(stdin))) {
        cout << "\033[92m[" << result << "]\033[0m " << filename << endl;
    } else {
        cout << "[" << result << "] " << filename << endl;
    }

    return exit_code;
}
