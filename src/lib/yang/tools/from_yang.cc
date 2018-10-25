// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_config.h>

#include <iostream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;

/// @file From YANG to JSON utility.

/// @brief Print from-yang usage.
void
usage() {
    cerr << "Usage: from-yang <model>" << endl;
}

int
main(int argc, char* argv[]) {
    if (argc != 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    S_Connection conn;
    try {
        conn.reset(new Connection("from-yang"));
    } catch (const sysrepo_exception& ex) {
        cerr << "Can't connect to sysrepo: " << ex.what() << endl;
        exit(EXIT_FAILURE);
    }

    S_Session sess;
    try {
        sess.reset(new Session(conn, SR_DS_STARTUP));
    } catch (const sysrepo_exception& ex) {
        cerr << "Can't establish a session: " << ex.what() << endl;
        exit(EXIT_FAILURE);
    }

    ConstElementPtr json;
    try {
        json = TranslatorConfig(sess, argv[1]).getConfig();
    } catch (const Exception& ex) {
        cerr << "Translation failed with: " << ex.what() << endl;
        exit(EXIT_FAILURE);
    }

    if (!json) {
        cerr << "Got an empty result" << endl;
        exit(EXIT_FAILURE);
    }

    prettyPrint(json, cout);

    exit(EXIT_SUCCESS);
}
