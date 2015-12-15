// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// BEGIN_HEADER_GUARD

#include <string>

#include <dns/rdata.h>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

// To add RDATA class definition of a new RR type (say "MyType"), copy this
// file to an appropriate subdirectory (if it's class-independent type, it
// should go to "generic/", if it's IN-class specific, it should be in
// "in_1/", and so on).  The copied file should be named as type_nn.h where
// "type" is textual representation (all lower cased) of the RR type, and "nn"
// is the 16-bit type code of the RR type.
// Normally, you'll need to define some specific member variables in the
// "RR-type specific members" space (please make them private).  In addition,
// you may want to define some specific member functions, either public or
// private (or, though unlikely for a leaf class, protected).
//
// Note: do not remove the comment lines beginning with "BEGIN_" and "END_".
// These are markers used by a script for auto-generating build-able source
// files.
//
// On completion of implementing a new type of Rdata, remove the corresponding
// entry from the meta_types dictionary of gen-rdatacode.py.in.  Otherwise
// it will cause build failure.

class MyType : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // Do not remove the BEGIN_xxx and END_xxx comment lines.
    // END_COMMON_MEMBERS
private:
    // RR-type specific members are here.
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables: 
// mode: c++
// End: 
