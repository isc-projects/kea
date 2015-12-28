// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "sockcreator.h"
#include <unistd.h>

using namespace isc::socket_creator;

int
main() {
    /*
     * TODO Maybe use some OS-specific caps interface and drop everything
     * but ability to bind ports? It would be nice.
     */
    try {
        run(STDIN_FILENO, STDOUT_FILENO, getSock, isc::util::io::send_fd, close);
    } catch (const SocketCreatorError& ec) {
        return (ec.getExitCode());
    }
    return (0);
}
