// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <kea_version.h>

#include <yang/translator_config.h>
#include <yang/sysrepo_error.h>
#include <dhcp6/parser_context.h>

#include <iostream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
#ifndef HAVE_PRE_0_7_6_SYSREPO
using namespace sysrepo;
#endif

/// @file From JSON to YANG utility: the configuration file is translated
/// and imported in the sysrepo startup datastore.

/// @brief Print import-to-yang6 usage.
void
usage() {
    cerr << "Usage: import-to-yang6 [-v] [-V] -i <input> -m <model>"
         << endl;
}

int
main(int argc, char* argv[]) {
    string input_file("");
    string model("kea-dhcp6-server");

    int ch;
    while ((ch = getopt(argc, argv, "i:m:vV")) != -1) {
        switch (ch) {
        case 'i':
            input_file = optarg;
            break;

        case 'm':
            model = optarg;
            break;

        case 'v':
            cout << VERSION << endl;
            return (EXIT_SUCCESS);

        case 'V':
            cout << VERSION << endl << EXTENDED_VERSION << endl;
            return (EXIT_SUCCESS);

        default:
            usage();
            return (EXIT_FAILURE);
        }
    }

    // Check for extraneous parameters.
    if (argc > optind) {
        usage();
        return (EXIT_FAILURE);
    }

    // Input file is required.
    if (input_file.empty()) {
        cerr << "Input file was not specified." << endl;
        usage();
        return (EXIT_FAILURE);
    }

    try {
        Parser6Context parser;
        ConstElementPtr json;
        json = parser.parseFile(input_file, Parser6Context::PARSER_DHCP6);
        if (!json) {
            cerr << "No input found" << endl;
            return (EXIT_FAILURE);
        }

        S_Connection conn;
        try {
            conn.reset(new Connection("import-to-yang6"));
        } catch (const sysrepo_exception& ex) {
            isc_throw(SysrepoError, "can't connect to sysrepo: " << ex.what());
        }

        S_Session sess;
        try {
            sess.reset(new Session(conn, SR_DS_STARTUP));
        } catch (const sysrepo_exception& ex) {
            isc_throw(SysrepoError, "can't establish a session: " << ex.what());
        }

        try {
            TranslatorConfig(sess, model).setConfig(json);
        } catch (const exception& ex) {
            isc_throw(SysrepoError, "translation failed: " << ex.what());
        }

        try {
            sess->validate();
        } catch (const sysrepo_exception& ex) {
            isc_throw(SysrepoError, "failed to validate: " << ex.what());
        }

        try {
            sess->commit();
        } catch (const sysrepo_exception& ex) {
            isc_throw(SysrepoError, "failed to commit " << ex.what());
        }
    } catch (const std::exception& ex) {
        cerr << "import-to-yang6 failed with " << ex.what() << endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
