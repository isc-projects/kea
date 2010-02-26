// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

// $Id$

#ifndef __AUTH_SRV_H
#define __AUTH_SRV_H 1

#include <cc/data.h>
#include <auth/data_source_static.h>
#include <auth/data_source_sqlite3.h>

class AuthSrv {
public:
    explicit AuthSrv(int port);
    int getSocket() { return (sock); }
    void processMessage();
    void serve(std::string zone_name);

    isc::data::ElementPtr updateConfig(isc::data::ElementPtr config);
private:

    isc::auth::MetaDataSrc data_src;
    int sock;
};

#endif // __AUTH_SRV_H

