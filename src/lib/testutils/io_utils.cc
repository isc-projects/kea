// Copyright (C) 2015-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <testutils/io_utils.h>
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <string>

namespace isc {
namespace test {

bool fileExists(const std::string& file_path) {
    struct stat statbuf;
    return(stat(file_path.c_str(), &statbuf) == 0);
}

std::string readFile(const std::string& file_path) {
    std::ifstream ifs;
    ifs.open(file_path.c_str(), std::ifstream::in);
    if (!ifs.good()) {
        return (std::string());
    }
    std::string buf;
    std::ostringstream output;
    while (!ifs.eof() && ifs.good()) {
        ifs >> buf;
        output << buf;
    }
    ifs.close();

    return (output.str());
}

std::string decommentJSONfile(const std::string& input_file) {

    using namespace std;

    ifstream f(input_file);
    if (!f.is_open()) {
        isc_throw(isc::BadValue, "can't open input file for reading: " + input_file);
    }

    string outfile;
    size_t last_slash = input_file.find_last_of("/");
    if (last_slash != string::npos) {
        outfile = input_file.substr(last_slash + 1);
    } else {
        outfile = input_file;
    }
    outfile += "-decommented";

    ofstream out(outfile);
    if (!out.is_open()) {
        isc_throw(isc::BadValue, "can't open output file for writing: " + input_file);
    }

    bool in_comment = false;
    string line;
    while (std::getline(f, line)) {
        // First, let's get rid of the # comments
        size_t hash_pos = line.find("#");
        if (hash_pos != string::npos) {
            line = line.substr(0, hash_pos);
        }

        // Second, let's get rid of the // comments
        // at the beginning or after a control character.
        size_t dblslash_pos = line.find("//");
        if ((dblslash_pos != string::npos) &&
            ((dblslash_pos == 0) ||
             ((unsigned) line[dblslash_pos - 1] <= 32))) {
            line = line.substr(0, dblslash_pos);
        }

        // Now the tricky part: c comments.
        size_t begin_pos = line.find("/*");
        size_t end_pos = line.find("*/");
        if (in_comment && end_pos == string::npos) {
            // we continue through multiline comment
            line = "";
        } else {

            if (begin_pos != string::npos) {
                in_comment = true;
                if (end_pos != string::npos) {
                    // single line comment. Let's get rid of the content in between
                    line = line.replace(begin_pos, end_pos + 2, end_pos + 2 - begin_pos, ' ');
                    in_comment = false;
                } else {
                    line = line.substr(0, begin_pos);
                }
            } else {
                if (in_comment && end_pos != string::npos) {
                    line = line.replace(0, end_pos +2 , end_pos + 2, ' ');
                    in_comment = false;
                }
            }
        }

        // Finally, write the line to the output file.
        out << line << endl;
    }
    f.close();
    out.close();

    return (outfile);
}

}; // end of isc::test namespace
}; // end of isc namespace
