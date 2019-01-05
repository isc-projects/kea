// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <kea_version.h>

#include <yang/translator_config.h>
#include <yang/sysrepo_error.h>

#include <fstream>
#include <iostream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
#ifndef HAVE_PRE_0_7_6_SYSREPO
using namespace sysrepo;
#endif

/// @file From YANG to JSON utility: the sysrepo startup datastore is
/// exported into a configuration file.

/// @brief Print export-from-yang4 usage.
void
usage() {
    cerr << "Usage: export-from-yang4 [-v] [-V] -m <model> -o <output>"
         << endl;
}

int
main(int argc, char* argv[]) {
    string model("kea-dhcp4-server");
    string output_file("");

    int ch;
    while ((ch = getopt(argc, argv, "m:o:vV")) != -1) {
        switch (ch) {
        case 'm':
            model = optarg;
            break;

        case 'o':
            output_file = optarg;
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

    try {
        S_Connection conn;
        try {
            conn.reset(new Connection("export-from-yang4"));
        } catch (const sysrepo_exception& ex) {
            isc_throw(SysrepoError, "can't connect to sysrepo: " << ex.what());
        }

        S_Session sess;
        try {
            sess.reset(new Session(conn, SR_DS_STARTUP));
        } catch (const sysrepo_exception& ex) {
            isc_throw(SysrepoError, "can't establish a session: " << ex.what());
        }

        ConstElementPtr json;
        try {
            json = TranslatorConfig(sess, model).getConfig();
        } catch (const exception& ex) {
            isc_throw(SysrepoError, "translation failed: " << ex.what());
        }

        if (!json) {
            isc_throw(SysrepoError, "got an emoty result");
        }

        if (output_file.empty()) {
            cout << prettyPrint(json) << endl;
        } else {
            ofstream out(output_file, ios::trunc);
            if (!out.good()) {
                isc_throw(Unexpected, "Unable to open file " + output_file +
                          " for writing");
                out << prettyPrint(json) << endl;
            }
            out.close();
        }
    } catch (const std::exception& ex) {
        cerr << "export-from-yang4 failed with " << ex.what() << endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
