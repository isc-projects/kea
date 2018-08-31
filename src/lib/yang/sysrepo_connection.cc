// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <yang/sysrepo_connection.h>

namespace isc {
namespace yang {

SysrepoConnection::SysrepoConnection() {
}

SysrepoConnection::~SysrepoConnection() {
    if (session_) {
      session_->discard_changes();
      session_->unlock_datastore();
      session_->session_stop();

      // how to call disconnect?
    }
}

void
SysrepoConnection::connect() {

    // Get a connection.
    S_Connection conn(new Connection("kea-netconf"));
    // Get a session.
    session_.reset(new Session(conn, SR_DS_CANDIDATE));
    // Get a from yang object.
}

void
SysrepoConnection::commit() {
  if (!session_) {
    isc_throw(SysrepoConnectionError, "session not established");
  }
  session_->commit();
}

}
}
