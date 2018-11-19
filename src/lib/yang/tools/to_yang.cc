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
#ifndef HAVE_PRE_0_7_6_SYSREPO
using namespace sysrepo;
#endif

/// @file From JSON to YANG utility.

/// @brief Print to-yang usage.
void
usage() {
    cerr << "Usage: to-yang <model>" << endl;
}

int
main(int argc, char* argv[]) {
    if (argc != 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    ConstElementPtr json;
    try {
        json = Element::fromJSON(cin, true);
    } catch (const Exception& ex) {
        cerr << "Can't get config: " << ex.what() << endl;
        exit(EXIT_FAILURE);
    }

    S_Connection conn;
    try {
        conn.reset(new Connection("to-yang"));
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

    try {
        TranslatorConfig(sess, argv[1]).setConfig(json);
    } catch (const Exception& ex) {
        cerr << "Translation failed with: " << ex.what() << endl;
        exit(EXIT_FAILURE);
    }

    try {
        sess->validate();
    } catch (const sysrepo_exception& ex) {
        cerr << "Failed to validate: " << ex.what() << endl;
        exit(EXIT_FAILURE);
    }

    try {
        sess->commit();
    } catch (const sysrepo_exception& ex) {
        cerr <<"Failed to commit: " << ex.what() << endl;
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
