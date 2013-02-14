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

// Note: this is derived from the generic Loader class of the C++
// implementation, but is slightly different from the original.
// Be careful when you make further merge from the C++ document.
const char* const RequestLoader_doc = "\
Loader of DNS Request ACLs.\n\
\n\
The goal of this class is to convert JSON description of an ACL to\n\
object of the ACL class (including the checks inside it).\n\
\n\
To allow any kind of checks to exist in the application, creators are\n\
registered for the names of the checks (this feature is not yet\n\
available for the python API).\n\
\n\
An ACL definition looks like this:  [\n\
   {\n\
      \"action\": \"ACCEPT\",\n\
      \"match-type\": <parameter>\n\
   },\n\
   {\n\
      \"action\": \"REJECT\",\n\
      \"match-type\": <parameter>,\n\
      \"another-match-type\": [<parameter1>, <parameter2>]\n\
   },\n\
   {\n\
      \"action\": \"DROP\"\n\
   }\n\
 ]\n\
 \n\
\n\
This is a list of elements. Each element must have an \"action\"\n\
entry/keyword. That one specifies which action is returned if this\n\
element matches (the value of the key is passed to the action loader\n\
(see the constructor), which is one of ACCEPT,\n\
REJECT, or DROP, as defined in the isc.acl.acl module.\n\
\n\
The rest of the element are matches. The left side is the name of the\n\
match type (for example \"from\" to match for source IP address).\n\
The <parameter> is whatever is needed to describe the\n\
match and depends on the match type, the loader passes it verbatim to\n\
creator of that match type.\n\
\n\
There may be multiple match types in single element. In such case, all\n\
of the matches must match for the element to take action (so, in the\n\
second element, both \"match-type\" and \"another-match-type\" must be\n\
satisfied). If there's no match in the element, the action is\n\
taken/returned without conditions, every time (makes sense as the last\n\
entry, as the ACL will never get past it).\n\
\n\
The second entry shows another thing - if there's a list as the value\n\
for some match and the match itself is not expecting a list, it is\n\
taken as an \"or\" - a match for at last one of the choices in the\n\
list must match. So, for the second entry, both \"match-type\" and\n\
\"another-match-type\" must be satisfied, but the another one is\n\
satisfied by either parameter1 or parameter2.\n\
\n\
Currently, a RequestLoader object cannot be constructed directly;\n\
an application must use the singleton loader defined in the\n\
isc.acl.dns module, i.e., isc.acl.dns.REQUEST_LOADER.\n\
A future version of this implementation may be extended to give\n\
applications full flexibility of creating arbitrary loader, when\n\
this restriction may be removed.\n\
";

const char* const RequestLoader_load_doc = "\
load(description) -> RequestACL\n\
\n\
Load a DNS (Request) ACL.\n\
\n\
This parses an ACL list, creates internal data for each rule\n\
and returns a RequestACl object that contains all given rules.\n\
\n\
Exceptions:\n\
  LoaderError Load failed.  The most likely cause of this is a syntax\n\
              error in the description.  Other internal errors such as\n\
              memory allocation failure is also converted to this\n\
              exception.\n\
\n\
Parameters:\n\
  description String or Python representation of the JSON list of\n\
              ACL. The Python representation is ones accepted by the\n\
              standard json module.\n\
\n\
Return Value(s): The newly created RequestACL object\n\
";
} // unnamed namespace
