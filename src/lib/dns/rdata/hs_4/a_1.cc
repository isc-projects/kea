// Copyright (C) 2010-2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

A::A(const std::string&) {
    // TBD
}

A::A(MasterLexer&, const Name*,
     MasterLoader::Options, MasterLoaderCallbacks&)
{
    // TBD
}

A::A(InputBuffer&, size_t) {
    // TBD
}

A::A(const A&) : Rdata() {
    // TBD
}

void
A::toWire(OutputBuffer&) const {
    // TBD
}

void
A::toWire(AbstractMessageRenderer&) const {
    // TBD
}

string
A::toText() const {
    // TBD
    isc_throw(InvalidRdataText, "Not implemented yet");
}

int
A::compare(const Rdata&) const {
    return (0);                 // dummy.  TBD
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
