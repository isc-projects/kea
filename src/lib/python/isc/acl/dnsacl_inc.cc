// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

namespace {
const char* const dnsacl_doc = "\
Implementation module for DNS ACL operations\n\n\
This module provides Python bindings for the C++ classes in the\n\
isc::acl::dns namespace.  Specifically, it defines Python interfaces of\n\
handling access control lists (ACLs) with DNS related contexts.\n\
These bindings are close match to the C++ API, but they are not complete\n\
(some parts are not needed) and some are done in more python-like ways.\n\
\n\
Special objects:\n\
\n\
REQUEST_LOADER -- A singleton loader of ACLs. It is expected applications\n\
  will use this function instead of creating their own loaders, because\n\
  one is enough, this one will have registered default checks and it is\n\
  known one, so any plugins can registrer additional checks as well.\n\
";
} // unnamed namespace
