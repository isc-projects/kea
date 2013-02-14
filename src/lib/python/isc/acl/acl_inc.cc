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
const char* const acl_doc = "\
Implementation module for ACL operations\n\n\
This module provides Python bindings for the C++ classes in the\n\
isc::acl namespace.\n\
\n\
Integer constants:\n\
\n\
ACCEPT, REJECT, DROP -- Default actions an ACL could perform.\n\
  These are the commonly used actions in specific ACLs.\n\
  It is possible to specify any other values, as the ACL class does\n\
  nothing about them, but these look reasonable, so they are provided\n\
  for convenience. It is not specified what exactly these mean and it's\n\
  up to whoever uses them.\n\
";
} // unnamed namespace
